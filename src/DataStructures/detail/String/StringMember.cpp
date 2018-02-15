#pragma once
#include <stdexcept>
#include "String.h"

const gfm::String gfm::String::empty("");

gfm::String gfm::String::ToLower() const {
	return ChangeForEachAndCopy([](CharType& ch, CharType tch) {
		ch = detail::CStringHelper::ToLower(tch);
	});
}

gfm::String gfm::String::ToUpper() const {
	return ChangeForEachAndCopy([](CharType& ch, CharType tch) {
		ch = detail::CStringHelper::ToUpper(tch);
	});
}

gfm::String gfm::String::ChangeForEachAndCopy(void(*predicate)(CharType&, CharType)) const {
	String result;
	result.Reserve(m_length);
	result.m_length = m_length;
	if (m_length > ms_SSOSIZE) {
		result.SetUseNoSSO();
	}
	CharType* rightData = result.Raw();
	const CharType* thisData = Raw();
	for (SizeType i = 0; i < m_length; ++i) {
		predicate(rightData[i], thisData[i]);
	}
	return result;
}

void gfm::String::Reserve(SizeType size) {
	if (m_capacity > size || size < ms_SSOSIZE) {
		return;
	}
	auto * temp = static_cast<CharType*>(m_allocator.Allocate(size * sizeof(CharType)));
	if (m_length != 0) {
		detail::CStringHelper::Copy(temp, Raw(), m_length);
	}
	if (!UsesSSO()) {
		m_allocator.Deallocate(m_ptr);
	}
	m_ptr = temp;
	m_capacity = size;
	SetUseNoSSO();
}

void gfm::String::Resize(SizeType newSize) {
	if (m_length > newSize) {
		return;
	}
	if (newSize <= ms_SSOSIZE) {
		memset(m_ssoArray, 0, sizeof(CharType) * newSize);
		SetUseSSO();
		m_length = newSize;
		return;
	}
	if (newSize > m_capacity && newSize > ms_SSOSIZE) {
		auto * temp = static_cast<CharType*>(m_allocator.Allocate(newSize * sizeof(CharType)));
		detail::CStringHelper::Copy(temp, m_ptr, m_length);
		m_allocator.Deallocate(m_ptr);
		m_ptr = temp;
		m_capacity = newSize;
		SetUseNoSSO();
	}
	memset(m_ptr + m_length, 0, newSize - m_length);
	m_length = newSize;
}

void gfm::String::Clear() noexcept
{
	if (m_length == 0) {
		return;
	}
	memset(Raw(), 0, Length() * sizeof(CharType));
	m_length = 0;
}

gfm::String gfm::String::SubString(SizeType index) const {
	return SubString(index, m_length);
}

gfm::String gfm::String::SubString(SizeType index, SizeType length) const {
	String result;
	if (index < 0 || index >= m_length || index + length > m_length) {
		return result;
	}
	if (length > ms_SSOSIZE) {
		result.SetUseSSO();
	}
	result.Reserve(length);
	result.m_length = length;
	detail::CStringHelper::Copy(result.Raw(), Raw() + index, length - 1);
	result.Raw()[length] = 0;
	return result;
}

gfm::String gfm::String::Trim() const {
	return Trim(0);
}

gfm::String gfm::String::Trim(SizeType index) const {
	String result;
	if (index < 0 || index >= m_length) {
		return result;
	}
	result.Reserve(m_length);
	const CharType* ptr = Raw();
	for (SizeType i = index; i < m_length; i++) {
		if (detail::CStringHelper::IsSpace(ptr[i])) {
			continue;
		}
		result.Append(ptr[i]);
	}
	result.Append(GFM_STRING('\0'));
	return result;
}

gfm::String gfm::String::Trim(const List<CharType>& ToTrimChars) const {
	String result;
	result.Reserve(Length());
	for (auto ch : *this) {
		if (ToTrimChars.Any(ch)) {
			continue;
		}
		result.Append(ch);
	}
	return result;
}

void gfm::String::Grow(SizeType toGrowSize) {
	if (m_capacity + toGrowSize <= ms_SSOSIZE) {
		return;
	}
	m_capacity += toGrowSize;
	auto* temp = static_cast<CharType*>(m_allocator.Allocate(m_capacity * sizeof(CharType)));
	if (m_length != 0) {
		detail::CStringHelper::Copy(temp, Raw(), m_length);
	}
	if (!UsesSSO()) {
		m_allocator.Deallocate(m_ptr);
	}
	m_ptr = temp;
	SetUseNoSSO();
}

void gfm::String::GrowIfToSmall(SizeType toGrowSize) {
	++toGrowSize; // for /0
	if (m_length + toGrowSize < ms_SSOSIZE) {
		return;
	}
	if (m_capacity >= m_length + toGrowSize) {
		return;
	}
	if (m_capacity + toGrowSize < m_capacity * 2) {
		m_capacity *= 2;
	}
	else if (toGrowSize + m_length > m_capacity) {
		m_capacity = toGrowSize + m_length;
	}
	else {
		m_capacity += toGrowSize;
	}
	if (m_length == 0) {
		++m_capacity;
	}
	const auto* myRaw = Raw();
	auto * temp = static_cast<CharType*>(m_allocator.Allocate(m_capacity * sizeof(CharType)));
	if (m_length != 0) {
		detail::CStringHelper::Copy(temp, myRaw, m_length);
	}
	if (!UsesSSO()) {
		m_allocator.Deallocate(m_ptr);
	}
	m_ptr = temp;
	SetUseNoSSO();

}

gfm::String::CharType & gfm::String::operator[](SizeType index)
{
	if (index >= m_length) {
		throw std::out_of_range("String operator[] index was out of range!");
	}
	return (UsesSSO()) ? m_ssoArray[index] : m_ptr[index];
}

const gfm::String::CharType & gfm::String::operator[](SizeType index) const
{
	if (index >= m_length) {
		throw std::out_of_range("String operator[] index was out of range!");
	}
	return (UsesSSO()) ? m_ssoArray[index] : m_ptr[index];
}

gfm::String& gfm::String::operator =(const String& other) {
	if (this != &other) {
		if (!UsesSSO() && m_capacity < other.m_length) {
			m_allocator.Deallocate(m_ptr);
			m_ptr = static_cast<CharType*>(m_allocator.Allocate(other.m_length * sizeof(CharType)));
			m_capacity = other.m_length;
		}
		detail::CStringHelper::Copy(Raw(), other.Raw(), other.m_length);
		m_length = other.m_length;
	}
	return *this;
}

gfm::String& gfm::String::operator =(String&& other) {
	if (this != &other) {
		if(!other.UsesSSO()){
			if (!UsesSSO()) {
				m_allocator.Deallocate(m_ptr);
			}
			m_ptr = other.m_ptr;
			m_capacity = other.m_capacity;
			m_length = other.m_length;
			other.m_length = 0;
			other.m_capacity = 0;
			other.m_ptr = nullptr;
			SetUseNoSSO();
		}
		else {
			detail::CStringHelper::Copy(Raw(), other.Raw(), other.m_length);
			m_length = other.m_length;
		}
	}
	return *this;
}

gfm::String& gfm::String::operator =(const wchar_t* other) {
	return (*this = std::move(String(other)));
}
gfm::String& gfm::String::operator =(const char* other) {
	return (*this = std::move(String(other)));
}

bool gfm::String::operator ==(const String& right) const {
	return right.Length() == Length() && detail::CStringHelper::Compare(right.Raw(), Raw(), Length()) == 0;
}

bool gfm::String::operator ==(const CharType* right) const {
	auto rightLen = detail::CStringHelper::Len(right);
	return rightLen == Length() && detail::CStringHelper::Compare(right, Raw(), Length()) == 0;
}

bool gfm::String::operator !=(const String& right) const {
	return !(*this == right);
}

bool gfm::String::operator !=(const CharType* right) const {
	return !(*this == right);
}

gfm::String& gfm::String::operator +=(const String& other) {
	return Append(other);
}

gfm::String& gfm::String::operator +=(const std::string& other) {
	return Append(other);
}

gfm::String& gfm::String::operator +=(const std::wstring& other) {
	return Append(other);
}

gfm::String& gfm::String::operator +=(const char* str) {
	return Append(str);
}

gfm::String& gfm::String::operator +=(const wchar_t* str) {
	return Append(str);
}

gfm::String& gfm::String::operator +=(const gfm::List<char>& other) {
	return Append(other);
}

gfm::String& gfm::String::operator +=(const gfm::List<wchar_t>& other) {
	return Append(other);
}

gfm::String& gfm::String::operator *=(SizeType skalar) {
	GrowIfToSmall(Length() * skalar);
	auto* myRaw = Raw();
	const auto* myConstRaw = Raw();
	auto oneLen = Length();
	for (SizeType i = 0; i < skalar; ++i) {
		detail::CStringHelper::Copy(myRaw + m_length, myConstRaw, oneLen);
		m_length += oneLen;
	}
	return *this;
}

gfm::String& gfm::String::Append(const String& other) {
	AppendRawStr(other.Raw(), other.Length());
	return *this;
}

gfm::String& gfm::String::Append(const std::string& other) {
	AppendRawStr(other.c_str(), other.length());
	return *this;
}

gfm::String & gfm::String::Append(const std::wstring & other) {
	AppendRawStr(other.c_str(), other.length());
	return *this;
}

gfm::String& gfm::String::Append(const char* str) {
	auto len = detail::CStringHelper::Len(str);
	AppendRawStr(str, len);
	return *this;
}

gfm::String& gfm::String::Append(const wchar_t* str) {
	auto len = detail::CStringHelper::Len(str);
	AppendRawStr(str, len);
	return *this;
}

gfm::String& gfm::String::Append(const gfm::List<char>& other) {
	AppendRawStr(other.Raw(), other.Length());
	return *this;
}

gfm::String& gfm::String::Append(const gfm::List<wchar_t>& other) {
	AppendRawStr(other.Raw(), other.Length());
	return *this;
}

gfm::String gfm::String::Replace(CharType from, CharType to) const {
	String result;
	result.Reserve(Length());
	for (auto ch : *this) {
		if (ch == from) {
			result.Append(to);
			continue;
		}
		result.Append(ch);
	}
	return result;
}

gfm::String gfm::String::Replace(const String & from, const String & to) const
{
	String result;
	result.Reserve(Length());
	SizeType i = 0;
	auto * mePtr = Raw();
	while (i != Length()) {
		if (detail::CStringHelper::Compare(&mePtr[i], from.Raw(), from.Length()) == 0) {
			result.Append(to);
			i += from.Length();
			continue;
		}
		result.Append(mePtr[i++]);
	}
	return result;
}

gfm::List<gfm::String> gfm::String::Split(const gfm::List<CharType>& toSplitChars) const {
	List<String> result;
	String part;
	part.Reserve(Length());
	for (auto ch : *this) {
		if (toSplitChars.Any(ch)) {
			result.Append(part);
			part.Clear();
			continue;
		}
		part.Append(ch);
	}
	return result;
}

gfm::List<gfm::String> gfm::String::Split(const gfm::List<CharType>& toSplitChars, SizeType maxSubStrings) const {
	List<String> result;
	String part;
	part.Reserve(Length());
	for (auto ch : *this) {
		if (result.Length() >= maxSubStrings) {
			break;
		}
		if (toSplitChars.Any(ch)) {
			result.Append(part);
			part.Clear();
			continue;
		}
		part.Append(ch);
	}
	return result;
}

gfm::List<gfm::String> gfm::String::Split(CharType delim) const {
	List<CharType> chList = { delim };
	return Split(chList);
}

gfm::List<gfm::String> gfm::String::Split(const String& delim) const {
	List<String> result;
	const auto* myPtr = Raw();
	auto len = Length();
	while (myPtr != myPtr + len) {
		auto cmpRes = detail::CStringHelper::Compare(myPtr, delim.CStr(), delim.Length());
		if (cmpRes == 0) {
			result.Append(SubString(Raw() - myPtr, delim.Length()));
			myPtr += delim.Length();
			continue;
		}
		++myPtr;
	}
	return result;
}

void gfm::String::ForEach(const std::function<void(CharType&)> predicate)
{
	for (auto& ch : *this) {
		predicate(ch);
	}
}

void gfm::String::ForEach(void(*predicate)(CharType&))
{
	if (predicate == nullptr) {
		throw std::invalid_argument("ForEach on String predicate was nullptr!");
	}
	for (auto & ch : *this) {
		predicate(ch);
	}
}

bool gfm::String::EndsWith(const String& value) const {
	if (value.Length() > Length()) {
		return false;
	}
	const auto* valRaw = value.Raw();
	const auto* myRaw = Raw();
	for (SizeType i = Length() - 1; i >= 0; --i) {
		if (myRaw[i] != *valRaw++) {
			return false;
		}
	}
	return true;
}

bool gfm::String::StartsWith(const String& value) const {
	if (value.Length() > Length()) {
		return false;
	}
	const auto* valRaw = value.Raw();
	const auto* myRaw = Raw();
	for (SizeType i = 0; i < value.Length(); ++i) {
		if (myRaw[i] != *valRaw++) {
			return false;
		}
	}
	return true;
}

bool gfm::String::StartsWith(const CharType* value) const {
	auto valLen = detail::CStringHelper::Len(value);
	if(valLen > Length()) {
		return false;
	}
	const auto* myRaw = Raw();
	for(SizeType i = 0; i < valLen; ++i) {
		if(value[i] != myRaw[i]) {
			return false;
		}
	}
	return true;
}

gfm::utils::int32 gfm::String::IndexOf(utils::uint32 toStartIndex, const String& value) const {
	if(value.Length() > Length()) {
		return -1;
	}
	if(toStartIndex >= Length()) {
		throw std::invalid_argument("toStartIndex can not be higher than Length!");
	}
	const auto* otherRaw = value.Raw();
	const auto* myRaw = Raw();
	for(SizeType i = toStartIndex; i < Length(); ++i) {
		if(myRaw[i] == otherRaw[0] && detail::CStringHelper::Compare(&myRaw[i], otherRaw, value.Length()) == 0) {
			return i;
		}
	}
	return -1;
}

gfm::utils::int32 gfm::String::IndexOf(const String& value) const {
	return IndexOf(0, value);
}

gfm::utils::int32 gfm::String::IndexOf(CharType ch) const {
	return IndexOf(0, ch);
}
gfm::utils::int32 gfm::String::IndexOf(utils::uint32 toStartIndex, CharType ch) const {
	if(toStartIndex - 1 >= Length()) {
		throw std::out_of_range("IndexOf toStartIndex to High!");
	}
	const auto* myRaw = Raw();
	for(SizeType i = toStartIndex; i < Length(); ++i) {
		auto char_ = myRaw[i];
		if(myRaw[i] == ch) {
			return i;
		}
	}
	return -1;
}

gfm::utils::int32 gfm::String::LastIndexOf(const String& value) const noexcept {
	if (value.Length() > Length()) {
		return -1;
	}
	const auto* otherRaw = value.Raw();
	const auto* myRaw = Raw();
	for (SizeType i = Length(); i >= 0; --i) {
		if (Length() - i >= value.Length() && detail::CStringHelper::Compare(&myRaw[i], otherRaw, value.Length()) == 0) {
			return i;
		}
	}
	return -1;
}

gfm::utils::int32 gfm::String::LastIndexOf(CharType ch) const noexcept {
	const auto* myRaw = Raw();
	for (SizeType i = 0; i < Length(); ++i) {
		if (myRaw[i] == ch) {
			return i;
		}
	}
	return -1;
}

void gfm::String::Insert(SizeType index, CharType ch) {
	if (index >= Length()) {
		throw std::out_of_range("Insert Index was out of Range!");
	}
	GrowIfToSmall(1);
	detail::CStringHelper::Copy(Raw() + index + 1, Raw() + index, Length() - index);
	Raw()[index] = ch;
	m_length++;
}

void gfm::String::Insert(SizeType index, const String& other) {
	if (index >= Length()) {
		throw std::out_of_range("Insert Index was out of Range!");
	}
	GrowIfToSmall(other.Length());
	detail::CStringHelper::Copy(Raw() + index + other.Length(), Raw() + index, Length() - index);
	detail::CStringHelper::Copy(Raw() + index, other.Raw(), other.Length());
	m_length += other.Length();
}

void gfm::String::Remove(SizeType index) {
	if (index >= Length()) {
		throw std::out_of_range("Insert Index was out of Range!");
	}
	detail::CStringHelper::Copy(Raw() + index, Raw() + index + 1, Length() - index);
	--m_length;
}

void gfm::String::Remove(SizeType index, SizeType length) {

	if (index >= Length() || index + length >= Length()) {
		throw std::out_of_range("Insert Index was out of Range!");
	}
	detail::CStringHelper::Copy(Raw() + index, Raw() + index + length, Length() - index - length);
	m_length -= length;
}

void gfm::String::FormatBuffer(const CharType * format, String & result) {
	result.Append(format);
}

gfm::String gfm::String::Format(const CharType* format) {
	return String(format);
}


bool gfm::String::isFloatingPoint() const noexcept {
	const auto* myPtr = Raw();
	if (!isdigit(myPtr[0]) && myPtr[0] != '-') {
		return false;
	}
	for (SizeType i = 1; i < Length(); ++i) {
		if (!isdigit(myPtr[i]) && myPtr[i] != '.') {
			return false;
		}
	}
	return true;
}

bool gfm::String::IsNumber() const noexcept {
	const auto* myPtr = Raw();
	if (!isdigit(myPtr[0]) && myPtr[0] != '-') {
		return false;
	}
	for (SizeType i = 1; i < Length(); ++i) {
		if (!isdigit(myPtr[i])) {
			return false;
		}
	}
	return true;
}

void gfm::String::Join(const String& delimiter, const List<String>& toJoin) {
	SizeType toAppendLen = 0;
	for (const auto& str : toJoin) {
		toAppendLen += str.Length();
	}
	toAppendLen += delimiter.Length() * toJoin.Length();
	GrowIfToSmall(toAppendLen);
	auto* myRaw = Raw();
	const auto* delimRaw = delimiter.Raw();
	auto delimLen = delimiter.Length();
	for (const auto& str : toJoin) {
		detail::CStringHelper::Copy(myRaw + m_length, delimRaw, delimLen);
		m_length += delimLen;
		detail::CStringHelper::Copy(myRaw + m_length, str.Raw(), str.Length());
		m_length += str.Length();
	}
}

void gfm::String::Join(CharType delimiter, const List<CharType>& toJoins) {
	GrowIfToSmall(toJoins.Length() * 2);
	auto* myRaw = Raw();
	for (auto ch : toJoins) {
		myRaw[m_length++] = delimiter;
		myRaw[m_length++] = ch;
	}
}
void gfm::String::Join(CharType delimiter, const List<String>& toJoin) {
	SizeType toAppendLen = 0;
	for (const auto& str : toJoin) {
		toAppendLen += str.Length();
	}
	toAppendLen += toJoin.Length();
	GrowIfToSmall(toAppendLen);
	auto* myRaw = Raw();
	for (const auto& str : toJoin) {
		myRaw[m_length++] = delimiter;
		detail::CStringHelper::Copy(myRaw + m_length, str.Raw(), str.Length());
		m_length += str.Length();
	}
}
void gfm::String::Join(const String& delimiter, const List<CharType>& toJoin) {
	GrowIfToSmall(toJoin.Length() + delimiter.Length() * toJoin.Length());
	auto* myRaw = Raw();
	auto delimLen = delimiter.Length();
	const auto* delimRaw = delimiter.Raw();
	for (auto ch : toJoin) {
		detail::CStringHelper::Copy(myRaw + m_length, delimRaw, delimLen);
		m_length += delimLen;
		myRaw[m_length++] = ch;
	}
}

gfm::utils::int32 gfm::String::ToInt() const {
	if (!IsNumber()) {
		throw std::logic_error("Can not convert ToInt when String is not A Number!!");
	}
	return detail::CStringHelper::ToInt(Raw());
}

gfm::utils::uint32 gfm::String::ToUInt() const {
	if (!IsNumber()) {
		throw std::logic_error("Can not convert ToUInt when String is not A Number!!");
	}
	return detail::CStringHelper::ToUInt(Raw());
}

gfm::utils::uint32 gfm::String::ToULong() const {
	if (!IsNumber()) {
		throw std::logic_error("Can not convert ToULong when String is not A Number!!");
	}
	return detail::CStringHelper::ToULong(Raw());
}

gfm::utils::uint32 gfm::String::ToLong() const {
	if (!IsNumber()) {
		throw std::logic_error("Can not convert ToULong when String is not A Number!!");
	}
	return detail::CStringHelper::ToLong(Raw());
}

gfm::utils::int64 gfm::String::ToLongLong() const {
	if (!IsNumber()) {
		throw std::logic_error("Can not convert ToULong when String is not A Number!!");
	}
	return detail::CStringHelper::ToLongLong(Raw());
}

gfm::utils::uint64 gfm::String::ToULongLong() const {
	if (!IsNumber()) {
		throw std::logic_error("Can not convert ToULong when String is not A Number!!");
	}
	return detail::CStringHelper::ToULongLong(Raw());
}
float gfm::String::ToFloat() const {
	if (!isFloatingPoint()) {
		throw std::logic_error("Can not convert ToULong when String is not A Number!!");
	}
	return detail::CStringHelper::ToFloat(Raw());
}

double gfm::String::ToDouble() const {
	if (!isFloatingPoint()) {
		throw std::logic_error("Can not convert ToULong when String is not A Number!!");
	}
	return detail::CStringHelper::ToDouble(Raw());
}

bool gfm::String::Contains(const String& other) const {
	const auto* me = Raw();
	auto cmpLambda = [&other](const auto* arg)->bool {
		for(auto i = 0U; i < other.Length(); ++i) {
			if(arg[i] != other[i]) {
				return false;
			}
		}
		return true;
	};

	for(auto i = 0U; i < Length(); ++i) {
		if(i + other.Length() > Length()) {
			return false;
		}
		if(cmpLambda(me + i)) {
			return true;
		}
	}
	return false;
}

bool gfm::String::Contains(CharType ch) const {
	const auto* me = Raw();
	for (auto i = 0U; i < Length(); ++i) {
		if(me[i] == ch) {
			return true;
		}
	}
	return false;
}
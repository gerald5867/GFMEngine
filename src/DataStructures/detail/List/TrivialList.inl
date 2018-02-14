#pragma once
#define LIST_TEMPLATE_PARAMS \
	template<typename ValueType, typename Allocator>

#define LIST_TEMPLATE_RESOLUTION \
	gfm::detail::TRIVIAL_LIST_NAME<ValueType, Allocator, typename std::enable_if<std::is_trivial<ValueType>::value>::type>


LIST_TEMPLATE_PARAMS
LIST_TEMPLATE_RESOLUTION::TRIVIAL_LIST_NAME(const std::initializer_list<ValueType>& initList) :
TrivialContainer<ValueType, Allocator>(initList) {
}

LIST_TEMPLATE_PARAMS
LIST_TEMPLATE_RESOLUTION::TRIVIAL_LIST_NAME(SizeType valueCount) :
TrivialContainer<ValueType, Allocator>(valueCount) {
}

LIST_TEMPLATE_PARAMS
LIST_TEMPLATE_RESOLUTION::TRIVIAL_LIST_NAME(ValueType&& value, SizeType count) :
TrivialContainer<ValueType, Allocator>(std::forward<ValueType&&>(value), count){
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType&  LIST_TEMPLATE_RESOLUTION::Append(const ValueType& value) {
	GrowIfToSmall(1);
	std::memcpy(m_data + m_size, std::addressof(value), sizeof(ValueType));
	return m_data[m_size++];
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType&  LIST_TEMPLATE_RESOLUTION::Append(const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& other) {
	GrowIfToSmall(other.Length());
	std::memcpy(m_data + m_size, other.m_data, sizeof(ValueType) * other.Length());
	m_size += other.Length();
	return *this;
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType&  LIST_TEMPLATE_RESOLUTION::Append(TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>&& other) {
	GrowIfToSmall(other.Length());
	memcpy(m_data + m_size, other.m_data, other.Length() * sizeof(ValueType));
	m_size += other.Length();
	return *this;
}

LIST_TEMPLATE_PARAMS
void LIST_TEMPLATE_RESOLUTION::Append(const std::initializer_list<ValueType>& initList) {
	GrowIfToSmall(initList.size());
	for (const auto & iter : initList) {
		m_data[m_size++] = iter;
	}
}

LIST_TEMPLATE_PARAMS
template<typename... CtorArgPack>
ValueType& LIST_TEMPLATE_RESOLUTION::AppendInPlace(CtorArgPack&&... arguments) {
	GrowIfToSmall(1);
	new (std::addressof(m_data[m_size])) ValueType{ std::forward<CtorArgPack&&>(arguments)... };
	return m_data[m_size++];
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE decltype(auto) LIST_TEMPLATE_RESOLUTION::Insert(SizeType index, const ValueType& value) {
	if (index < 0 || index >= Length()) {
		throw std::out_of_range("List Insert Index out of Range!");
	}
	return m_data[index] = value;
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE void LIST_TEMPLATE_RESOLUTION::Remove(SizeType index) {
	if (index < 0 || index >= Length()) {
		throw std::out_of_range("List Insert Index out of Range!");
	}
	std::memmove(std::addressof(m_data[index]) , std::addressof(m_data[index]) + 1, (Length() - index) * sizeof(ValueType));
	--m_size;
}

LIST_TEMPLATE_PARAMS
template<typename... ValueTypes>
void LIST_TEMPLATE_RESOLUTION::AppendRange(ValueTypes&&... values){
	GrowIfToSmall(sizeof...(ValueTypes));
	UnrollAppendRange(std::forward<ValueTypes&&>(values)...);
}

LIST_TEMPLATE_PARAMS
template<typename FirstType, typename... RestValueTypes>
void  LIST_TEMPLATE_RESOLUTION::UnrollAppendRange(FirstType&& firstArg, RestValueTypes&&... restArgs) {
	static_assert(std::is_convertible<FirstType, ValueType>::value,
		"Some Argument in AppendRange could not be converted to the List Type!");
	m_data[m_size++] = static_cast<ValueType>(firstArg);
	UnrollAppendRange(std::forward<RestValueTypes&&>(restArgs)...);
}

LIST_TEMPLATE_PARAMS
template<typename LastType>
void LIST_TEMPLATE_RESOLUTION::UnrollAppendRange(LastType&& lastArg) {
	static_assert(std::is_convertible<LastType, ValueType>::value,
		"Some Argument in AppendRange could not be converted to the List Type!");
	m_data[m_size++] = static_cast<ValueType>(lastArg);
}

LIST_TEMPLATE_PARAMS
template<typename ToType>
void LIST_TEMPLATE_RESOLUTION::ConvertAll(TRIVIAL_LIST_NAME<ToType, Allocator, SFINAE_DUMMY>& outList) const {

	ConvertAll(outList, startIndex);
}

LIST_TEMPLATE_PARAMS
template<typename ToType>
void LIST_TEMPLATE_RESOLUTION::ConvertAll(TRIVIAL_LIST_NAME<ToType, Allocator, SFINAE_DUMMY>& outList, SizeType startIndex) const {
	static_assert(std::is_convertible<ValueType, ToType>::value, "ERROR: Types in ConvertAll are not convertible!");
	if (startIndex < 0 || startIndex >= Length()) {
		throw std::out_of_range("List ConvertAll Index out of Range!");
	}
	outList.Reserve(Length());
	outList.m_size = Length();
	outList.m_capacity = Length();
	std::memcpy(std::addressof(outList.m_data[startIndex]), m_data, Length() * sizeof(ValueType));
}

LIST_TEMPLATE_PARAMS
void LIST_TEMPLATE_RESOLUTION::CopyTo(ValueType* outPtr) const {
	std::memcpy(outPtr, m_data, Length() * sizeof(ValueType));
}

LIST_TEMPLATE_PARAMS
void LIST_TEMPLATE_RESOLUTION::CopyTo(ValueType* outPtr,SizeType startIndex) const {
	if (startIndex < 0 || startIndex >= Length()) {
		throw std::out_of_range("List ConvertAll Index out of Range!");
	}
	std::memcpy(outPtr, std::addressof(m_data[startIndex]), Length() * sizeof(ValueType));
}

LIST_TEMPLATE_PARAMS
gfm::detail::TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& LIST_TEMPLATE_RESOLUTION::operator +=
(const TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& other) {
	Append(other);
	return *this;
}

LIST_TEMPLATE_PARAMS
gfm::detail::TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& LIST_TEMPLATE_RESOLUTION::operator +=
(const std::initializer_list<ValueType>& initList) {
	Append(initList);
	return *this;
}

LIST_TEMPLATE_PARAMS
gfm::detail::TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& LIST_TEMPLATE_RESOLUTION::operator *= (SizeType skalar) {
	if (skalar <= 0) {
		return *this;
	}
	GrowIfToSmall(skalar * Length());
	auto len = Length();
	for (size_t i = len; i < skalar; i += len) {
		std::memcpy(std::addressof(m_data[i]), m_data, sizeof(ValueType) * len);
	}
	return *this;
}

LIST_TEMPLATE_PARAMS
ValueType& LIST_TEMPLATE_RESOLUTION::PopLast() {
	if(m_size == 0) {
		throw std::out_of_range("Can not PopLast on an Empty List!");
	}
	return m_data[--m_size];
}

LIST_TEMPLATE_PARAMS
const ValueType& LIST_TEMPLATE_RESOLUTION::Last() const {
	if(m_size == 0) {
		throw std::out_of_range("Last Cannot be called when List is Empty!");
	}
	return m_data[m_size - 1];
}

LIST_TEMPLATE_PARAMS
ValueType& LIST_TEMPLATE_RESOLUTION::Last() {
	if(m_size == 0) {
		throw std::out_of_range("Last Cannot be called when List is Empty!");
	}
	return m_data[m_size - 1];
}

LIST_TEMPLATE_PARAMS
void LIST_TEMPLATE_RESOLUTION::ForEach(void(*predicate)(ValueType&)) {
	for(auto& it : *this) {
		predicate(it);
	}
}

LIST_TEMPLATE_PARAMS
void LIST_TEMPLATE_RESOLUTION::ForEach(void(*predicate)(const ValueType&)) const {
	for(const auto& it : this) {
		predicate(it);
	}
}

LIST_TEMPLATE_PARAMS
bool LIST_TEMPLATE_RESOLUTION::operator != (const gfm::detail::TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& other) {
	return !(*this == other);
}

LIST_TEMPLATE_PARAMS
bool LIST_TEMPLATE_RESOLUTION::operator == (const gfm::detail::TRIVIAL_LIST_NAME<ValueType, Allocator, SFINAE_DUMMY>& other) {
	return Length() == other.Length() && Equals(other);
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE ValueType* LIST_TEMPLATE_RESOLUTION::begin() noexcept {
	return m_data;
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE const ValueType* LIST_TEMPLATE_RESOLUTION::cbegin() const noexcept {
	return m_data;
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE ValueType* LIST_TEMPLATE_RESOLUTION::end() noexcept {
	return m_data + m_size;
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE const ValueType* LIST_TEMPLATE_RESOLUTION::cend() const noexcept {
	return m_data + m_size;
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType* LIST_TEMPLATE_RESOLUTION::end() const noexcept {
	return cend();
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType* LIST_TEMPLATE_RESOLUTION::begin() const noexcept {
	return cbegin();
}

#undef LIST_TEMPLATE_PARAMS
#undef LIST_TEMPLATE_RESOLUTION
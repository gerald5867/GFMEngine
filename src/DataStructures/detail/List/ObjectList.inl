#pragma once

#define LIST_TEMPLATE_PARAMS \
	template<typename ValueType, typename Allocator>

#define LIST_TEMPLATE_RESOLUTION \
	gfm::detail::OBJECT_LIST<ValueType, Allocator, typename std::enable_if<!std::is_trivial<ValueType>::value>::type>

LIST_TEMPLATE_PARAMS
LIST_TEMPLATE_RESOLUTION::OBJECT_LIST(const std::initializer_list<ValueType>& initList) :
	OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>(initList) {
}

LIST_TEMPLATE_PARAMS
LIST_TEMPLATE_RESOLUTION::OBJECT_LIST(SizeType valueCount) :
	OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>(valueCount) {
}

LIST_TEMPLATE_PARAMS
LIST_TEMPLATE_RESOLUTION::OBJECT_LIST(ValueType&& value, SizeType count) :
	OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>(std::forward<ValueType&&>(value), count) {
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType& LIST_TEMPLATE_RESOLUTION::Append(const ValueType& value) {
	GrowIfToSmall(1);
	new (std::addressof(m_data[m_size])) ValueType(value);
	return m_data[m_size++];
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE gfm::detail::OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>&
LIST_TEMPLATE_RESOLUTION::Append(const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& other) {
	GrowIfToSmall(other.Length());
	for (SizeType i = 0; i < other.m_size; ++i) {
		new (std::addressof(m_data[m_size + i])) ValueType(other.m_data[i]);
	}
	m_size += other.Length();
	return *this;
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE gfm::detail::OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& 
LIST_TEMPLATE_RESOLUTION::Append(OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>&& other) {
	GrowIfToSmall(other.Length());
	for (SizeType i = 0; i < other.m_size; ++i) {
		new (std::addressof(m_data[m_size + i])) ValueType(std::move(other.m_data[i]));
	}
	m_size += other.Length();
	return *this;
}

LIST_TEMPLATE_PARAMS
void LIST_TEMPLATE_RESOLUTION::Append(const std::initializer_list<ValueType>& initList) {
	GrowIfToSmall(initList.size());
	for (const auto & iter : initList) {
		new (std::addressof(m_data[m_size++])) ValueType(iter);
	}
}

LIST_TEMPLATE_PARAMS
template<typename... CtorArgPack>
void LIST_TEMPLATE_RESOLUTION::AppendInPlace(CtorArgPack&&... arguments) {
	GrowIfToSmall(1);
	new (std::addressof(m_data[m_size++])) ValueType(std::forward<CtorArgPack&&>(arguments)...);
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE decltype(auto) LIST_TEMPLATE_RESOLUTION::Insert(SizeType index, const ValueType& value) {
	if (index < 0 || index >= Length()) {
		throw std::out_of_range("List Insert Index out of Range!");
	}
	new (std::addressof(m_data[m_size])) ValueType(value);
	return m_data[m_size++];
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE void LIST_TEMPLATE_RESOLUTION::Remove(SizeType index) {
	if (index < 0 || index >= Length()) {
		throw std::out_of_range("List Insert Index out of Range!");
	}
	m_data[index].~ValueType();
	for (SizeType i = index ; i++ i < Length() - 1; i++) {
		new (std::addressof(m_data[i])) ValueType(std::move(m_data[i + 1]));
	}
	--m_size;
}

LIST_TEMPLATE_PARAMS
template<typename... ValueTypes>
void LIST_TEMPLATE_RESOLUTION::AppendRange(ValueTypes&&... values) {
	GrowIfToSmall(sizeof...(ValueTypes));
	UnrollAppendRange(std::forward<ValueTypes&&>(values)...);
}

LIST_TEMPLATE_PARAMS
template<typename FirstType, typename... RestValueTypes>
void  LIST_TEMPLATE_RESOLUTION::UnrollAppendRange(FirstType&& firstArg, RestValueTypes&&... restArgs) {
	static_assert(std::is_convertible<FirstType, ValueType>::value, 
		"Some Argument in AppendRange could not be converted to the List Type!");
	new (std::addressof(m_data[m_size++])) ValueType(std::forward<FirstType&&>(firstArg));
	UnrollAppendRange(std::forward<RestValueTypes&&>(restArgs)...);
}

LIST_TEMPLATE_PARAMS
template<typename LastType>
void LIST_TEMPLATE_RESOLUTION::UnrollAppendRange(LastType&& lastArg) {
	static_assert(std::is_convertible<FirstType, ValueType>::value, 
		"Some Argument in AppendRange could not be converted to the List Type!");
	new (std::addressof(m_data[m_size++])) ValueType(std::forward<FirstType&&>(firstArg));
}

LIST_TEMPLATE_PARAMS
template<typename ToType>
void LIST_TEMPLATE_RESOLUTION::ConvertAll(OBJECT_LIST < ToType, Allocator, SFINAE_DUMMY > & outList) const {
	ConvertAll(outList, startIndex);
}

LIST_TEMPLATE_PARAMS
template<typename ToType>
void LIST_TEMPLATE_RESOLUTION::ConvertAll(OBJECT_LIST < ToType, Allocator, SFINAE_DUMMY  > & outList, SizeType startIndex) const {
	static_assert(std::is_convertible<ValueType, ToType>::value, "ERROR: Types in ConvertAll are not convertible!");
	if (startIndex < 0 || startIndex >= Length()) {
		throw std::out_of_range("List ConvertAll Index out of Range!");
	}
	outList.Reserve(Length());
	outList.m_size = Length();
	outList.m_capacity = Length();
	for (SizeType i = 0; i < Length(); i++) {
		new (std::addressof(outList.m_data[i])) ValueType(m_data[i]);
	}
}

LIST_TEMPLATE_PARAMS
void LIST_TEMPLATE_RESOLUTION::CopyTo(ValueType* outPtr) const {
	for (SizeType i = 0; i < Length(); i++) {
		new (std::addressof(outPtr[i])) ValueType(m_data[i]);
	}
}

LIST_TEMPLATE_PARAMS
void LIST_TEMPLATE_RESOLUTION::CopyTo(ValueType* outPtr, SizeType startIndex) const {
	if (startIndex < 0 || startIndex >= Length()) {
		throw std::out_of_range("List ConvertAll Index out of Range!");
	}
	for (SizeType i = startIndex; i < Length(); i++) {
		new (std::addressof(outPtr[i - startIndex])) ValueType(m_data[i]);
	}
}

LIST_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType& LIST_TEMPLATE_RESOLUTION::Append(ValueType&& value) {
	GrowIfToSmall(1);
	new (std::addressof(m_data[m_size])) ValueType(std::move(value));
	return m_data[m_size++];
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
void LIST_TEMPLATE_RESOLUTION::PopLast() {
	if(m_size == 0) {
		return;
	}
	m_data[--m_size].~ValueType();
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
gfm::detail::OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& LIST_TEMPLATE_RESOLUTION::operator += 
(const OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& other) {
	Append(other);
	return *this;
}

LIST_TEMPLATE_PARAMS
gfm::detail::OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& LIST_TEMPLATE_RESOLUTION::operator += 
(const std::initializer_list<ValueType>& initList) {
	Append(initList);
	return *this;
}

LIST_TEMPLATE_PARAMS
gfm::detail::OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& LIST_TEMPLATE_RESOLUTION::operator *= (SizeType skalar) {
	if (skalar <= 0) {
		return *this;
	}
	auto len = Length();
	GrowIfToSmall(skalar * len);
	SizeType i = 0;
	do {
		for (i = 0; i < len; ++i) {
			new (std::addressof(m_data[m_size++])) ValueType(m_data[i]);
		}
	} while (m_size < (skalar * len));
	return *this;
}

LIST_TEMPLATE_PARAMS
bool LIST_TEMPLATE_RESOLUTION::operator != (const gfm::detail::OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& other) {
	return !(*this == other);
}

LIST_TEMPLATE_PARAMS
bool LIST_TEMPLATE_RESOLUTION::operator == (const gfm::detail::OBJECT_LIST<ValueType, Allocator, SFINAE_DUMMY>& other) {
	return Length() == other.Length() && Equals(other);
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType* LIST_TEMPLATE_RESOLUTION::begin() noexcept {
	return m_data;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType* LIST_TEMPLATE_RESOLUTION::cbegin() const noexcept {
	return m_data;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType* LIST_TEMPLATE_RESOLUTION::end() noexcept {
	return m_data + m_size;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType* LIST_TEMPLATE_RESOLUTION::cend() const noexcept {
	return m_data + m_size;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType* LIST_TEMPLATE_RESOLUTION::end() const noexcept {
	return cend();
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType* LIST_TEMPLATE_RESOLUTION::begin() const noexcept {
	return cbegin();
}
#undef LIST_TEMPLATE_PARAMS
#undef LIST_TEMPLATE_RESOLUTION
/*
#define CONTAINER_TEMPLATE_PARAMS \
	template<typename ValueType, typename Allocator>

#define CONTAINER_TEMPLATE_RESOLUTION \
	gfm::detail::ObjectContainer<ValueType, Allocator>

CONTAINER_TEMPLATE_PARAMS
CONTAINER_TEMPLATE_RESOLUTION::ObjectContainer() :
	m_capacity(0), m_size(0), m_data(nullptr) {
}

CONTAINER_TEMPLATE_PARAMS
CONTAINER_TEMPLATE_RESOLUTION::ObjectContainer(SizeType valueCount) :
	m_capacity(valueCount) {
	m_data = static_cast<ValueType*>(m_allocator.Allocate(valueCount * sizeof(ValueType)));
	while (m_size != valueCount) {
		new (std::addressof(m_data[m_size++])) ValueType();
	}
}

CONTAINER_TEMPLATE_PARAMS
CONTAINER_TEMPLATE_RESOLUTION::ObjectContainer(const ObjectContainer<ValueType, Allocator>& other) :
	m_capacity(other.m_capacity) {
	m_data = static_cast<ValueType*>(m_allocator.Allocate(other.m_capacity * sizeof(ValueType)));
	while (m_size != other.m_size) {
		new (std::addressof(m_data[m_size])) ValueType(other.m_data[m_size]);
		m_size++;
	}
}

CONTAINER_TEMPLATE_PARAMS
CONTAINER_TEMPLATE_RESOLUTION::ObjectContainer(ObjectContainer<ValueType, Allocator>&& other) :
	m_capacity(other.m_capacity), m_size(other.m_size), m_data(other.m_data) {
	other.m_data = nullptr;
	other.m_size = 0;
	other.m_capacity = 0;
}

CONTAINER_TEMPLATE_PARAMS
CONTAINER_TEMPLATE_RESOLUTION::ObjectContainer(const ValueType& value, SizeType count) :
	m_capacity(count), m_size(count) {
	m_data = static_cast<ValueType*>(m_allocator.Allocate(m_capacity * sizeof(ValueType)));
	while (count-- != 0) {
		new (std::addressof(m_data[count])) ValueType(value);
	}
}

CONTAINER_TEMPLATE_PARAMS
CONTAINER_TEMPLATE_RESOLUTION::~ObjectContainer() noexcept {
	Clear();
	utils::SaveReleaseArray(m_data);
	m_capacity = 0;
}

CONTAINER_TEMPLATE_PARAMS
CONTAINER_TEMPLATE_RESOLUTION& CONTAINER_TEMPLATE_RESOLUTION::operator = (const ObjectContainer<ValueType, Allocator>& other) {
	if (this != &other) {
		if (m_capacity < other.size) {
			Allocator.Deallocate(m_data);
			m_data = Allocator.Allocate(other.m_capacity * sizeof(ValueType));
		}
		m_size = other.m_size;
		for (SizeType i = 0; i < m_size; i++) {
			new (std::addressof(m_data[i])) ValueType(other.m_data[i]);
		}
	}
	return *this;
}

CONTAINER_TEMPLATE_PARAMS
CONTAINER_TEMPLATE_RESOLUTION& CONTAINER_TEMPLATE_RESOLUTION::operator = (ObjectContainer<ValueType, Allocator>&& other) {
	if (this != &other) {
		utils::SaveReleaseArray(m_data);
		m_capacity = other.m_capacity;
		m_size = other.m_size;
		m_data = other.m_data;
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}
	return *this;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType& CONTAINER_TEMPLATE_RESOLUTION::operator[]
(typename CONTAINER_TEMPLATE_RESOLUTION::SizeType index) {
	if (index < 0 || index >= m_size) {
		throw std::out_of_range("ObjectContainer Operator[] Index was Out of Range !");
	}
	return m_data[index];
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType& CONTAINER_TEMPLATE_RESOLUTION::operator[]
(typename CONTAINER_TEMPLATE_RESOLUTION::SizeType index) const {
	if (index < 0 || index >= m_size) {
		throw std::out_of_range("ObjectContainer Operator[] Index was Out of Range !");
	}
	return m_data[index];
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE typename CONTAINER_TEMPLATE_RESOLUTION::SizeType
CONTAINER_TEMPLATE_RESOLUTION::Length() const noexcept {
	return m_size;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE typename CONTAINER_TEMPLATE_RESOLUTION::SizeType
CONTAINER_TEMPLATE_RESOLUTION::Capacity() const noexcept {
	return m_capacity;
}
CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType* CONTAINER_TEMPLATE_RESOLUTION::Raw() noexcept {
	return m_data;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType* CONTAINER_TEMPLATE_RESOLUTION::Raw() const noexcept {
	return m_data;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType* CONTAINER_TEMPLATE_RESOLUTION::begin() noexcept {
	return m_data;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType* CONTAINER_TEMPLATE_RESOLUTION::cbegin() const noexcept {
	return m_data;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE ValueType* CONTAINER_TEMPLATE_RESOLUTION::end() noexcept {
	return m_data + m_size;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE const ValueType* CONTAINER_TEMPLATE_RESOLUTION::cend() const noexcept {
	return m_data + m_size;
}

CONTAINER_TEMPLATE_PARAMS
void CONTAINER_TEMPLATE_RESOLUTION::Clear() noexcept {
	for (SizeType i = 0; i < m_size; i++) {
		(std::addressof(m_data[i]))->~ValueType();
	}
	m_size = 0;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE void CONTAINER_TEMPLATE_RESOLUTION::CopyDataTo(ValueType* newPtr) {
	if (m_data != nullptr) {
		for (SizeType i = 0; i < m_size; i++) {
			new (std::addressof(newPtr[i])) ValueType(m_data[i]);
		}
		m_allocator.Deallocate(m_data);
	}
	m_data = newPtr;
}

CONTAINER_TEMPLATE_PARAMS
void CONTAINER_TEMPLATE_RESOLUTION::Resize(SizeType size) {
	if (m_size >= size) {
		return;
	}
	if (size > m_capacity) {
		auto * temp = static_cast<ValueType*>(m_allocator.Allocate(size * sizeof(ValueType)));
		CopyDataTo(temp);
		m_capacity = size;
	}
	for (SizeType i = m_size; i < size; i++) {
		new (std::addressof(m_data[i])) ValueType();
	}
	m_size = size;
}

CONTAINER_TEMPLATE_PARAMS
void CONTAINER_TEMPLATE_RESOLUTION::Reserve(SizeType size) {
	if (m_capacity > size) {
		return;
	}
	auto * temp = static_cast<ValueType*>(m_allocator.Allocate(size * sizeof(ValueType)));
	CopyDataTo(temp);
	m_capacity = size;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE bool CONTAINER_TEMPLATE_RESOLUTION::Empty() const noexcept {
	return m_data == nullptr || m_size == 0;
}

CONTAINER_TEMPLATE_PARAMS
GFM_BEST_INLINE void CONTAINER_TEMPLATE_RESOLUTION::GrowIfToSmall(SizeType toAddCount) {
	if (toAddCount + m_size >= m_capacity) {
		if (toAddCount > m_capacity * 2) {
			m_capacity = toAddCount;
		}
		else {
			m_capacity *= 2;
		}
		auto * temp = static_cast<ValueType*>(m_allocator.Allocate(m_capacity * sizeof(ValueType)));
		CopyDataTo(temp);
	}
}

CONTAINER_TEMPLATE_PARAMS
bool CONTAINER_TEMPLATE_RESOLUTION::Contains(const ValueType& val) const {
	for (SizeType i = 0; i < val; ++i) {
		if (val == m_data[i]) {
			return true;
		}
	}
	return false;
}


#undef LIST_TEMPLATE_PARAMS
#undef LIST_TEMPLATE_RESOLUTION
*/
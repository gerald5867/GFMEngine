#pragma once
#define CONTAINER_TEMPLATE_PARAMS \
	template<typename ValueType, typename Allocator>

#define CONTAINER_TEMPLATE_RESOLUTION \
	gfm::detail::TrivialContainer<ValueType, Allocator>

template<typename ValueType, typename Allocator>
CONTAINER_TEMPLATE_RESOLUTION::TrivialContainer(const std::initializer_list<ValueType>& initList) :
	m_capacity(initList.size()), m_size(initList.size()) {
	m_data = static_cast<ValueType*>(m_allocator.Allocate(m_capacity * sizeof(ValueType)));
	utils::uint32 i = 0;
	for (const auto & iter : initList) {
		m_data[i++] = iter;
	}

}

template<typename ValueType, typename Allocator>
CONTAINER_TEMPLATE_RESOLUTION::TrivialContainer() :
	m_capacity(0), m_size(0), m_data(nullptr) {
}

template<typename ValueType, typename Allocator>
CONTAINER_TEMPLATE_RESOLUTION::TrivialContainer(SizeType valueCount) :
	m_capacity(valueCount), m_size(valueCount) {
	m_data = static_cast<ValueType*>(m_allocator.Allocate(valueCount * sizeof(ValueType)));
	memset(m_data, 0, sizeof(ValueType) * m_capacity);
}

template<typename ValueType, typename Allocator>
CONTAINER_TEMPLATE_RESOLUTION::TrivialContainer(const TrivialContainer<ValueType, Allocator>& other) :
	m_capacity(other.m_capacity), m_size(other.m_size) {
	m_data = static_cast<ValueType*>(m_allocator.Allocate(other.m_capacity * sizeof(ValueType)));
	memcpy(m_data, other.m_data, sizeof(ValueType) * other.Length());
}

template<typename ValueType, typename Allocator>
CONTAINER_TEMPLATE_RESOLUTION::TrivialContainer(TrivialContainer<ValueType, Allocator>&& other) :
	m_capacity(other.m_capacity), m_size(other.m_size), m_data(other.m_data) {
	other.m_data = nullptr;
	other.m_size = 0;
	other.m_capacity = 0;
}

template<typename ValueType, typename Allocator>
CONTAINER_TEMPLATE_RESOLUTION::TrivialContainer(const ValueType& value, SizeType count) :
	m_capacity(count), m_size(count) {
	m_data = static_cast<ValueType*>(m_allocator.Allocate(m_capacity * sizeof(ValueType)));
	while (count-- != 0) {
		m_data[count] = value;
	}
}

template<typename ValueType, typename Allocator>
CONTAINER_TEMPLATE_RESOLUTION::~TrivialContainer() noexcept {
	memset(m_data, 0, sizeof(ValueType) * m_size);
	utils::SaveReleaseArray(m_data);
	m_size = 0;
	m_capacity = 0;
}

template<typename ValueType, typename Allocator>
CONTAINER_TEMPLATE_RESOLUTION& CONTAINER_TEMPLATE_RESOLUTION::operator = (const TrivialContainer<ValueType, Allocator>& other) {
	if (this != &other) {
		if (m_capacity < other.m_size) {
			m_allocator.Deallocate(m_data);
			m_data = static_cast<ValueType*>(m_allocator.Allocate(other.m_capacity * sizeof(ValueType)));
		}
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		std::memcpy(m_data, other.m_data, sizeof(ValueType) * other.Length());
	}
	return *this;
}

template<typename ValueType, typename Allocator>
CONTAINER_TEMPLATE_RESOLUTION& CONTAINER_TEMPLATE_RESOLUTION::operator = (TrivialContainer<ValueType, Allocator>&& other) {
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

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE ValueType& CONTAINER_TEMPLATE_RESOLUTION::operator[]
(typename CONTAINER_TEMPLATE_RESOLUTION::SizeType index) {
	if (index < 0 || index >= m_size) {
		throw std::out_of_range("TrivialContainer Operator[] Index was Out of Range !");
	}
	return m_data[index];
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE const ValueType& CONTAINER_TEMPLATE_RESOLUTION::operator[]
(typename CONTAINER_TEMPLATE_RESOLUTION::SizeType index) const {
	if (index < 0 || index >= m_size) {
		throw std::out_of_range("TrivialContainer Operator[] Index was Out of Range !");
	}
	return m_data[index];
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE typename CONTAINER_TEMPLATE_RESOLUTION::SizeType
CONTAINER_TEMPLATE_RESOLUTION::Length() const noexcept {
	return m_size;
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE typename CONTAINER_TEMPLATE_RESOLUTION::SizeType
CONTAINER_TEMPLATE_RESOLUTION::Capacity() const noexcept {
	return m_capacity;
}
template<typename ValueType, typename Allocator>
GFM_BEST_INLINE ValueType* CONTAINER_TEMPLATE_RESOLUTION::Raw() noexcept {
	return m_data;
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE const ValueType* CONTAINER_TEMPLATE_RESOLUTION::Raw() const noexcept {
	return m_data;
}

template<typename ValueType, typename Allocator>
void CONTAINER_TEMPLATE_RESOLUTION::Clear() noexcept {
	memset(m_data, 0, sizeof(ValueType) * m_size);
	m_size = 0;
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE void CONTAINER_TEMPLATE_RESOLUTION::CopyDataTo(ValueType* newPtr) {
	if (m_data != nullptr) {
		memcpy(newPtr, m_data, m_size * sizeof(ValueType));
		m_allocator.Deallocate(m_data);
	}
	m_data = newPtr;
}

template<typename ValueType, typename Allocator>
void CONTAINER_TEMPLATE_RESOLUTION::Resize(SizeType size) {
	if (m_size >= size) {
		return;
	}
	if (size > m_capacity) {
		auto * temp = static_cast<ValueType*>(m_allocator.Allocate(size * sizeof(ValueType)));
		CopyDataTo(temp);
		m_capacity = size;
	}
	std::memset(std::addressof(m_data[m_size]), 0, (size - m_size) * sizeof(ValueType));
	m_size = size;
}

template<typename ValueType, typename Allocator>
void CONTAINER_TEMPLATE_RESOLUTION::Reserve(SizeType size) {
	if (m_capacity > size) {
		return;
	}
	auto * temp = static_cast<ValueType*>(m_allocator.Allocate(size * sizeof(ValueType)));
	CopyDataTo(temp);
	m_capacity = size;
}

template<typename ValueType, typename Allocator>
GFM_BEST_INLINE bool CONTAINER_TEMPLATE_RESOLUTION::Empty() const noexcept {
	return m_data == nullptr || m_size == 0;
}

template<typename ValueType, typename Allocator>
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

template<typename ValueType, typename Allocator>
bool CONTAINER_TEMPLATE_RESOLUTION::Contains(const ValueType& val) const {
	for (SizeType i = 0; i < val; ++i) {
		if (m_data[i] == val) {
			return true;
		}
	}
	return false;
}

CONTAINER_TEMPLATE_PARAMS
bool CONTAINER_TEMPLATE_RESOLUTION::Equals(const TrivialContainer<ValueType, Allocator>& other) {
	for (SizeType i = 0; i < Length(); ++i) {
		if (m_data[i] != other.m_data[i]) {
			return false;
		}
	}
	return true;
}

#undef CONTAINER_TEMPLATE_PARAMS
#undef CONTAINER_TEMPLATE_RESOLUTION
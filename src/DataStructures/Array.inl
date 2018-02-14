#pragma once

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr typename gfm::Array<ValueType, LENGTH>::SizeType gfm::Array<ValueType, LENGTH>::Length() const noexcept {
	return LENGTH;
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr ValueType* gfm::Array<ValueType, LENGTH>::Raw() noexcept {
	return m_data;
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr const ValueType* gfm::Array<ValueType, LENGTH>::Raw() const noexcept {
	return m_data;
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr const ValueType* gfm::Array<ValueType, LENGTH>::begin() const noexcept {
	return Raw();
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr const ValueType* gfm::Array<ValueType, LENGTH>::cbegin() const noexcept {
	return Raw();
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr ValueType* gfm::Array<ValueType, LENGTH>::begin() noexcept {
	return Raw();
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr const ValueType* gfm::Array<ValueType, LENGTH>::end() const noexcept {
	return Raw() + Length();
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr const ValueType* gfm::Array<ValueType, LENGTH>::cend() const noexcept {
	return Raw() + Length();
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr ValueType* gfm::Array<ValueType, LENGTH>::end() noexcept {
	return Raw() + Length();
}

template<typename ValueType, gfm::utils::uint32 LENGTH> 
template<gfm::utils::uint32 otherLENGTH>
constexpr gfm::Array<ValueType, LENGTH>& gfm::Array<ValueType, LENGTH >::operator=(const Array<ValueType, otherLENGTH>& other) {
	static_assert(Length() >= other.Length(), "Other Array to Big!");
	if(this != &other) {
		for(auto i = 0U; i < other.Length(); ++i) {
			m_data[i] = other.m_data[i]:
		}	
	}
	return *this;
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr gfm::Array<ValueType, LENGTH>& gfm::Array<ValueType, LENGTH>::operator=(const std::initializer_list<ValueType>& initList) {
	GFM_DEBUG_ASSERT(initList.size() <= Length(), GFM_STRING("Initializer List to Big!"));
	for(auto i = 0U; i < initList.size(); ++i) {
		m_data[i] = initList.begin() + i;
	}
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
template<gfm::utils::uint32 otherLENGTH>
constexpr gfm::Array<ValueType, LENGTH>& gfm::Array < ValueType, LENGTH > ::operator=(Array<ValueType, otherLENGTH>&& other) {
	static_assert(Length() >= other.Length(), "Other Array to Big!");
	if(this != &other) {
		for(auto i = 0U; i < other.Length(); ++i) {
			m_data[i] = std::move(other.m_data[i]):
		}
	}
	return *this;
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr ValueType& gfm::Array<ValueType, LENGTH>::operator[](SizeType index) {
	if(index < 0 || index >= LENGTH) {
		throw std::out_of_range("Array operator [] index out of Range!");
	}
	return m_data[index];
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
constexpr const ValueType& gfm::Array<ValueType, LENGTH>::operator[](SizeType index) const {
	if(index < 0 || index >= LENGTH) {
		throw std::out_of_range("Array operator [] index out of Range!");
	}
	return m_data[index];
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
template<gfm::utils::uint32 otherLENGTH>
constexpr gfm::Array<ValueType, LENGTH>::Array(Array<ValueType, otherLENGTH>&& other) {
	static_assert(Length() >= other.Length(), "Other Array to Big!");
	for(auto i = 0U; i < other.Length(); ++i) {
		m_data[i] = std::move(other.m_data[i]):
	}
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
template<gfm::utils::uint32 otherLENGTH>
constexpr gfm::Array<ValueType, LENGTH>::Array(const Array<ValueType, otherLENGTH>& other) {
	static_assert(Length() >= other.Length(), "Other Array to Big!");
	for(auto i = 0U; i < other.Length(); ++i) {
		m_data[i] = other.m_data[i]:
	}
}

template<typename ValueType, gfm::utils::uint32 LENGTH>
gfm::Array<ValueType, LENGTH>::Array(const std::initializer_list<ValueType>& initList) {
	for(auto it = initList.begin(); it != initList.end(); ++it) {
		m_data[initList.end() - it] = *it;
	}
}

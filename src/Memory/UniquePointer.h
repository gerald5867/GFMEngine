#pragma once
#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <type_traits>
#include "../utils/Types.h"
#include "../Utils/SaveRelease.h"
#include "DefaultDestroyer.h"
namespace gfm {
namespace memory {

template<typename T, typename Destroyer = ObjectDestroyer>
class UniquePointer final
{
public:
	template<typename... CtorArgTypes>
	friend UniquePointer<T, Destroyer> MakeUnique(CtorArgTypes&&... arguments);
	template<typename T>
	friend UniquePointer<T, Destroyer> MakeUniqueBytes(utils::uint32 size);
	template<typename... CtorArgTypes>
	friend UniquePointer<T, Destroyer> MakeUniqueArray(utils::uint32 count, CtorArgTypes&&... arguments);

	UniquePointer(const UniquePointer&)			    = delete;
	UniquePointer& operator =(const UniquePointer&) = delete;

	UniquePointer<T, Destroyer>(UniquePointer<T, Destroyer>&& other);
	UniquePointer<T, Destroyer>& operator =(UniquePointer<T, Destroyer>&& other);
	UniquePointer <T, Destroyer>& operator =(T* ptr);
	~UniquePointer();
	explicit UniquePointer<T, Destroyer>(T* ptr);
	UniquePointer() = default;

public:
	GFM_BEST_INLINE T* Raw() noexcept;
	GFM_BEST_INLINE const T* Raw() const noexcept;

	GFM_BEST_INLINE const T& operator *() const;
	GFM_BEST_INLINE T& operator *();

	GFM_BEST_INLINE const T* operator ->() const;
	GFM_BEST_INLINE T* operator ->();

	GFM_BEST_INLINE explicit operator bool() const noexcept;
 private:

	T* m_data = nullptr;
	Destroyer m_destroyer;
};

}//memory
}//gfm
template<typename T, typename Destroyer>
gfm::memory::UniquePointer<T, Destroyer>::UniquePointer(UniquePointer<T, Destroyer>&& other) :
	m_data(other.m_data), m_destroyer(other.m_destroyer) {
	other.m_data = nullptr;
}

template<typename T, typename Destroyer>
gfm::memory::UniquePointer<T, Destroyer>& 
gfm::memory::UniquePointer<T, Destroyer>::operator =(UniquePointer<T, Destroyer>&& other) {
	if(this != &other) {
		m_data = other.m_data;
		other.m_data = nullptr;
		m_destroyer = other.m_destroyer;
	}
	return *this;
}

template<typename T, typename Destroyer>
gfm::memory::UniquePointer <T, Destroyer>& gfm::memory::UniquePointer <T, Destroyer>::operator = (T* ptr) {
	if(m_data != nullptr) {
		m_destroyer.Destroy(m_data);
	}
	m_data = ptr;
	return *this;
}

template<typename T, typename Destroyer>
gfm::memory::UniquePointer<T, Destroyer>::~UniquePointer() {
	if(m_data != nullptr) {
		m_destroyer.Destroy(m_data);
		m_data = nullptr;
	}
}

template<typename T, typename Destroyer>
gfm::memory::UniquePointer<T, Destroyer>::UniquePointer(T* ptr) {
	m_data = std::move(ptr);
}

template<typename T, typename Destroyer>
GFM_BEST_INLINE T* gfm::memory::UniquePointer<T, Destroyer>::Raw() noexcept {
	return m_data;
}

template<typename T, typename Destroyer>
GFM_BEST_INLINE const T* gfm::memory::UniquePointer<T, Destroyer>::Raw() const noexcept {
	return m_data;
}

template<typename T, typename Destroyer>
GFM_BEST_INLINE const T& gfm::memory::UniquePointer<T, Destroyer>::operator *() const {
	return *m_data;
}

template<typename T, typename Destroyer>
GFM_BEST_INLINE T& gfm::memory::UniquePointer<T, Destroyer>::operator *() {
	return *m_data;
}

template<typename T, typename Destroyer>
GFM_BEST_INLINE const T* gfm::memory::UniquePointer<T, Destroyer>::operator ->() const {
	return m_data;
}

template<typename T, typename Destroyer>
GFM_BEST_INLINE T* gfm::memory::UniquePointer<T, Destroyer>::operator ->() {
	return m_data;
}

template<typename T, typename Destroyer>
GFM_BEST_INLINE gfm::memory::UniquePointer<T, Destroyer>::operator bool() const noexcept {
	return m_data != nullptr;
}

#endif //UNIQUE_PTR_H
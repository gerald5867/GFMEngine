#pragma once 
#include <type_traits>
#include "../Utils/Types.h"
#include "../Macro/BestInline.h"
namespace gfm 
{
namespace memory 
{
	class DefaultAllocator final
	{
	public:
		static GFM_BEST_INLINE decltype(auto) Allocate(utils::uint32 size) {
			return ::operator new(size);
		}

		template<typename T>
		static GFM_BEST_INLINE void Deallocate(T* ptr) {
			::operator delete[](ptr);
		}

		template<typename T, typename... CtorTypes>
		static GFM_BEST_INLINE decltype(auto) AllocateObject(CtorTypes&&... arguments) {
			return new T(std::forward<CtorTypes&&>(arguments)...);
		}

		template<typename T>
		static GFM_BEST_INLINE void DeallocateObject(T* ptr) {
			::delete ptr;
		}

		template<typename T, typename... CtorTypes>
		static GFM_BEST_INLINE decltype(auto) AllocateObjectArray(utils::uint32 count, CtorTypes&&... arguments) {
			return ::new T[count](std::forward<CtorTypes&&>(arguments)...);
		}

		template<typename T>
		static GFM_BEST_INLINE void DeallocateObjectArray(T* ptr) {
			::delete[] ptr;
		}

	};
}//namepsace memory
}//namespace gfm
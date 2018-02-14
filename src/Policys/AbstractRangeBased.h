#pragma once
namespace gfm {
namespace policy {
namespace detail {
	template<typename ValueType>
	class AbstractRangeBased
	{
	public:
		virtual ValueType* begin() noexcept = 0;
		virtual ValueType* end() noexcept = 0;
		virtual const ValueType* cbegin() const noexcept = 0;
		virtual const ValueType* cend() const noexcept = 0;
		virtual const ValueType* begin() const noexcept = 0;
		virtual const ValueType* end() const noexcept = 0;
	};
}//detail
}//policy
}//gfm
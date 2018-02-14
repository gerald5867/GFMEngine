#pragma once
namespace gfm
{
namespace traits
{
	template<typename T, std::size_t Size>
	static constexpr std::size_t ArrayLen(T(&)[Size]) noexcept {
		return Size;
	}

}//namespace utils
}//namespace gfm
#pragma once
#ifndef NON_MOVEABLE_H
#define NON_MOVEABLE_H
namespace gfm {
namespace policy {
class Nonmoveable
{
	public:
		Nonmoveable() = default;
		Nonmoveable(Nonmoveable&&)			    = delete;
		Nonmoveable& operator = (Nonmoveable&&) = delete;
};
}//policy
}//gfm
#endif // NON_MOVEABLE_H
#pragma once
#ifndef NON_COPYABLE_H
#define NON_COPYABLE_H
namespace gfm {
namespace policy {
	class Noncopyable 
	{
		public:
			Noncopyable() = default;
			Noncopyable(const Noncopyable& )			 = delete;
			Noncopyable& operator = (const Noncopyable&) = delete;
	};
}//policy
}//gfm
#endif // NON_COPYABLE_H
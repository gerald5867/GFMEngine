#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H
#include "../Macro/BestInline.h"

namespace gfm
{
namespace policy {

	template<typename ClassType>
	class MakeThreadLocalSingletonPtr
	{
	public:
		static GFM_BEST_INLINE ClassType & instance() noexcept {
			return *mp_instance;
		}

		MakeThreadLocalSingletonPtr(MakeThreadLocalSingletonPtr &&) = delete;
		MakeThreadLocalSingletonPtr(const MakeThreadLocalSingletonPtr &) = delete;
		MakeThreadLocalSingletonPtr & operator = (MakeThreadLocalSingletonPtr &&) = delete;
		MakeThreadLocalSingletonPtr & operator = (const MakeThreadLocalSingletonPtr &) = delete;

	protected:
		~MakeThreadLocalSingletonPtr() = default;
		MakeThreadLocalSingletonPtr() = default;
		thread_local static ClassType* mp_instance;
	};


	template<typename ClassType>
	class MakeThreadLocalSingletonStatic
	{
	public:
		static GFM_BEST_INLINE ClassType & instance() noexcept {
			thread_local static ClassType instance;
			return instance;
		}

		MakeThreadLocalSingletonStatic(MakeThreadLocalSingletonStatic &&) = delete;
		MakeThreadLocalSingletonStatic(const MakeThreadLocalSingletonStatic &) = delete;
		MakeThreadLocalSingletonStatic & operator = (MakeThreadLocalSingletonStatic &&) = delete;
		MakeThreadLocalSingletonStatic & operator = (const MakeThreadLocalSingletonStatic &) = delete;

	protected:
		~MakeThreadLocalSingletonStatic() = default;
		MakeThreadLocalSingletonStatic() = default;
	};

	template<typename ClassType>
	class MakeSingletonPtr
	{

	public:
		static GFM_BEST_INLINE ClassType & instance() noexcept {
			return *mp_instance;
		}

		MakeSingletonPtr(MakeSingletonPtr &&) = delete;
		MakeSingletonPtr(const MakeSingletonPtr &) = delete;
		MakeSingletonPtr & operator = (MakeSingletonPtr &&) = delete;
		MakeSingletonPtr & operator = (const MakeSingletonPtr &) = delete;

	protected:
		~MakeSingletonPtr() = default;
		MakeSingletonPtr() = default;
		static ClassType* mp_instance;
	};


	template<typename ClassType>
	class MakeSingletonStatic
	{
	public:
		static GFM_BEST_INLINE ClassType & instance() {
			static ClassType instance;
			return instance;
		}

		MakeSingletonStatic(MakeSingletonStatic &&) = delete;
		MakeSingletonStatic(const MakeSingletonStatic &) = delete;
		MakeSingletonStatic & operator = (MakeSingletonStatic &&) = delete;
		MakeSingletonStatic & operator = (const MakeSingletonStatic &) = delete;

	protected:
		~MakeSingletonStatic() = default;
		MakeSingletonStatic() = default;

	};
}//namespace policy
}//namespace gfm
#endif // SINGLETON_H
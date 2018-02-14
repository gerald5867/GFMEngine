#pragma once
#include <chrono>
#include "Types.h"
#define DATE_MAX_LEN 52

namespace gfm 
{
namespace utils 
{
	class Date final
	{

	public:
		using Clock = std::chrono::system_clock;
		using TimePoint = typename std::chrono::time_point<Clock>;

	public:
		Date();

		void UpdateNow();
		const TimePoint& GetTimeStamp() const noexcept;
		const CharType* GetDate() const;

	private:
		TimePoint m_time;
		CharType  m_date[DATE_MAX_LEN];
	};
}//utils
}//gfm
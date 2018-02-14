#pragma once
#include <ctime>
#include "Date.h"
#include "../DataStructures/detail/String/CStringHelper.h"
gfm::utils::Date::Date() {
	UpdateNow();
}

void gfm::utils::Date::UpdateNow() {
	m_time = Clock::now();
	auto timeStamp = Clock::to_time_t(m_time);
	auto* date = std::ctime(&timeStamp);
	detail::CStringHelper::Copy(m_date, date, DATE_MAX_LEN);
}

const gfm::utils::Date::TimePoint& gfm::utils::Date::GetTimeStamp() const noexcept {
	return m_time;
}

const gfm::utils::CharType* gfm::utils::Date::GetDate() const {
	return m_date;
}
#undef DATE_MAX_LEN
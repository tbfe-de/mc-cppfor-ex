#include "Clock.h"

#include <cassert>
#include <iostream>
#include <iomanip>

bool Clock::IsCeiling() const {
    return counter_.IsHighBound();
}
bool Clock::IsFloor() const {
    return counter_.IsLowBound();
}

void Clock::Print(std::ostream& s) const {
    std::ostream os{s.rdbuf()};
    os.fill('0');
    using ULL = unsigned long long;
    const auto name = name_.get() ? name_.get() : "?dead?";
    os << name << '=' << ULL{counter_.GetDays()} << '.'
       << std::setw(2) << ULL{counter_.GetHours()} << ':'
       << std::setw(2) << ULL{counter_.GetMinutes()} << ':'
       << std::setw(2) << ULL{counter_.GetSeconds()};
}

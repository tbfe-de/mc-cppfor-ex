#include "Clock.h"

#include <cassert>
#include <iostream>
#include <iomanip>

Clock::Clock(Clock &&init) noexcept
    : name_{std::move(init.name_)}
    , days_{init.days_.GetValue(), init.days_.GetLimit()}
    , hours_{init.hours_.GetValue(), init.hours_.GetLimit(), &days_}
    , minutes_{init.minutes_.GetValue(), init.minutes_.GetLimit(), &hours_}
    , seconds_{init.seconds_.GetValue(), init.seconds_.GetLimit(), &seconds_}
{
    init.name_ = nullptr;
}

Clock& Clock::operator=(Clock &&rhs) noexcept {
    assert(days_.GetLimit() == rhs.days_.GetLimit());
    assert(hours_.GetLimit() == rhs.hours_.GetLimit());
    assert(minutes_.GetLimit() == rhs.minutes_.GetLimit());
    assert(seconds_.GetLimit() == rhs.seconds_.GetLimit());
//  - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    name_ = std::move(rhs.name_);
    days_.SetValue(rhs.days_.GetValue());
    hours_.SetValue(rhs.hours_.GetValue());
    minutes_.SetValue(rhs.minutes_.GetValue());
    seconds_.SetValue(rhs.seconds_.GetValue());
    return *this;
}

bool Clock::IsCeiling() const {
    return (days_.GetValue()+1 == days_.GetLimit())
        && (hours_.GetValue()+1 == hours_.GetLimit())
        && (minutes_.GetValue()+1 == minutes_.GetLimit())
        && (seconds_.GetValue()+1 == seconds_.GetLimit());
}
bool Clock::IsFloor() const {
    return (days_.GetValue() == 0)
        && (hours_.GetValue() == 0)
        && (minutes_.GetValue() == 0)
        && (seconds_.GetValue() == 0);
}

void Clock::Print(std::ostream& s) const {
    std::ostream os{s.rdbuf()};
    os.fill('0');
    using ULL = unsigned long long;
    const auto name = name_.get() ? name_.get() : "?dead?";
    os << name << '=' << ULL{days_.GetValue()} << '.'
       << std::setw(2) << ULL{hours_.GetValue()} << ':'
       << std::setw(2) << ULL{minutes_.GetValue()} << ':'
       << std::setw(2) << ULL{seconds_.GetValue()};
}

#include "Clock.h"

#include <cassert>
#include <iostream>
#include <iomanip>

Clock::Clock(Clock &&init) noexcept
    : name_(init.name_)
    , days_(init.days_.GetValue(), init.days_.GetLimit())
    , hours_(init.hours_.GetValue(), init.hours_.GetLimit(), &days_)
    , minutes_(init.minutes_.GetValue(), init.minutes_.GetLimit(), &hours_)
    , seconds_(init.seconds_.GetValue(), init.seconds_.GetLimit(), &seconds_)
{
    init.name_ = nullptr;
}

Clock& Clock::operator=(Clock &&rhs) noexcept {
    assert(days_.GetLimit() == rhs.days_.GetLimit());
    assert(hours_.GetLimit() == rhs.hours_.GetLimit());
    assert(minutes_.GetLimit() == rhs.minutes_.GetLimit());
    assert(seconds_.GetLimit() == rhs.seconds_.GetLimit());
    if (this != &rhs) {
	delete[] name_;
        name_ = rhs.name_;
        rhs.name_ = nullptr;
        days_.SetValue(rhs.days_.GetValue());
        hours_.SetValue(rhs.hours_.GetValue());
        minutes_.SetValue(rhs.minutes_.GetValue());
        seconds_.SetValue(rhs.seconds_.GetValue());
    }
    return *this;
}

bool Clock::IsCeiling() const {
    return (seconds_.GetValue()+1 == 0)
        && (minutes_.GetValue()+1 == 0)
        && (hours_.GetValue()+1 == 0)
        && (days_.GetValue()+1 == 0);
}
bool Clock::IsFloor() const {
    return (seconds_.GetValue() == 0)
        && (minutes_.GetValue() == 0)
        && (hours_.GetValue() == 0)
        && (days_.GetValue() == 0);
}

void Clock::Print(std::ostream& s) const {
    std::ostream os{s.rdbuf()};
    os.fill('0');
    auto name = name_ ? name_ : "?dead?";
    os << name << '=' << days_.GetValue() << '.'
       << std::setw(2) << hours_.GetValue() << ':'
       << std::setw(2) << minutes_.GetValue() << ':'
       << std::setw(2) << seconds_.GetValue();
}

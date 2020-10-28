#include "Clock.h"

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

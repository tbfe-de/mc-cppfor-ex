#include "Clock.h"

#include <iostream>
#include <iomanip>

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
    std::ostream os(s.rdbuf());
    os.fill('0');
    const char* name = name_ ? name_ : "?dead?";
    os << name << '=' << days_.GetValue() << '.'
       << std::setw(2) << hours_.GetValue() << ':'
       << std::setw(2) << minutes_.GetValue() << ':'
       << std::setw(2) << seconds_.GetValue();
}

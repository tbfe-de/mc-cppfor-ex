#include "Clock.h"

#include <iostream>
#include <iomanip>

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
    auto name = name_ ? name_ : "?dead?";
    using ULL = unsigned long long;
    os << name << '=' << ULL{days_.GetValue()} << '.'
       << std::setw(2) << ULL{hours_.GetValue()} << ':'
       << std::setw(2) << ULL{minutes_.GetValue()} << ':'
       << std::setw(2) << ULL{seconds_.GetValue()};
}

#include "Clock.h"

#include <iostream>
#include <iomanip>

void Clock::Print(std::ostream& strm) const {
    std::ostream os(strm.rdbuf());
    os.fill('0');
    os << std::setw(2) << hours_.GetValue() << ':'
       << std::setw(2) << minutes_.GetValue() << ':'
       << std::setw(2) << seconds_.GetValue();
}


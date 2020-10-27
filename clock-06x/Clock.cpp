#include "Clock.h"

#include <iostream>
#include <iomanip>

std::ostream& Clock::Print(std::ostream& s) const {
    std::ostream os{s.rdbuf()};
    os.fill('0');
    os << std::setw(2) << hours_.GetValue() << ':'
       << std::setw(2) << minutes_.GetValue() << ':'
       << std::setw(2) << seconds_.GetValue();
    return s;       
}


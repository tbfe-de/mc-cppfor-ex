#include "Clock.h"

#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& lhs, const Clock& rhs) {
    std::ostream os{lhs.rdbuf()};
    os.fill('0');
    os << std::setw(2) << rhs.hours_.GetValue() << ':'
       << std::setw(2) << rhs.minutes_.GetValue() << ':'
       << std::setw(2) << rhs.seconds_.GetValue();
    return lhs;       
}

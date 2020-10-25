#include "Clock.h"

void Clock::TickUp(int n) {
    while (n-- > 0) {
        if (++seconds_ >= 60) {
            seconds_ = 0;
            if (++minutes_ >= 60) {
                minutes_ = 0;
                if (++hours_ >= 24) {
                        hours_ = 0;
                }
            }
        }
    }
}

#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& lhs, const Clock& rhs) {
    std::ostream os{lhs.rdbuf()};
    os.fill('0');
    os << std::setw(2) << rhs.hours_ << ':'
       << std::setw(2) << rhs.minutes_ << ':'
       << std::setw(2) << rhs.seconds_;
    return lhs;       
}

#include "HHMMSS_Clock.h"

#include <cassert>
#include <iostream>
#include <iomanip>

void HHMMSS_Clock::Set(const std::initializer_list<int>& li) {
    assert(li.size() <= 3);
    auto it{ li.begin() };
    for (auto *cntrp : { &hours_, &minutes_, &seconds_ }) {
        if (it == li.end()) return;
        cntrp->SetValue(*it++);
    }
}

void HHMMSS_Clock::Print(std::ostream& s) const {
    std::ostream os{s.rdbuf()};
    os.fill('0');
    os << std::setw(2) << hours_.GetValue() << ':'
       << std::setw(2) << minutes_.GetValue() << ':'
       << std::setw(2) << seconds_.GetValue();
}


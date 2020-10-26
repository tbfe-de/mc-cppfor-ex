#include "StopWatch.h"

#include <cassert>
#include <iostream>
#include <iomanip>

static constexpr int print_width(int n) {
    int result = 1;
    int maxval = n-1;
    while ((maxval /= 10) > 0) {
        ++result;
    }
    return result;
}

void StopWatch::Set(const std::initializer_list<int>& li) {
    assert(li.size() <= 2);
    auto it{ li.begin() };
    if (it != li.end()) seconds_.SetValue(*it++);
    if (it != li.end()) fraction_.SetValue(*it++);
}

void StopWatch::Print(std::ostream& s) const {
    std::ostream os{ s.rdbuf() };
    const auto pw = print_width(fraction_.GetLimit());
    os << seconds_.GetValue() << '.'
       << std::setw(pw) << std::setfill('0') << fraction_.GetValue();
}


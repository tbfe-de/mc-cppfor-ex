#ifndef HHMMSS_CLOCK_H
#define HHMMSS_CLOCK_H

#include <iosfwd>
#include <cstring>
#include <iostream>

#include "IClock.h"
#include "Counter.h"

#include <cassert>

class HHMMSS_Clock : public IClock {
    Counter hours_;
    Counter minutes_;
    Counter seconds_;
public:
    HHMMSS_Clock(int hours = 0, int minutes = 0, int seconds = 0)
        : hours_{24}
        , minutes_{60, &hours_}
        , seconds_{60, &minutes_}
    {
        Set({ hours, minutes, seconds });
    }
    HHMMSS_Clock(const HHMMSS_Clock&) =delete;                // copy c'tor
    HHMMSS_Clock& operator=(const HHMMSS_Clock&) =delete;     // copy assignment
    HHMMSS_Clock(HHMMSS_Clock&&) =delete;                     // move c'tor
    HHMMSS_Clock& operator=(HHMMSS_Clock&&) =delete;          // move assignment

    virtual void Set(const std::initializer_list<int>& li) override;
    virtual void TickUp(int seconds) override { seconds_.Count(seconds); }
    virtual void Print(std::ostream&) const override;
};

#endif

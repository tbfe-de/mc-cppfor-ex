#ifndef CLOCK_H
#define CLOCK_H

#include <iosfwd>

#include "Counter.h"

class Clock {
    Counter hours_;
    Counter minutes_;
    Counter seconds_;
public:
    Clock(int hours = 0, int minutes = 0, int seconds = 0)
        : hours_{24}
        , minutes_{60, &hours_}
        , seconds_{60, &minutes_}
    {
        Set(hours, minutes, seconds);
    }
    Clock(const Clock&) =delete;
    Clock& operator=(const Clock&) =delete;
    
    void Set(int hours, int minutes, int seconds) {
        hours_.SetValue(hours);
        minutes_.SetValue(minutes);
        seconds_.SetValue(seconds);
    }
    void TickUp(int ticks = 1) { seconds_.Count(ticks); }
    friend std::ostream& operator<<(std::ostream&, const Clock&);
};

#endif

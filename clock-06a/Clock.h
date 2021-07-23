#ifndef CLOCK_H
#define CLOCK_H

#include <iosfwd>
#include <cstring>
#include <iostream>

#include "IClock.h"
#include "LimitCounter.h"
#include "OverflowCounter.h"

class Clock : public IClock {
    LimitCounter hours_;
    OverflowCounter minutes_;
    OverflowCounter seconds_;
public:
    Clock(int hours = 0, int minutes = 0, int seconds = 0)
        : hours_(24)
        , minutes_(60, hours_)
        , seconds_(60, minutes_)
    {
        Set(hours, minutes, seconds);
    }
private:
    Clock(const Clock&);                        // copy c'tor
    Clock& operator=(const Clock&);             // copy assignment

public:
    virtual void Set(int hours, int minutes, int seconds) {
        hours_.SetValue(hours);
        minutes_.SetValue(minutes);
        seconds_.SetValue(seconds);
    }
    virtual void TickUp(int seconds) { seconds_.Count(seconds); }
    virtual std::ostream& Print(std::ostream&) const;
};

#endif

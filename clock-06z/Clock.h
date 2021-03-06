#ifndef CLOCK_H
#define CLOCK_H

#include <iosfwd>
#include <cstring>
#include <iostream>

#include "IClock.h"
#include "LimitCounter.h"
#include "OverflowCounter.h"

class Clock : public IClock {
    const char* name_;
    LimitCounter hours_;
    OverflowCounter minutes_;
    OverflowCounter seconds_;
public:
    Clock(const char* name, int hours = 0, int minutes = 0, int seconds = 0)
        : name_{std::strcpy(new char[std::strlen(name)+1], name)}
        , hours_{24}
        , minutes_{60, hours_}
        , seconds_{60, minutes_}
    {
        Set(hours, minutes, seconds);
    }
    ~Clock() { delete[] name_; }
    Clock(const Clock&) =delete;                // copy c'tor
    Clock& operator=(const Clock&) =delete;     // copy assignment
    Clock(Clock&&) =delete;                     // move c'tor
    Clock& operator=(Clock&&) =delete;          // move assignment

    virtual void Set(int hours, int minutes, int seconds) override {
        hours_.SetValue(hours);
        minutes_.SetValue(minutes);
        seconds_.SetValue(seconds);
    }
    virtual void TickUp(int seconds) override { seconds_.Count(seconds); }
    virtual std::ostream& Print(std::ostream&) const override;
};

#endif
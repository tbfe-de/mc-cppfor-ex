#ifndef CLOCK_H
#define CLOCK_H

#include <cstring>
#include <iosfwd>

#include "IClock.h"
#include "UpDownCounter.h"

class Clock : public IClock {
    const char* name_;
    UpDownCounter days_;
    UpDownCounter hours_;
    UpDownCounter minutes_;
    UpDownCounter seconds_;
public:
    Clock(const char* name,
          UpDownCounter::value_type days = 0,
          UpDownCounter::value_type hours = 0,
          UpDownCounter::value_type minutes = 0,
          UpDownCounter::value_type seconds = 0)
        : name_(std::strcpy(new char[std::strlen(name)+1], name))
        , days_(days, 0, NULL)
        , hours_(hours, 24, &days_)
        , minutes_(minutes, 60, &hours_)
        , seconds_(seconds, 60, &minutes_)
    {}
    ~Clock() { delete[] name_; }    // REQUIRED to return heap memory
    Clock(const Clock&);            // will NOT be implemented
    Clock& operator=(const Clock&); // will NOT be implemented

    Clock& Days(unsigned v = 0)
        { days_.SetValue(v); return *this; }
    Clock& Hours(unsigned v = 0)
        { hours_.SetValue(v); return *this; }
    Clock& Minutes(unsigned v = 0)
        { minutes_.SetValue(v); return *this; }
    Clock& Seconds(unsigned v = 0)
        { seconds_.SetValue(v); return *this; }

    virtual void Print(std::ostream&) const;
    virtual bool IsCeiling() const;
    virtual bool IsFloor() const;
    virtual IClock& TickUp()
        { if (!IsCeiling()) seconds_.UpCount(); return *this; }
    virtual IClock& TickDown()
        { if (!IsFloor()) seconds_.DownCount(); return *this; }
};

#endif

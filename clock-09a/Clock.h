#ifndef CLOCK_H
#define CLOCK_H

#include <cstddef>
#include <cstring>
#include <iosfwd>
#include <memory>
#include <utility>

#include "IClock.h"
#include "UpDownCounter.h"

class Clock : public IClock {
    std::auto_ptr<char> name_;
    UpDownCounter days_;
    UpDownCounter hours_;
    UpDownCounter minutes_;
    UpDownCounter seconds_;
    static std::auto_ptr<char> strdup_to_auto_ptr(const char *s) {
	    std::auto_ptr<char> r(new char[std::strlen(s)+1]);
    	std::strcpy(r.get(), s);
        return r;
    }
public:
    Clock(const char* name,
          UpDownCounter::value_type days = 0,
          UpDownCounter::value_type hours = 0,
          UpDownCounter::value_type minutes = 0,
          UpDownCounter::value_type seconds = 0)
        : name_(strdup_to_auto_ptr(name))
        , days_(days, 0, NULL)
        , hours_(hours, 24, &days_)
        , minutes_(minutes, 60, &hours_)
        , seconds_(seconds, 60, &minutes_)
    {}
    ~Clock() {}
    Clock(Clock&) throw();              // user-defined copy is move c'tor       
    Clock& operator=(Clock&) throw();   // user-defined copy is move assignment

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

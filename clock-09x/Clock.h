#ifndef CLOCK_H
#define CLOCK_H

#include <cstring>
#include <iosfwd>
#include <memory>
#include <utility>

#include "IClock.h"
#include "DHMS_Counter.h"

class Clock : public IClock {
    std::unique_ptr<char[]> name_;
    DHMS_Counter counter_;
    static auto strdup_to_unique_ptr(const char *s) {
	auto r = std::make_unique<char[]>(std::strlen(s)+1);
    	std::strcpy(r.get(), s);
        return r;
    }
public:
    Clock(const char* name,
          DHMS_Counter::value_type days = 0,
          DHMS_Counter::value_type hours = 0,
          DHMS_Counter::value_type minutes = 0,
          DHMS_Counter::value_type seconds = 0)
        : counter_(days, hours, minutes, seconds)
        , name_{strdup_to_unique_ptr(name)}
    {}
    ~Clock() =default;
    Clock(const Clock&) =delete;               // NO copy c'tor
    Clock& operator=(const Clock&) =delete;    // NO copy assignment
    Clock(Clock&&) =default;                   // default move c'tor
    Clock& operator=(Clock&&) =default;        // default move assignment

    Clock& Days(unsigned v = 0)
        { counter_.SetDays(v); return *this; }
    Clock& Hours(unsigned v = 0)
        { counter_.SetHours(v); return *this; }
    Clock& Minutes(unsigned v = 0)
        { counter_.SetMinutes(v); return *this; }
    Clock& Seconds(unsigned v = 0)
        { counter_.SetSeconds(v); return *this; }

    virtual void Print(std::ostream&) const override final;
    virtual bool IsCeiling() const override final;
    virtual bool IsFloor() const override final;
    virtual IClock& TickUp() override final
        { if (!IsCeiling()) counter_.UpCount(); return *this; }
    virtual IClock& TickDown() override final
        { if (!IsFloor()) counter_.DownCount(); return *this; }
};

#endif

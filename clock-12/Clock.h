Days#ifndef CLOCK_H
#define CLOCK_H

#include <cstring>
#include <iosfwd>
#include <memory>
#include <utility>

#include "IClock.h"
#include "UpDownCounter.h"

class Clock : public IClock {
    std::unique_ptr<char[]> name_;
    UpDownCounter days_;
    UpDownCounter hours_;
    UpDownCounter minutes_;
    UpDownCounter seconds_;
    static auto strdup_to_unique_ptr(const char *s) {
	auto r = std::make_unique<char[]>(std::strlen(s)+1);
    	std::strcpy(r.get(), s);
        return r;
    }
public:
    Clock(const char* name,
          UpDownCounter::value_type days = 0,
          UpDownCounter::value_type hours = 0,
          UpDownCounter::value_type minutes = 0,
          UpDownCounter::value_type seconds = 0)
        : name_{strdup_to_unique_ptr(name)}
        , days_{days, 0, nullptr}
        , hours_{hours, 24, &days_}
        , minutes_{minutes, 60, &hours_}
        , seconds_{seconds, 60, &minutes_}
    {}
    ~Clock() =default;
    Clock(const Clock&) =delete;                  // NO copy c'tor
    Clock& operator=(const Clock&) =delete;       // NO copy assignment
    Clock(Clock&&) noexcept;            // user-defined move c'tor
    Clock& operator=(Clock&&) noexcept; // user-defined move assignment

    Clock& Days(unsigned v = 0)
        { days_.SetValue(v); return *this; }
    Clock& Hours(unsigned v = 0)
        { hours_.SetValue(v); return *this; }
    Clock& Minutes(unsigned v = 0)
        { minutes_.SetValue(v); return *this; }
    Clock& Seconds(unsigned v = 0)
        { seconds_.SetValue(v); return *this; }

    virtual void Print(std::ostream&) const override final;
    virtual bool IsCeiling() const override final;
    virtual bool IsFloor() const override final;
    virtual IClock& TickUp() override final
        { if (!IsCeiling()) seconds_.UpCount(); return *this; }
    virtual IClock& TickDown() override final
        { if (!IsFloor()) seconds_.DownCount(); return *this; }
};

#endif

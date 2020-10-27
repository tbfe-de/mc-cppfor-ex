#ifndef CLOCK_H
#define CLOCK_H

#include <cstdint>
#include <cstring>
#include <iosfwd>
#include <iostream>

#include "IClock.h"
#include "UpDownCounter.h"

class Clock : public IClock {
public:
    using CounterType = UpDownCounter<std::uint_fast8_t>;
private:
    const char* name_;
    CounterType days_;
    CounterType hours_;
    CounterType minutes_;
    CounterType seconds_;
    constexpr static auto cvt_adjusted(int v) {
        return static_cast<CounterType::value_type>((v > 0) ? v : 0);
    }
public:
    Clock(const char* name, int days = 0, int hours = 0, int minutes = 0, int seconds = 0)
        : name_{std::strcpy(new char[std::strlen(name)+1], name)}
        , days_{cvt_adjusted(days)}
        , hours_{cvt_adjusted(hours), cvt_adjusted(24), &days_}
        , minutes_{cvt_adjusted(minutes), cvt_adjusted(60), &hours_}
        , seconds_{cvt_adjusted(seconds), cvt_adjusted(60), &minutes_}
    {}
    ~Clock() { delete[] name_; }
    Clock(const Clock&) =delete;                // copy c'tor
    Clock& operator=(const Clock&) =delete;     // copy assignment
    Clock(Clock&&) =delete;                     // move c'tor
    Clock& operator=(Clock&&) =delete;          // move assignment

    virtual void Set(int days, int hours, int minutes, int seconds) override {
	if (days >= 0) days_.SetValue(cvt_adjusted(days));
        if (hours >= 0) hours_.SetValue(cvt_adjusted(hours));
        if (minutes >= 0) minutes_.SetValue(cvt_adjusted(minutes));
        if (seconds >= 0) seconds_.SetValue(cvt_adjusted(seconds));
    }
    virtual void TickUp() override { seconds_.UpCount(); }
    virtual void TickDown() override { seconds_.DownCount(); }
    virtual void Print(std::ostream&) const override;
};

#endif

#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <cassert>
#include <cstring>
#include <iosfwd>
#include <iostream>

#include "IClock.h"
#include "Counter.h"

class StopWatch : public IClock {
    Counter seconds_{};
    Counter fraction_{};
public:
    StopWatch()
        : fraction_{1000, &seconds_}
    {}
    StopWatch(const StopWatch&) =delete;                // copy c'tor
    StopWatch& operator=(const StopWatch&) =delete;     // copy assignment
    StopWatch(StopWatch&&) =delete;                     // move c'tor
    StopWatch& operator=(StopWatch&&) =delete;          // move assignment

    virtual void Set(const std::initializer_list<int>& li) override;
    virtual void TickUp(int steps) override { fraction_.Count(steps); }
    virtual void Print(std::ostream&) const override;
};

#endif

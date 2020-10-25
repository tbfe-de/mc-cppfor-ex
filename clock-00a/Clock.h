#ifndef CLOCK_H
#define CLOCK_H

#include <iosfwd>

class Clock {
    int hours_;
    int minutes_;
    int seconds_;
public:
    Clock()
        : hours_(0)
        , minutes_(0)
        , seconds_(0)
    {}
    Clock(int hours, int minutes, int seconds)
        : hours_(hours)
        , minutes_(minutes)
        , seconds_(seconds)
    {}
    Clock(const Clock&); // will NOT be implemented
    Clock& operator=(const Clock&); // will NOT be implemented
    
    void Set(int hours, int minutes, int seconds) {
        hours_ = hours;
        minutes_ = minutes;
        seconds_ = seconds;
    }
    void TickUp(int seconds = 1);
    friend std::ostream& operator<<(std::ostream&, const Clock&);
};

#endif

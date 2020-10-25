#ifndef CLOCK_H
#define CLOCK_H

#include <iosfwd>

class Clock {
    int hours_{0};
    int minutes_{0};
    int seconds_{0};
public:
    Clock() =default;
    Clock(int hours, int minutes, int seconds)
        : hours_{hours}
        , minutes_{minutes}
        , seconds_{seconds}
    {}
    Clock(const Clock&) =delete;
    Clock& operator=(const Clock&) =delete;
    
    void Set(int hours, int minutes, int seconds) {
        hours_ = hours;
        minutes_ = minutes;
        seconds_ = seconds;
    }
    void TickUp(int seconds = 1);
    friend std::ostream& operator<<(std::ostream&, const Clock&);
};

#endif
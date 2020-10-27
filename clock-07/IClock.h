#ifndef ICLOCK_H
#define ICLOCK_H

#include <iosfwd>

class IClock {
public:
    virtual ~IClock() =default;
    virtual void Set(int days = -1,
                     int hours = -1,
                     int minutes = -1,
                     int seconds = -1) =0;
    virtual void TickUp() =0;
    virtual void TickDown() =0;
    virtual void Print(std::ostream&) const =0;
};

inline
std::ostream& operator<<(std::ostream& lhs, const IClock& rhs) {
    rhs.Print(lhs);
    return lhs;
}

#endif

#ifndef ICLOCK_H
#define ICLOCK_H

#include <iosfwd>

class IClock {
public:
    virtual ~IClock() =default;
    virtual void Set(int, int, int) =0;
    virtual void TickUp(int = 1) =0;
    virtual std::ostream& Print(std::ostream&) const =0;
};

inline
std::ostream& operator<<(std::ostream& lhs, const IClock& rhs) {
    return rhs.Print(lhs);
}

#endif
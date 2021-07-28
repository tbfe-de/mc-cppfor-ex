#ifndef ICLOCK_H
#define ICLOCK_H

#include <iosfwd>

class IClock {
public:
    virtual ~IClock() =default;
    virtual void Print(std::ostream&) const =0;
    virtual bool IsCeiling() const =0;
    virtual bool IsFloor() const =0;
    virtual IClock& TickUp() =0;
    virtual IClock& TickDown() =0;
};

inline
std::ostream& operator<<(std::ostream& lhs, const IClock& rhs) {
    rhs.Print(lhs);
    return lhs;
}

#endif

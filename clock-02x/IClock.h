#ifndef ICLOCK_H
#define ICLOCK_H

#include <iosfwd>

#include <initializer_list>

class IClock {
public:
    virtual ~IClock() =default;
    virtual void Set(const std::initializer_list<int>& li) =0;
    virtual void TickUp(int = 1) =0;
    virtual void Print(std::ostream&) const =0;
};

inline
std::ostream& operator<<(std::ostream& lhs, const IClock& rhs) {
    rhs.Print(lhs);
    return lhs;
}

#endif

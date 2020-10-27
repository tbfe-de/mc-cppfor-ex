#include <iostream>

#define SHOW(...)\
    (void)(std::cout << __FILE__ <<  ':' << __LINE__ << '\t'\
                     << #__VA_ARGS__ << " --> " << (__VA_ARGS__)\
                     << std::endl)

#include "IClock.h" 

void appl(IClock& c) {
    SHOW(                           c);
    SHOW(c.TickUp(),                c);
    SHOW(c.TickUp(),                c);
    SHOW(c.TickUp(),                c);
    SHOW(c.Set(3, 0, 0, 58),        c);
    SHOW(c.TickUp(),                c);
    SHOW(c.TickUp(),                c);
    SHOW(c.TickUp(),                c);
    SHOW(c.Set(-1, -1, 59, 58),     c);
    SHOW(c.TickUp(),                c);
    SHOW(c.TickUp(),                c);
    SHOW(c.Set(-1, 23, 59, 59),     c);
    SHOW(c.TickUp(),                c);
    SHOW(c.TickDown(),              c);
}

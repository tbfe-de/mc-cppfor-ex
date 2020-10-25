#include <iostream>

#define SHOW(...)\
    (void)(std::cout << __FILE__ <<  ':' << __LINE__ << '\t'\
                     << #__VA_ARGS__ << " --> " << (__VA_ARGS__)\
                     << std::endl)

#include "IClock.h" 

void appl(IClock& c) {
    SHOW(                 c);
    SHOW(c.TickUp(),      c);
    SHOW(c.TickUp(),      c);
    SHOW(c.TickUp(),      c);
    SHOW(c.Set({22, 58}), c);
    SHOW(c.TickUp(),      c);
    SHOW(c.TickUp(),      c);
    SHOW(c.TickUp(),      c);
    SHOW(c.TickUp(200),   c);
    SHOW(c.TickUp(400),   c);
    SHOW(c.TickUp(600),   c);
}

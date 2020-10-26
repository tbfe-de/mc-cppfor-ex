#include <iostream>

#define SHOW(...)\
    (void)(std::cout << __FILE__ <<  ':' << __LINE__ << '\t'\
                     << #__VA_ARGS__ << " --> " << (__VA_ARGS__)\
                     << std::endl)

#include "IClock.h" 

void appl(IClock& c) {
    c.TickUp();             c.Print(std::cout);
    c.TickUp();             SHOW(c);
    c.TickUp();             SHOW(c);
    c.TickUp();             SHOW(c);
    c.Set(0, 0, 58);        SHOW(c);
    c.TickUp();             SHOW(c);
    c.TickUp();             SHOW(c);
    c.TickUp();             SHOW(c);
    c.Set(0, 59, 58);       SHOW(c);
    c.TickUp();             SHOW(c);
    c.TickUp();             SHOW(c);
}

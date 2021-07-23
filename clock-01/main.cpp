#include "Clock.h"

#include <iostream>

#define SHOW(...)\
    (void)(std::cout << __FILE__ <<  ':' << __LINE__ << '\t'\
                     << #__VA_ARGS__ << " --> " << (__VA_ARGS__)\
                     << std::endl)
int main() {
    std::cout.setf(std::ios::boolalpha);
    
    Clock c{};              SHOW(c);
    c.TickUp();             SHOW(c);
    c.TickUp();             SHOW(c);
    c.TickUp();             SHOW(c);
    c.Set(0, 0, 58);        SHOW(c);
    c.TickUp();             SHOW(c);
    c.TickUp();             SHOW(c);
    c.TickUp();             SHOW(c);
    c.TickUp(60);           SHOW(c);
    c.TickUp(60);           SHOW(c);
    
    Clock c2{23, 59, 58};   SHOW(c2);
    c2.TickUp();            SHOW(c2);
    c2.TickUp();            SHOW(c2);
    c2.TickUp();            SHOW(c2);
 }

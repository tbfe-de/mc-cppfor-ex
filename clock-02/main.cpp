#include "Clock.h"

extern void appl(IClock&);
                     
int main()
{
    std::cout.setf(std::ios::boolalpha);
    Clock c{};
    appl(c);
 }

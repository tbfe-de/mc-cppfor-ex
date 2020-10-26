#include "Clock.h"

extern void appl(IClock&);
                     
int main()
{
    #if defined LC_SIMPLE_IMPLEMENTATION && defined OC_SIMPLE_IMPLEMENTATION
    std::cout << "simple LimitCounter and "
                 "simple OverflowCounter implementations" << std::endl;
    #elif defined LC_SIMPLE_IMPLEMENTATION
    std::cout << "simple LimitCounter implementation" << std::endl;
    #elif defined OC_SIMPLE_IMPLEMENTATION
    std::cout << "simple OverflowCounter implementation" << std::endl;
    #endif

    std::cout.setf(std::ios::boolalpha);
    Clock c{};
    appl(c);
 }

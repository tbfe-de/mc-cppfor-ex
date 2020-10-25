#include "HHMMSS_Clock.h"
#include "StopWatch.h"

extern void appl(IClock&);
                     
int main()
{
    std::cout.setf(std::ios::boolalpha);

    HHMMSS_Clock c{18, 59, 58};
    appl(c);
    StopWatch s{};
    appl(s);
}

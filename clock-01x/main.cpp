#include "Clock.h"

#include <iostream>
#include <sstream>

#define SHOW_(expect, ...)\
    do {\
        std::ostringstream result;\
        result.copyfmt(std::cout);\
        result << (__VA_ARGS__);\
       	std::cout << __FILE__ <<  ':' << __LINE__ << '\t'\
                  << #__VA_ARGS__ << " --> " << result.str();\
        if (result.str() != expect) {\
            std::cout << " != " << expect;\
        }\
        std::cout << std::endl;\
    }\
    while (0)

int main()
{
    std::cout.setf(std::ios::boolalpha);
    
    Clock c{};              SHOW_("00:00:00", c);
    c.TickUp();             SHOW_("00:00:01", c);
    c.TickUp();             SHOW_("00:00:02", c);
    c.TickUp();             SHOW_("00:00:03", c);

    c.Set(0, 0, 58);	    SHOW_("00:00:58", c);
    c.TickUp();             SHOW_("00:00:59", c);
    c.TickUp();             SHOW_("00:01:00", c);
    c.TickUp();             SHOW_("00:01:01", c);
    c.TickUp(60);           SHOW_("00:02:01", c);
    c.TickUp(100);          SHOW_("00:03:41", c);
    c.TickUp(1000);         SHOW_("00:20:21", c);
    
    Clock c2{23, 59, 58};   SHOW_("23:59:58", c2);
    c2.TickUp();            SHOW_("23:59:59", c2);
    c2.TickUp();            SHOW_("00:00:00", c2);
    c2.TickUp();            SHOW_("00:00:01", c2);
 }

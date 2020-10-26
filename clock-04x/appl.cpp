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

#include "IClock.h" 

void appl(IClock& c) {
    SHOW_("00:00:00", 			c);
    SHOW_("00:00:01", c.TickUp(),	c);
    SHOW_("00:00:02", c.TickUp(), 	c);
    SHOW_("00:00:03", c.TickUp(), 	c);
    SHOW_("00:00:58", c.Set(0, 0, 58), 	c);
    SHOW_("00:00:59", c.TickUp(), 	c);
    SHOW_("00:01:00", c.TickUp(), 	c);
    SHOW_("00:01:01", c.TickUp(),	c);
    SHOW_("00:59:58", c.Set(0, 59, 58), c);
    SHOW_("00:59:59", c.TickUp(),	c);
    SHOW_("01:00:00", c.TickUp(),	c);
    SHOW_("01:01:00", c.TickUp(60),	c);
    SHOW_("01:11:00", c.TickUp(600),	c);
}

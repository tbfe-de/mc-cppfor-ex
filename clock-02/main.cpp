#include "Clock.h"

extern void appl(IClock&);
                     
int main() {
    Clock c{};
    appl(c);
 }

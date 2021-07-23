#include "Clock.h"

#include <iostream>

int main() {
    Clock c{};              std::cout << c << std::endl;
    c.TickUp();             std::cout << c << std::endl;
    c.TickUp();             std::cout << c << std::endl;
    c.TickUp();             std::cout << c << std::endl;
    c.Set(0, 0, 58);        std::cout << c << std::endl;
    c.TickUp();             std::cout << c << std::endl;
    c.TickUp();             std::cout << c << std::endl;
    c.TickUp();             std::cout << c << std::endl;
    c.Set(0, 58, 37);       std::cout << c << std::endl;	
    c.TickUp(60);           std::cout << c << std::endl;
    c.TickUp(100);          std::cout << c << std::endl;
    
    Clock c2{23, 59, 58};   std::cout << c2 << std::endl;
    c2.TickUp();            std::cout << c2 << std::endl;
    c2.TickUp();            std::cout << c2 << std::endl;
    c2.TickUp();            std::cout << c2 << std::endl;
 }

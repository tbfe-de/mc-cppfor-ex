# mc-cppfor-ex

## Sequence of exercises

    C++98 track | Modern C++ | (Extras)
    ------------+------------+----------
    clock-00a <--> clock-00
                       |
                       v
    clock-01a <--> clock-01 --> clock-01x
                       |
                       v
    clock-02a <--> clock-02 --> clock-02x
                       |
                       v
    clock-03a <--> clock-03 --> clock-03x
                       |
                       v
    clock-04a <--> clock-04 --> clock-04x
                       |
                       v
    clock-05a <--> clock-05 --> clock-05x
                       |
                       v
    clock-06a <--> clock-06 --> clock-06x
                       |   \     \-> clock-06y
                       v    \------> clock-06z
    clock-07a <--> clock-07 --> clock-07x
                       |
                       v
    clock-08a <--> clock-08 --> clock-08x
                       |
                       v
    clock-09a <--> clock-09
                       |
                       v
                   clock-10
                       |
                       v
                   clock-11
                       |
                       v
                   clock-12
                       |
                       v
                   clock-xx
```

## Specific C++11 features used in steps 0 to 9

    0 1 2 3 4 5 6 7 8 9
    - - - - - - * * * * new typedef / type aliasing syntax
    * * * * * * * * * * brace initialization
    - * - * - - - * * * auto-typed variables
    - * * * * - - - - * auto as return type
    - - - - - - - - * * std::initializer_list
    - - - - - - - - - * range-based for loops
    * * * * * * * * * * direct member initialization
    - * * * * * * * * - move constructor / assignment
    * * * * * * * * * * delete-ing copy/move
    * * * * * * * * * * default-ing / delete-ing (in general)
    - - - - - - - * * * constructor delegation
    - * * * * * * * * * override / final
    - - - - - - - * * * lambdas
    - - - - - - - - * - std::array
    - - - - - - - - - * std::unordered_map
    - - - - - - - - - * std::unique_ptr
    - - - - - - - - - * STL algorithms

Generally for the above you may just do a side-by-side
comparison of the files in the `clock-0#` variant with their
counterpart in the `clock-0#a` variant to see the equivalent
C++98 feature.

## Specific C++11 features outside mainline steps 0 … 9

    02x 06y 06z 10 11 . new typedef syntax
    02x 08 10 11 ...... initializer_list
    02x 11 ............ range-based for loops
    06y ............... variadic template argument lists
    06y ............... perfect forwarding
    10 11 ............. lambdas
    10 11 ............. std::array
    10 11 ............. std::unordered_map
    10 11 ............. STL algorithms
    ................... constructor inheritance

Here is no direct C++98 equivalent directly available.
(Multiple template overloads as alternative to variadic
template argument lists as used in `06y` are in `06x`.)

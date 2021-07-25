# mc-cppfor-ex

## Specific C++11 features used in steps 0 to 9

    0 1 2 3 4 5 6 7 8 9
    - - - - - - * * * - new typedef / type aliasing syntax
    * * * * * * * * * * brace initialization
    - * - * - - - * * * auto-typed variables
    - * * * * - - - - * auto as return type
    - - - - - - - - * * std::initializer_list
    - - - - - - - - - * range-based for loops
    - * * * * * * * * * rvalue references
    * * * * * * * * * * direct member initialization
    - * * * * * * * * - move constructor / assignment
    * * * * * * * * * * delete-ing copy/move
    - * * * * * * * * * default-ing / delete-ing (in general)
    - - - - - - - * - - constructor delegation
    - * * * * * * * * * override / final
    - - - - - - - * - * lambdas
    - - - - - - - - * - std::array
    - - - - - - - - - * std::unordered_map
    - - - - - - - - - * std::unique_ptr
    - - - - - - - - - * STL algorithms

Generally simply do a side-by-side comparison of the files
in the `clock-0#` variant with their counterpart in the
`clock-0#a` variant.

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

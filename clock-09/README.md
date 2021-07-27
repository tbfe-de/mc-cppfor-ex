# Simplify the code by using `std::unique_ptr`

As promised, the solution was mostly deleting lines no
longer necessary.

The copy operations (constructor and assignment) are still
kept as `=delete` to express the *Move Only* character of
the class.

Technically that wouldn't be necessary as according to
C++11 rules once a class defines it's own move operarions
no "default" copy operations will be created by the compiler
by itself.

# Simplify the code by using `std::unique_ptr`

As promised, the solution was mostly deleting lines no
longer necessary.

The copy operations (constructor and assignment) are still
kept to express the *Move Only* character of the class,
though they wouldn't have to be included explicitly.

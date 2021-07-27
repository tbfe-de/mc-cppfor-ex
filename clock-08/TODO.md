# Simplify the code by using `std::unique_ptr`

A *Move-Only* class implemented with raw pointers can
typically be simplified by replacing the raw pointer
with an `std::unique_ptr`.

- The constructor will have to do more or less the same as
  before …
- … but the destructor isn't any longer necessary (if its
  only purpose was to `delete` or `delete[]` the heap space
  pointed to) …
- … same for the move operations (constructor and assignment)
  which may be simply `default`-ed …
- … while the copy operations (constructor and assignment) are
  automatically `delete`-d as the `std::unique_ptr` member
  doesn't support copying.

So this exercise is mostly about deleting stuff … (at the right
places).

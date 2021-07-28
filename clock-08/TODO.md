# Simplify the code by using `std::unique_ptr`

A *Move-Only* class implemented with raw pointers can
typically be simplified by replacing the raw pointer
```
… const char* name_;
```
with an
```
std::unique_ptr<char[]>` name_;
```

- The constructor will have to do more or less the same as
  before …
- … but the destructor isn't any longer necessary …
  -  … at least if its only purpose was to `delete` or
     `delete[]` the heap space pointed to, which is the
     case here …
- … same for the move operations (constructor and
    assignment) which may be simply `default`-ed …
    - … at least if their only purpose was to "steal"
      the pointer into the heap from `init_` or `rhs_` …
    - … **which is NOT the case here(!)**
- … while the copy operations (constructor and assignment)
    are automatically `delete`-d as the `std::unique_ptr`
    member doesn't support copying.
- Furthermore, wherever `name_` is used in places in which
  the contained raw pointer is required
  - `name_` must be replaced with
  - `name_.get()`.

So this exercise could be mostly about deleting stuff (at
the right places) …

* * * * *

**… if only there weren't that pesky `UpDownCounter`-s!**

* * * * *

These are neither copyable nor moveable for a good reason:

- Each `UpDownCounter` contains a pointers to the next
  stage.
- Therefore only the destructor of the `Clock can be
  removed completely..
- In `Clock::Clock(Clock&& init) the following needs to
  be modified:
  - `… name_{init.name_} …` becomes
  - `… name_{std::move(init.name_)} …` and
  -  `init.name_ = nullptr;` is removed.
- Similarly in `Clock& operator=Clock(Clock&& init, where
  the following needs to be modified:
  - `… name_ = rhs.name_ …` becomes
  - `… name_ = std::move(rhs.name_)`and
  -  `rhs.name_ = nullptr;` is removed.
  - 
  to be modified.

  * * * * * 

  Optional / Advanced

  (TBD)

  



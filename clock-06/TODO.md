# Nothing Much To Be Done This Time

At this point the current design is discontinued.

It was mainly chosen to demonstrate aspects of class design
with a relatively simple example. From a practical viewpoint
it is somewhat "over-engineered" and staying with it would
make demonstrating more C++ features outside the classic OOP
realm needlessly convoluted.

Still, the general topic is kept, which is to build a
`Clock` but this time one that can count up and down and
will finally be used to build "KitchenTimer"-s which …
- … can be set to a specific start value from which they
  count down …
- … at which point they will issue an alarm …
- … and start to count up from there …
- … (so that the cook knows how over-boiled the egg is :-)).

The smallest component of this new kind of `Clock` will be
`UpDownCounters` - wait and see (and relax a bit before we
redirect our journey to new spots in C++ land).

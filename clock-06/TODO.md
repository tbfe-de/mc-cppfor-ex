# Nothing To Be Done This Time

At this point the current design is discontinued.

It was chosen to mainly demonstrate aspects of class design
with a simple example. From a practical viewpoint it is
somewhat "over-engineered" and staying with would make
demonstrating more C++ features outside the OOP realm
needlessly convoluted.

Still, the general topic is kept, which is to build a
`Clock` but this time one that can count up and down
and will finally be used to build a "KitchenTimer"-s
which …
- … can be ste to a specific start value from which they count down …
- … at which point they will issue an alarm …
- … at start to count up from there
- (so that the cook can see how over-boiled the egg is :-)).

The smallest component of this new kind of `Clock` will be
`UpDownCounters` - wait and see (and relax a bit before we
start on a new journey through C++ land).
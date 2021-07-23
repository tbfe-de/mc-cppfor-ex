#  Encapsulate the Increment Logic and Data in a Class

The overflow algorithm is separated into a class of its own.
Objects of this class can be chained via pointers. The last
in the chain holds a null pointer.

- PRO-s:
  - straight forward extension
  - still quite easy to understand

- CON-s:
  - no flexibility wrt. the counters used in the clock

* * * * *

UNRELATED improvements:

Generating output has been moved into the helper macro
`SHOW`` (intended to be useful mainly for proof of concept
implementations).

- PRO-s:
  - more compact
  - centralizes changes and extensions

- CON-s:
  - to understand the program the helper macro needs to be
    understood too
  - (really, does it …?)

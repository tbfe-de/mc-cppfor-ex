Example For a Clock Build From a Helper Class `Counter`
=======================================================

The overflow algorithm is separated into a class of its own.
Objects of this class can be chained via pointers. The last
in the chain holds a null pointer.

PRO-s:
	straight forward extension
	still quite easy to understand
CON-s:
	no flexibility wrt. the counters used in the clock

UNRELATED improvements:

Output (designed mostly for debugging and prove of concept)
moved into helper macro.

PRO-s:
	more compact
	centralizes changes and extensions
CON-s:
	to understand the program the helper macro needs to
	be understood too

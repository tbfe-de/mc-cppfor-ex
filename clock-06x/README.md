# Fill Extension Points via Template Base Class (Version 2)

**NOTE:**\
All what is said for `clock-06` applies heres too – make
sure you read that other `README.txt` first.

The main purpose is to show how templated constructors for
up to three arguments can be supplied ("just in case" the
template base class might have a need for them).

Also, a technique called "perfect forwarding" is used to
ensured moves are used for handing over arguments, if such
are available.

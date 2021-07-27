# Adding an Interface `ICounter` (Version 2)

    +----------------+
    | <<interface>>  |
    |   ICounter     |
    |                |
    +-----.----.-----+
         /_\  /_\
          |    |_____________________
          |                         |
    +----------------+    +-----------------+
    |   <<class>>    |    |    <<class>>    |
    |  LimitCounter  |---<> OverflowCounter |
    |                |    |                 |
    +----------------+    +-----------------+

The interface ICounter` is implemented by `LimitCounter`,
which subsequently defines the extension points and is USED
AS PART of `OverflowCounter` (= Composition), which fills
the extension points to implement the added behavior.

Furthermore `OverflowCounter` would also need to IMPLEMENT
the interface `ICounter`, as member functions from used
parts can only be delegated to.

A specialty from C++ are "private base classes", essentially
composition too, but providing a short-hand for delegation
via `using` directives, which can be used to change
visibility of privately inherited member functions.

A minor pitfall here is that delegating via `using`
directives to the implementation of `ICounter` as done in
`LimitCounter`, COMING FROM `OverflowCounter`, technically
is ambiguous. To avoid the ambiguity it is necessary to make
`ICounter` a virtual base class, OF BOTH, `LimitCounter` and
`OverflowCounter`, which may cause a tiny performance
penalty.

(How much depends on the implementation, usually it's
minimal, eg. instead of two levels of indirection when
calling a function from the interface it may be three.)

From the viewpoint of the LSP `OverflowCounter` also IS NOT
a `LimitCounter`, though it shares most of its member
function names.

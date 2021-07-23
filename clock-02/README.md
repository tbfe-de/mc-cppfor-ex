# Adding an Interface to the Clock

Adding an interface (class) `IClock` makes the design more
flexible. Among other things several different types of clocks
(with different counter arrangements) may implement this
interface.

**NOTE:**\
Several classes implementing this interface are NOT shown in
this solution as simply moving all of the former member
functions of clock to the `IClock` interface is disputable:

- It defeats at least one of the design goals - … 
- … if that were to operate several clocks …
- … with a different number of counters.

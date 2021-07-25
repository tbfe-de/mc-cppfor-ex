# A Counter Chain Connected via References

Using references instead of pointers to chain the counters.

* PRO-s:
  * Some space is saved in counters (now: `LimitCounter`) that
    are NOT actually chained.
  * No run-time tests required to decide whether the chained
    counter need to be incremented or reset.

* CON-s:
  * If virtual member functions aren't necessary for any other
    reasons, the "saved space" comes back via the VMT-pointer
    which is added as "hidden data member" to each class using
    "runtime polymorphism" (aka. "late binding").

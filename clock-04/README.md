# Apply NVI-Idiom ("Non-Virtual Interface")

This solution not only shows "NVI" to the minimal amount
necessary to solve forwarding "overflows" and "resets" but
already provided more extension points … just "in case".

- PRO-s:
  - More flexibility / adaptability

- CON-s:
  - Potentially calls to many subroutines that do nothing
    but return immediately if many of the provided extension
    points aren't actually used.

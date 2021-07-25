To advance to the next step apply the following changes:

* Add an interface `ICounter` to class `LimitCounter`,
  with the member functions `Count` and `Reset`.
  * in the interface these need to be pure `virtual` but
  * to keep with the NVI-idiom in `LimitCounter` these should
    be `override final`

If you are good with the above, start right away. Otherwise,
if you need a bit more of guidance, read on.

Adding an Interface to class `LimitCounter`means you first add
a new file defining the interface. It can look a bit like this
(of course, this needs to be wrapped in the usual include guards
and the new file must be included at the appropriate places):

    // ----------------------------------
    class ICounter {
        virtual ~ICounter() =delete;
        virtual void Count() =0;
        virtual void Reset() =0;
    };
    // ----------------------------------

* Having `LimitCounter` implement that interface means as little
  as changing it like below. The current content can stay as it
  was unless you want to indicate which member functions implement
  some interface function (using `override`) and that your design
  follows the NVI idiom (using `final`) at the appropriate places.

    // ----------------------------------
    class LimitCounter : public ICounter {
        ...
    };
    // ----------------------------------

One purpose of that interface is to use it for the chain counter
reference, so the actual counter coupled to lower stages gets more
freedom what it can be.

* This requires TWO changes to `OverflowCounter`:
  * Once as type for `next_counter_`
  * Second as consructor argument type!

=================================================================

Optional/Advanced

Discuss based on the LSP – ie. each DERIVED class (when accessed
via reference or pointer) – may be used in place of any (direct
or indirect) of its BASE classes (including interfaces:

* Which classes can currently be used in place of which other
  classes (or interfacesa

NOTE: The following question may be "theoretically"  answereds
      based on the LSP only, but the MINIMAL way to IMPLEMENT it
      requires the use of private inheritance combined with
      virtual base classes, so its defintely NOT for beginners.

* If `OverflowCounter` should only usable in place of `ICounter`
  but NOT in place or `LimitCounter`, with which changes could
  this be achieved?

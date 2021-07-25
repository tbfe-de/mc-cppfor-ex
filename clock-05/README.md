Adding an Interface `ICounter`
------------------------------

The inheritance here is:

+-----------------+
|  <<interface>>  |
|    ICounter     |
|                 |
+--------.--------+
        /_\
         |
         |
+-----------------+
|   <<class>>     |
|  LimitCounter   |
|                 |
+--------.--------+
        /_\
         |
         |
+-----------------+
|    <<class>>    |
| OverflowCounter |
|                 |
+-----------------+

The interface `ICounter` is implemented by `LimitCounter`, which
subsequently defines the extension points and is THE BASE CLASS
of `OverflowCounter` (= Inheritance) which fills the extension
points to implement the added behavior.

As derived class `OverflowCounter` ALSO INHERITS the interface
implementations from `LimitCounter`. But as the public members
there are `final` (as the following the NVI-idiom recommends.)

From the viewpoint of the LSP `OverflowCounter` also IS A
`LimitCounter`.

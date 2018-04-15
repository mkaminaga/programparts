Liner Quaternary Tree.

This is the implementation of the Liner Quaternary Tree (LQT) algorithm.
The one of the sample implementation of the LQT is available form the following:
http://marupeke296.com.

I added the new feature, the serial number.
The serial number is used to reduce the search path in the collision list
generation. Each cell in the tree has a serial number, which is updated when
a new object is pushed to the cell. The cell with the latest serial number is
counted to the collision list generation, though the cell with the old serial
number is not counted in the collision list generation. When the collision list
is generated, serial number of the tree is updated.

I also changed the collision list generation method.
The original sample of the above URL implemented the tree routing with a
reclusive method. My tree search is implemented without the reclusive method, so
the cost of function call may be reduced.

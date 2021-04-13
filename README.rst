Arduino simpleRPC API client library for C++
============================================

This library provides a simple way to interface to Arduino_ functions exported
with the simpleRPC_ protocol. The exported method definitions are communicated
to the host, which is then able to generate an API interface using this
library.

**Features:**

- User friendly API library.
- Function signatures are defined on the Arduino.
- RPC methods are *type safe*.

Please see ReadTheDocs_ for the latest documentation.


Quick start
-----------

Installation
^^^^^^^^^^^^

Fetch the source and compile the library.

::

    git clone https://github.com/jfjlaros/cpp-simple-rpc.git
    cd cpp-simple-rpc/src
    make

This will create the library (``libsimpleRPC.a``) and a command line utility
(``generate``) which is needed to generate a header file for your project.

Usage
^^^^^

You can find an example project in ``examples/demo``. This demonstration should
work when the Arduino device name is ``/dev/ttyACM0`` and the simpleRPC demo_
project is loaded.

To modify this example:

- Edit ``Makefile``, change ``DEVICE``, ``BAUDRATE`` and ``WAIT`` to match your
  configuration.
- Connect the Arduino and recreate ``device.h``.

::

    make header

The file ``device.h``, should now contain your local configuration and all
function signatures of the exported RPC methods.

You can now modify the client code:

- Edit ``demo.cc``, replace all ``call`` invocations by ones that match your
  project.
- Recompile your project.

::

    make


.. _Arduino: https://www.arduino.cc
.. _demo: https://github.com/jfjlaros/simpleRPC/tree/master/examples/demo
.. _simpleRPC: https://simpleRPC.readthedocs.io

Arduino simpleRPC API client library for C++
============================================

This library provides a simple way to interface to Arduino_ functions exported
with the simpleRPC_ protocol. The exported method definitions are communicated
to the host, which is then able to generate an API interface using this
library.

**Features:**

- User friendly API library.
- Function signatures are defined on the Arduino.

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

This will create the library ``libsimpleRPC.a``.

Usage
^^^^^

You can find an example project in ``examples/demo``. This demonstration should
work when the Arduino device name is ``/dev/ttyACM0`` and the simpleRPC demo_
project is loaded.

To modify this example:

- Edit ``demo.cc``, replace all ``call`` invocations by ones that match your
  project.
- Recompile your project.

::

    make


.. _Arduino: https://www.arduino.cc
.. _demo: https://github.com/jfjlaros/simpleRPC/tree/master/examples/demo
.. _simpleRPC: https://simpleRPC.readthedocs.io

.. Orca documentation master file, created by
   sphinx-quickstart on Sun Jun 20 10:59:18 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Orca
===============

.. image:: /images/logo-dropshadow.svg

A Multi-REST API library that is easy to reason about, easy to debug, and easy to use.

**Features:**

- Easy to reason about the code

  - We use the most native data structures, the simplest algorithms, and intuitive interfaces.

- Easy to debug (networking and logic) errors

  - Extensive assertion and logging facilities.

- Easy to use for the end users

  - We provide internal synchronization so that the user may provide
    scalability to his applications without having to excessively worry
    about race-conditions. All transfers made with Orca are thread-safe by nature.

Documentation
-------------

.. toctree::
   :maxdepth: 2

   apis/index

   common/index

Help
----

* :ref:`genindex`

..
  * :ref:`modindex`
  * :ref:`search`

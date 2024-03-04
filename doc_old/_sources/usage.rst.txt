Getting Started with Tomtag
==============================

Tomtag is intended as an efficient tool to identify correlated timetags between multiple channels.
It is equipped to deal with up to 4 channels to find four-fold coincidences, but can easily be extended to arbitrary numbers.

You will need some information about the timetagging device and your experimental specs:

* Timetag precision
* Coincidence window (as an integer multiple of the precision)

The only input it expects are lists of integer timetags, and this coincidence window.
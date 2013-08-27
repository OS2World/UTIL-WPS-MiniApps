Contents
--------

This distribution contains the following small applications:

	PMtime
	PMdate
	PMuptime

Each of these applications provides a small window containing
an item of information; time, date, and machine up-time
respectively.


Using
-----

There is a popup menu associated with each application
window, and this can be obtained by clicking on the window 
with mouse button 2.  Selecting the Float menuitem will
cause the window to periodically attempt to pop itself to
the front of the screen display.  

The windows can be positioned by dragging them with mouse
button 1, and the font and colour palette drag'n'drop
operations are supported.

The applications have deliberately been made as simple
as possible, but feel free to build on them if you have
the time and inclination.


Source
------

Full C++ source code for the three applications is supplied.
Feel free to use it for whatever you want.

The code compiles under Borland C++ v1.0 for OS/2, and should
also be easy to get to compile with IBM's Cset/2++ and the
various gcc environments.

If you've got any questions about any bits of the source,
I can be contacted at the email address at the end of this
file.


Known problems
--------------

If you select the Float menuitem, then the Lockup program
will not function correctly.  The lockup timer seems to
be reset every time a window changes its depth.


Disclaimer
----------

The authors accept no responsibility for any adverse effects
caused by the use or misuse of this software.


// J.R.Shannon // 4th June 1993 // jrs1@ukc.ac.uk //
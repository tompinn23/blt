blt 🥪
***

blt is a library that implements an almost perfect copy of `bearlibterminal <http://foo.wyrd.name/en:bearlibterminal>`.

The major difference is that I implement a small subset of the configuration options.
As I need them. Other than that you should be able to dump it straight into any program using bearlibterminal.

blt is a terminal output library that emulates a standard terminal using SDL2 and SDL-gpu.
It has bindings for C/C++, C#, Python and more.

It will feature support for: 
 * TTF Fonts.
 * Bitmap fonts.
   * libtcod layout.
   * square layout.
 * Multiple layers.
 * Access to the internal SDL for advanced manipulation.


Building blt.
*************

To build blt you use cmake available `here <https://cmake.org>`

First obtain the source with:
:: 
   git clone https://github.com/tompinn23/blt.git


Linux
#####

Run the following commands:
::
   mkdir build
   cd build
   cmake -DCMAKE_BUILD_TYPE=Release ..
   make

Windows
#######

Run the following commands in the visual studio dev terminal:
::
   md build
   cd build
   cmake -DCMAKE_BUILD_TYPE=Release ..
   msbuild


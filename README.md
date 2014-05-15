SA-MP Streamer Plugin
=====================

This plugin streams objects, pickups, checkpoints, race checkpoints, map icons, and 3D text labels at user-defined server ticks. Basic area detection is also included. Because it is written entirely in C++, much of the overhead from PAWN is avoided. This streamer, as a result, is quite a bit faster than any other implementation currently available in PAWN.

Compilation (Windows)
---------------------

Open the solution file (streamer.sln) in Microsoft Visual Studio 2010 (or higher). Build the project.

To generate project files for a different version of Visual Studio, download Premake 5.x (or higher), and type "premake5 vs20xx" (where "xx" completes the version number, as in "vs2010") in the top directory.

Compilation (Linux)
-------------------

Install the GNU Compiler Collection and GNU Make. Type "make" in the top directory to compile the source code.

To generate the GNU makefiles again, download Premake 4.x (or higher), and type "premake4 gmake" in the top directory.

Download
--------

The latest binaries for Windows and Linux can be found [here](https://github.com/samp-incognito/samp-streamer-plugin/releases).

Documentation
-------------

More information can be found in the [SA-MP forum thread](http://forum.sa-mp.com/showthread.php?t=102865) as well as the README file in the binary package.
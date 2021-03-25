### About newlib

The application depends on libc.a and libm.a from newlib so we ported newlib-4.1.0.

You can get more information from libc/sys/rtt. It contains syscalls and signal that RT-Thread support

To build the library, you can simply follow the compiling instruction of newlib. If it is hard for understanding, you can just follow my steps below.

### How to build the library

You can build newlib in this manner: Newlib is very pesky about the compiler and configure will not be happy when you set target to arm-rtt. So use this hack to get it to work (it worked fine for me).

```
cd ${PATH_TO_TOUR_TOOLCHAINS}

# the name of your toolchains may be not same as mine
# according to your actual situation to modify the name
# root privilege may be required
ln arm-none-eabi-ar arm-rtt-eabi-ar
ln arm-none-eabi-as arm-rtt-eabi-as
ln arm-none-eabi-gcc arm-rtt-eabi-gcc
ln arm-none-eabi-gcc arm-rtt-eabi-cc
ln arm-none-eabi-ranlib arm-rtt-eabi-ranlib

# return
cd -
```

Then run the following commands to build newlib. Note that the `FULL_PATH_TO_LIBRARY` indicated the path that library will be installed, it must be an absolute path.

```
mkdir build && cd build
../configure --target=arm-rtt-eabi --prefix=${FULL_PATH_TO_LIBRARY} --with-float=soft
make all-target-newlib  # wait for a while
make install-target-newlib
```

Now the library has been installed and you can set `NEWLIB_PATH` in Makefile.common to the path you indicated.

----

		   README for GNU development tools

This directory contains various GNU compilers, assemblers, linkers, 
debuggers, etc., plus their support routines, definitions, and documentation.

If you are receiving this as part of a GDB release, see the file gdb/README.
If with a binutils release, see binutils/README;  if with a libg++ release,
see libg++/README, etc.  That'll give you info about this
package -- supported targets, how to use it, how to report bugs, etc.

It is now possible to automatically configure and build a variety of
tools with one command.  To build all of the tools contained herein,
run the ``configure'' script here, e.g.:

	./configure 
	make

To install them (by default in /usr/local/bin, /usr/local/lib, etc),
then do:
	make install

(If the configure script can't determine your type of computer, give it
the name as an argument, for instance ``./configure sun4''.  You can
use the script ``config.sub'' to test whether a name is recognized; if
it is, config.sub translates it to a triplet specifying CPU, vendor,
and OS.)

If you have more than one compiler on your system, it is often best to
explicitly set CC in the environment before running configure, and to
also set CC when running make.  For example (assuming sh/bash/ksh):

	CC=gcc ./configure
	make

A similar example using csh:

	setenv CC gcc
	./configure
	make

Much of the code and documentation enclosed is copyright by
the Free Software Foundation, Inc.  See the file COPYING or
COPYING.LIB in the various directories, for a description of the
GNU General Public License terms under which you can copy the files.

REPORTING BUGS: Again, see gdb/README, binutils/README, etc., for info
on where and how to report problems.

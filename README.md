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

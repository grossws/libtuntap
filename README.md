# libtuntap -- TUN/TAP adapter library for Linux

## Requirments
* Linux 2.6+ (should work in 2.4, but I haven't tested)
* Python 2.7+/3.2+
* gcc 4.x (for build)
* python-distutils

## API

### C
To use C API just `#include "tuntap.h"` and add `tuntap.c` to your project.

### Python
To use Python API build module with

    python setup.py build

and use resulting `tuntap.so` file in your project.

After `import tuntap` tou can use `tap_open` and `tun_open`.
They open `FileIO` in `r+b` mode, so you can use

    f.read(MAX_PACKET_SIZE)

to read _raw ethernet frame_ from TAP device or _raw IP frame_ from TUN.

## License
This library is distributed under terms of BSD License.


# Typotronic
Reads a target string as well as the string actually typed by the user, and scores it based on the typos made.

## Building
To build the `typo` executable:
```
mkdir build
cd build
cmake ..
make
cd ..
```

And to run:
```
./build/typo/typo
```

**Build Mode** can be changed by passing CMake the `-DCMAKE_BUILD_TYPE=[RELEASE|DEBUG]` flag.

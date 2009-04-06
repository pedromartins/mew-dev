#!/bin/bash

# This little script will build the entire system
# according to the CMakeLists.txt provided, and
# then test it, reporting any failures in an insanely
# verbose manner.

cmake ../
make
ctest -V

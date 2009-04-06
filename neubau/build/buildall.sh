#!/bin/bash

# This file makes makefiles,
# makes the project
# and then tests it.

cmake ../
make
ctest -V

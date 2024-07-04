#!/bin/sh
gcc src/crate/*.cpp -o src/crate/crate -lstdc++
./src/crate/crate src/crate/sample.crate
gzip man/man1/crate.1 -kf19

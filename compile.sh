#!/bin/sh
gcc src/crate/*.cpp -o src/crate/crate -lstdc++
./src/crate/crate sample.crate
gzip man/man1/crate.1 -kf19
man -l man/man1/crate.1.gz

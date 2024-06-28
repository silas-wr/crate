#!/bin/sh
gcc crate/*.cpp -o crate/crate -lstdc++
./crate/crate sample.crate
gzip man/man1/crate.1 -kf19
man -l man/man1/crate.1.gz

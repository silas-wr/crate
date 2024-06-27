#!/bin/sh
gcc crate/main.cpp crate/lex.cpp -o crate/crate -lstdc++
./crate/crate
gzip man/man1/crate.1 -kf19
man -l man/man1/crate.1.gz

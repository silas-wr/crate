#!/bin/sh
gcc crate/main.c crate/lex.c
gzip man/man1/crate.1 -kf19
man -l man/man1/crate.1.gz

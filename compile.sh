#!/bin/sh
javac com/crate/Main.java
java com.crate.Main sample.crate
gzip man/man1/crate.1 -kf19
man -l man/man1/crate.1.gz

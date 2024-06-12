#!/bin/sh
javac com/crate/Main.java
gzip man/man1/crate.1 -kf19

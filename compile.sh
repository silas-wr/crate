#!/bin/sh
javac com/crate/Main.java
jar --create --manifest=com/crate/META-INF/MANIFEST.MF --file=lib/crate.jar
gzip man/man1/crate.1 -kf19
native-image com.crate.Main -o bin/crate

# The Crate Programming Language

[![CodeQL](https://github.com/silas-wr/crate/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/silas-wr/crate/actions/workflows/github-code-scanning/codeql) [![C++ Project Build](https://github.com/silas-wr/crate/actions/workflows/cppbuild.yml/badge.svg)](https://github.com/silas-wr/crate/actions/workflows/cbuild.yml)

## Overview

The Crate Programming Language is a language geared towards container programming and data analysis.
Its syntax is similar to that of the Java programming language. However, it does incorporate some aspects of Python.
My goal with **crate** is to reach both low and high levels in programming.

## History

The Crate Programming Language originated (in my mind) when I decided I wanted to be able to run a container _within_ my code. Moreover, I wanted to be able to control the _permissions_ of the container, as well as letting the container manage its variables. In short, I wanted what I've termed a _self-contained environment_. So that's why I decided to make Crate. I didn't know where to start so naturally I started with the language I'm most familiar with: Python. Afterwards, I decided to move closer to C/C++. Since I didn't know either, I started with Java. Now, I've begun to learn C and C++ with books and the Internet.

## Moving from Java to C/C++

Although my project still has a `com/crate/*.java` structure, I will eventually delete those files. My sample input file is `src/crate/sample.crate`, but you can find more complete programs in the `samples/` directory.

## Example in crate

The example below can be found at `samples/com/myproject/authentication.crate` to demonstrate a package in crate.

```
$ Sample program in crate
$ What we're aiming for here is a program that lets us do anything in an authenticated environment.
$ We'll use a wrapper to authenticate, and a crate (a container within our program) that lets us do stuff with our User self.

package com::myproject;  $ thing::user is of type User, which comes from this package
import crate::secure::*; $ import Hash class

wrapper auth(thing) {
    func __init__(self, thing) {
        $ Hash
        private self::hsh << Hash;

        $ Require authentication of the user
        self::hsh : hash( thing::user::req("PASSWORD") );

        $ Authenticate
        if (self::hsh == thing::user::hash) {
            ; 
        } else {
            raise Exception("Authentication faliure");
        }

        return 0;   $ fall into the object being authenticated     
    }

    func __exit__(self) {
        $ Hide everything
        del self::hsh;
    }
}

@auth crate SecureEnv {   $ use our authentication
    func __init__(self) {
        self::user << User : User(); $ create a user (with whatever method myproject defines)
    }

    func myfunc(self) {
        $ do anything here, knowing that you've been authenticated
    }
}
```

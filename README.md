# The Crate Programming Language

[![CodeQL](https://github.com/silas-wr/crate/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/silas-wr/crate/actions/workflows/github-code-scanning/codeql) [![C++ Project Build](https://github.com/silas-wr/crate/actions/workflows/cbuild.yml/badge.svg)](https://github.com/silas-wr/crate/actions/workflows/cbuild.yml)

## Overview

The Crate Programming Language is a language geared towards container programming and data analysis.
Its syntax is similar to that of the Java programming language. However, it does incorporate some aspects of Python.
My goal with **crate** is to reach both low and high levels in programming.

## Example in crate

```
$ Sample program in crate
$ What we're aiming for here is a program that lets us do anything in an authenticated environment.
$ We'll use a wrapper to authenticate, and a crate (a container within our program) that lets us do stuff with our User self.

package com::myproject;  $ thing::user is of type User, which comes from this package
import crate::secure::*; $ import Hash class

wrapper auth(thing)
{
    func __init__(self, thing)
    {
        $ Hash
        private self::hsh << Hash;

        $ Require authentication of the user
        self::hsh : hash( thing::user::req("PASSWORD") );

        $ Authenticate
        if (self::hsh = thing::user::hash)
        {
            ; 
        } else
        {
            raise Exception("Authentication faliure");
        }

        return 0;   $ fall into the object being authenticated     
    }

    func __exit__(self)
    {
        $ Hide everything
        del self::hsh;
    }
}

@auth crate SecureEnv     $ use our authentication
{
    func __init__(self)
    {
        self::user << User : User(); $ create a user (with whatever method myproject defines)
    }

    func myfunc(self) {
        $ do anything here, knowing that you've been authenticated
    }
}
```

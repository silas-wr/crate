package com.crate;

public enum NodeTypes {
    BASE_ID,
    BASE_CONST,
    BASE_TCONST, // constant
    BASE_TSTR, // string
    BASE_TCHR, // character
    BASE_TBYT, // byte
    BASE_TSHR, // short
    BASE_TINT, // integer
    BASE_TFLT, // floating point / double
    BASE_TLIS, // list
    BASE_TDIC, // dictionary
    BASE_TSET, // set (immutable list)
    BASE_TCDC, // immutable dictionary
    BASE_TBLN, // boolean
    BASE_NULL, // null
    BASE_TTYP, // type
    BASE_TALL, // any (#)
    STEM_ASSIGN,
    STEM_TYPIFY,
    ROOT_ASSIGN,
    GR_TYPIFY,
    NODE_ASSIGN,
    NODE_TYPIFY,
}

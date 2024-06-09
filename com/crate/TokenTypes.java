package com.crate;

public enum TokenTypes {
    // Variable tokens
    ID, // This is our token for all identifiers    ([A-Za-z_]*[A-Za-z0-9_]+)
    CONST, // Constants
    IS, // We"ll use this for assignment statements (:)
    TYPE, // We"ll use this to set a type (think int x = 0;) ( << )
    ATTR, // Commonly known as square (::)
    RTYP, // Required type ( >> )

    // Type names
    TCONST, // constant
    TSTR, // string
    TCHR, // character
    TBYT, // byte
    TSHR, // short
    TINT, // integer
    TFLT, // floating point / double
    TLIS, // list
    TDIC, // dictionary
    TSET, // set (immutable list)
    TCDC, // immutable dictionary
    TBLN, // boolean
    NULL, // null
    TTYP,
    TALL, // any (#)

    // Num types
    BYTE, // byte sized num (u_byte or s_byte)
    SHORT, // short sized num (u_short or s_short)
    INT, // int sized num (u_int or s_int)
    FLOAT, // floating point integer

    // Num signature
    UB,
    US,
    UI,
    SB,
    SS,
    SI,

    // Other types
    STR,
    CHR,
    LIST,
    SET,
    DICT,
    CDIC,
    BOOL,
    NUL,

    // Control
    IMPORT,
    FROM,
    IN,
    IF,
    ELIF,
    ELSE,
    WHILE,
    DO,
    SWITCH,
    CASE,
    DEFAULT,
    TRY,
    EXCEPT,
    WITH,
    LAMBDA,

    // Operators
    SUM,
    SUB,
    MUL,
    DIV,
    MOD,
    PP,
    SUMBY,
    MM,
    SUBBY,
    MULBY,
    DIVBY,
    MODBY,
    EXPBY,
    EXP,
    BAND,
    BOR,
    XOR,
    AND,
    OR,

    // Questions
    GT,
    LT,
    EQ,
    GE,
    LE,
    NE,
    NOT,
    DIAMOND,

    // Parse nibbles
    OPAR,
    CPAR,
    OBRK,
    CBRK,
    OBRC,
    CBRC,
    COMMA,
    SEMI,
    EOL,
    EOF, 

    // Data structure keywords
    WRAP,
    FUNC, 
    CLASS, 
    CRATE, 
    STRUCT,

    // Booleans
    TRUE,
    FALSE,
}

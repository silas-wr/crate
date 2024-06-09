package com.crate;

public class Token {
    TokenTypes type;
    String content;
    int row;
    int col;
    
    Token (TokenTypes typ, String cont, int r, int c) {
	    type = typ;
	    content = cont;
	    row = r;
        col = c;
    }
}

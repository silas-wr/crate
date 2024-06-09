package com.crate;

import java.io.*;
import java.util.*;

public class Lex {
    public static List<Token> lex(FileInputStream file) {
        List<Token> result = new ArrayList<>();
        Map<String, TokenTypes> keys = new HashMap<>();

        keys.put("str", TokenTypes.TSTR);
        keys.put("char", TokenTypes.TCHR);
        keys.put("byte", TokenTypes.TBYT);
        keys.put("short", TokenTypes.TSHR);
        keys.put("int", TokenTypes.TINT);
        keys.put("double", TokenTypes.TFLT);
        keys.put("list", TokenTypes.TLIS);
        keys.put("dict", TokenTypes.TDIC);
        keys.put("set", TokenTypes.TSET);
        keys.put("cdic", TokenTypes.TCDC);
        keys.put("bool", TokenTypes.TBLN);
        keys.put("null", TokenTypes.NULL);
        keys.put("#", TokenTypes.TALL);
        keys.put("func", TokenTypes.FUNC);
        keys.put("class", TokenTypes.CLASS);
        keys.put("crate", TokenTypes.CRATE);
        keys.put("struct", TokenTypes.STRUCT);
        keys.put("if", TokenTypes.IF);
        keys.put("elif", TokenTypes.ELIF);
        keys.put("else", TokenTypes.ELSE);
        keys.put("while", TokenTypes.WHILE);
        keys.put("do", TokenTypes.DO);
        keys.put("switch", TokenTypes.SWITCH);
        keys.put("case", TokenTypes.CASE);
        keys.put("default", TokenTypes.DEFAULT);
        keys.put("try", TokenTypes.TRY);
        keys.put("except", TokenTypes.EXCEPT);
        keys.put("with", TokenTypes.WITH);
        keys.put("u_byte", TokenTypes.UB);
        keys.put("u_short", TokenTypes.US);
        keys.put("u_int", TokenTypes.UI);
        keys.put("s_byte", TokenTypes.SB);
        keys.put("s_short", TokenTypes.SS);
        keys.put("s_int", TokenTypes.SI);
        keys.put("const", TokenTypes.TCONST);
        keys.put("true", TokenTypes.TRUE);
        keys.put("false", TokenTypes.FALSE);
        keys.put("import", TokenTypes.IMPORT);
        keys.put("from", TokenTypes.FROM);
        keys.put("in", TokenTypes.IN);
        keys.put("type", TokenTypes.TTYP);
	
	Map<String, TokenTypes> relatives = new HashMap<>();

        relatives.put("<<", TokenTypes.TYPE);
        relatives.put(">>", TokenTypes.RTYP);
        relatives.put("<>", TokenTypes.DIAMOND);
        relatives.put(">=", TokenTypes.GE);
        relatives.put("=<", TokenTypes.LE);
        relatives.put("=>", TokenTypes.LAMBDA);
        relatives.put("==", TokenTypes.EQ);
        relatives.put("!=", TokenTypes.NE);
        relatives.put("!!", TokenTypes.NOT);
        relatives.put("<", TokenTypes.LT);
        relatives.put(">", TokenTypes.GT);

        Map<String, TokenTypes> ops = new HashMap<>();

        ops.put("&", TokenTypes.BAND);
        ops.put("|", TokenTypes.BOR);
        ops.put("^", TokenTypes.XOR);
        ops.put("&&", TokenTypes.AND);
        ops.put("||", TokenTypes.OR);
        ops.put("+", TokenTypes.SUM);
        ops.put("-", TokenTypes.SUB);
        ops.put("*", TokenTypes.MUL);
        ops.put("/", TokenTypes.DIV);
        ops.put("%", TokenTypes.MOD);
        ops.put("++", TokenTypes.PP);
        ops.put("--", TokenTypes.MM);
        ops.put("**", TokenTypes.EXP);
        ops.put("//", TokenTypes.DIVBY);
        ops.put("%%", TokenTypes.MODBY);
        ops.put("+&", TokenTypes.SUMBY);
        ops.put("-&", TokenTypes.SUBBY);
        ops.put("**&", TokenTypes.EXPBY);
        ops.put("*&", TokenTypes.MULBY);
	
        String alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_#";
        String numb = "0123456789";
        String whit = " \n    \r;{[()]},@\";' ";
        String bytes = "0123456789ABCDEFabcdef";
        String octs = "01234567";
        String bin = "01";
        String content = "";
        boolean load_bin = false;
        boolean load_comm = false;
        boolean load_str = false;
        boolean load_chr = false;
        boolean load_esc = false;
        boolean load_byte = false;
        boolean load_oct = false;
    	String load_var = "";
        String load_type = "";
        char cur_char;
        int load_col = 0;
        int load_row = 1;
        int i;
        FileInputStream fi = file;
        boolean done = false;
        boolean strloaded = false;
        boolean chrloaded = false;
        boolean chrfull = false;
        int bytefull = 2;
        boolean byteable = false;
        boolean octable = false;
        boolean binable = false;
        boolean eol = false;


	try {
	    do {
	        i = fi.read();
	        if (i != -1) {
	            content += (char) i;
	        }
	    } while (i != -1);
		
	} catch (IOException exc) {
            System.out.println("Error reading file.");
        }
        
        try {
            fi.close();
        } catch (IOException ex) {
            System.out.println("Error closing file.");
            
        }

	for (int total = 0 ; total < content.length() ; total++) {
	    cur_char = content.charAt(total);
            done = false;
            strloaded = false;
            chrloaded = false;

            if (cur_char == '\n') {
                eol = true;
                load_col = 0;
                load_row ++;
            } else {
                load_col ++;
            }

            if (load_comm & cur_char != '\n') {
                
            } else if (load_str) {
                if (cur_char == '\\' & load_esc != true) {
                    load_var += cur_char;
                    strloaded = true;
                    load_esc = true;
                } else if (cur_char == '\\' & load_esc) {
                    load_var += cur_char;
                    strloaded = true;
                    load_esc = false;
                } else if (cur_char != '\\' & load_esc) {
                    load_var += cur_char;
                    strloaded = true;
                    load_esc = false;
                }

                if (cur_char == '"' & strloaded != true) {
                    load_var += cur_char;
                    strloaded = true;
                    result.add(new Token(TokenTypes.STR, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                    load_str = false;
                }
                if (cur_char != '"' & strloaded != true) {
                    load_var += cur_char;
                    strloaded = true;
                }

            } else if (load_chr) {
                if (cur_char == '\'' & chrfull != true & load_esc != true) {
                    Err.err(load_row, load_col, "Invalid character literal. No character specified, or incomplete unicode. (try \\uxxxx)");
                }

                if (cur_char != '\'' & chrfull == true) {
                    Err.err(load_row, load_col, "Invalid character literal. Multiple characters specified.");
                }
                
                if (cur_char == '\\' & load_esc != true & chrfull != true & chrloaded != true) {
                    load_var += cur_char;
                    chrloaded = true;
                    load_esc = true;
                } else if (load_esc & chrfull != true & chrloaded != true) {
                    load_var += cur_char;
                    chrloaded = true;
                    load_esc = false;
                    chrfull = true;
                }

                if (cur_char == '\'' & chrloaded != true & chrfull == true) {
                    load_var += cur_char;
                    chrloaded = true;
                    result.add(new Token(TokenTypes.CHR, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                    load_chr = false;
                }
                if (cur_char != '\'' & chrloaded != true & chrfull != true & load_esc != true) {
                    load_var += cur_char;
                    chrloaded = true;
                    chrfull = true;
                }

            } else if (bin.indexOf(cur_char) != -1 & load_bin) {
                load_var += cur_char;
            } else if (octs.indexOf(cur_char) != -1 & load_oct) {
                load_var += cur_char;
            } else if (bytes.indexOf(cur_char) != -1 & load_byte) {
                if (bytefull == 0) {
                    load_type = "int";
                }
                load_var += cur_char;
                bytefull -= 1;

            } else if (alpha.indexOf(cur_char) != -1) {
                if (byteable & cur_char == 'x') {
                    load_var += cur_char;
                    load_type = "byte";
                    load_byte = true;
                    byteable = false;
                    octable = false;
                    binable = false;
                } else if (octable & cur_char == 'o') {
                    load_var += cur_char;
                    load_type = "int";
                    load_oct = true;
                    octable = false;
                    byteable = false;
                    binable = false;
                } else if (binable & cur_char == 'b') {
                    load_var += cur_char;
                    load_type = "int";
                    load_bin = true;
                    octable = false;
                    byteable = false;
                    binable = false;
                } else if (load_type == "int" | load_type == "double" | load_type == "byte") {
                    Err.err(load_row, load_col, "Cannot begin identifier with number");
                } else if (load_type == "id") {
                    load_var += cur_char;
                } else if (load_type == "relative") {
                    if (relatives.get(load_var) != null) {
                        result.add(new Token(relatives.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                    } else {
                        Err.err(load_row, load_col, "Invalid relative: " + load_var);
                    }
                } else if (load_type == "operator") {
                    if (ops.get(load_var) != null) {
                        result.add(new Token(ops.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                    } else {
                        Err.err(load_row, load_col, "Invalid operator: " + load_var);
                    }
                } else if (load_type == "colon") {
                    result.add(new Token(TokenTypes.IS, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                }
                if (load_var == "" & load_type == "") {
                    load_var += cur_char;
                    load_type = "id";
                }
            } else if (numb.indexOf(cur_char) != -1) {        
            	if (load_type == "int" | load_type == "double") {
                    load_var += cur_char;
                } else if (load_type == "id") {
                    load_var += cur_char;
                } else if (load_type == "relative") {
                    if (relatives.get(load_var) != null) {
                        result.add(new Token(relatives.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                    } else {
                        Err.err(load_row, load_col, "Invalid relative: " + load_var);
                    }
                } else if (load_type == "operator") {
                    if (ops.get(load_var) != null) {
                        result.add(new Token(ops.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                    } else {
                        Err.err(load_row, load_col, "Invalid operator: " + load_var);
                    }
                } else if (load_type == "colon") {
                    result.add(new Token(TokenTypes.IS, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                }
                if (load_var == "" & load_type == "") {
                    load_var += cur_char;
	            load_type = "int";
                    if (cur_char == '0') {
                        byteable = true;
                        octable = true;
                        binable = true;
                    }
	        }
            } else if (cur_char == '>' | cur_char == '<' | cur_char == '=' | cur_char == '!') {
                if (load_type == "relative") {
                    load_var += cur_char;
                    if (relatives.get(load_var) != null) {
                        result.add(new Token(relatives.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                        done = true;
                    } else {
                        Err.err(load_row, load_col, "Invalid relative: " + load_var);
                    }
                } else if (load_var != "" & load_type == "int") {
                    result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                    load_byte = false;
                    load_bin = false;
                    load_oct = false;
                } else if (load_var != "" & load_type == "double") {
                    result.add(new Token(TokenTypes.FLOAT, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                } else if (load_var != "" & load_type == "id") {
                    if (keys.get(load_var) != null) {
                        result.add(new Token(keys.get(load_var), load_var, load_row, load_col));
                    } else if (load_var.toUpperCase() == load_var) {
                        result.add(new Token(TokenTypes.CONST, load_var, load_row, load_col));
                    } else {
                        result.add(new Token(TokenTypes.ID, load_var, load_row, load_col));
                    }
                    load_var = "";
                    load_type = "";
                } else if (load_var != "" & load_type == "operator") {
                    if (ops.get(load_var) != null) {
                        result.add(new Token(ops.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                    } else {
                        Err.err(load_row, load_col, "Invalid operator: " + load_var);
                    }
                } else if (load_var != "" & load_type == "colon") {
                    result.add(new Token(TokenTypes.IS, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                } else if (load_var != "" & load_type == "byte") {
                    if (bytefull != 0) {
                        result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
                    } else {
                        result.add(new Token(TokenTypes.BYTE, load_var, load_row, load_col));
                    }
                    load_var = "";
                    load_type = "";
                    load_byte = false;
                    bytefull = 2;
                }
                if (load_var == "" & load_type == "" & done == false) {
                    load_var += cur_char;
                    load_type = "relative";
                }      
            } else if (cur_char == '&' | cur_char == '|' | cur_char == '^' | cur_char == '+' | cur_char == '-' | cur_char == '*' | cur_char == '/' | cur_char == '%') {
                if (load_type == "relative") {
                    load_var += cur_char;
                    if (relatives.get(load_var) != null) {
                        result.add(new Token(relatives.get(load_var), load_var, load_row, load_col));
                    } else {
                        Err.err(load_row, load_col, "Invalid relative: " + load_var);
                    }
                    load_var = "";
                    load_type = "";
                } else if (load_var != "" & load_type == "int") {
                    result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                    load_byte = false;
                    load_bin = false;
                    load_oct = false;
                } else if (load_var != "" & load_type == "double") {
                    result.add(new Token(TokenTypes.FLOAT, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                } else if (load_var != "" & load_type == "id") {
                    if (keys.get(load_var) != null) {
                        result.add(new Token(keys.get(load_var), load_var, load_row, load_col));
                    } else if (load_var.toUpperCase() == load_var) {
                        result.add(new Token(TokenTypes.CONST, load_var, load_row, load_col));
                    } else {
                        result.add(new Token(TokenTypes.ID, load_var, load_row, load_col));
                    }
                    load_var = "";
                    load_type = "";
                } else if (load_var != "" & load_type == "operator") {
                    load_var += cur_char;
                    if (ops.get(load_var) != null) {
                        result.add(new Token(ops.get(load_var), load_var, load_row, load_col));
                    } else {
                        Err.err(load_row, load_col, "Invalid operator: " + load_var);
                    }
                    
                    load_var = "";
                    load_type = "";
                    done = true;
                } else if (load_var != "" & load_type == "colon") {
                    result.add(new Token(TokenTypes.IS, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                } else if (load_var != "" & load_type == "byte") {
                    if (bytefull != 0) {
                        result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
                    } else {
                        result.add(new Token(TokenTypes.BYTE, load_var, load_row, load_col));
                    }
                    load_var = "";
                    load_type = "";
                    load_byte = false;
                    bytefull = 2;
                }
                if (load_var == "" & load_type == "" & done == false) {
                    load_var += cur_char;
                    load_type = "operator";
                }
            } else if (cur_char == '.') {
                if (load_type == "int") {
                    if (load_byte != true & load_oct != true & load_bin != true) {
                        load_var += cur_char;
                        load_type = "double";
                    } else {
                        Err.err(load_row, load_col, "Invalid period on hexadecimal integer.");
                    }
                } else if (load_type == "double") {
                    Err.err(load_row, load_col, "Cannot have multiple decimal points within double.");
                } else if (load_type == "id") {
                    Err.err(load_row, load_col, "Cannot have decimal point within identifier.");
                } else if (load_type == "relative") {
                    if (relatives.get(load_var) != null) {
                        result.add(new Token(relatives.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                    } else {
                        Err.err(load_row, load_col, "Invalid relative: " + load_var);
                    }
                } else if (load_type == "operator") {
                    if (ops.get(load_var) != null) {
                        result.add(new Token(ops.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                    } else {
                            Err.err(load_row, load_col, "Invalid operator: " + load_var);
                        }
                } else if (load_type == "colon") {
                    result.add(new Token(TokenTypes.IS, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                } else if (load_var != "" & load_type == "byte") {
                    Err.err(load_row, load_col, "Invalid period on byte");
                }
                if (load_var == "" & load_type == "") {
                    load_var += cur_char;
                    load_type = "double";
                }                
            } else if (cur_char == ':') {
                if (load_type == "colon") {
                    load_var += cur_char;
                    result.add(new Token(TokenTypes.ATTR, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                    done = true;
                } else if (load_var != "" & load_type == "int") {
                    result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                    load_byte = false;
                    load_bin = false;
                    load_oct = false;
                } else if (load_var != "" & load_type == "double") {
                    result.add(new Token(TokenTypes.FLOAT, load_var, load_row, load_col));
                    load_var = "";
                    load_type = "";
                } else if (load_var != "" & load_type == "id") {
                    if (keys.get(load_var) != null) {
                        result.add(new Token(keys.get(load_var), load_var, load_row, load_col));
                    } else if (load_var.toUpperCase() == load_var) {
                        result.add(new Token(TokenTypes.CONST, load_var, load_row, load_col));
                    } else {
                        result.add(new Token(TokenTypes.ID, load_var, load_row, load_col));
                    }
                    load_var = "";
                    load_type = "";
                } else if (load_type == "relative") {
                    if (relatives.get(load_var) != null) {
                        result.add(new Token(relatives.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                    } else {
                        Err.err(load_row, load_col, "Invalid relative: " + load_var);
                    }
                } else if (load_type == "operator") {
                    if (ops.get(load_var) != null) {
                        result.add(new Token(ops.get(load_var), load_var, load_row, load_col));
                        load_var = "";
                        load_type = "";
                    } else {
                        Err.err(load_row, load_col, "Invalid operator: " + load_var);
                    }
                } else if (load_var != "" & load_type == "byte") {
                    if (bytefull != 0) {
                        result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
                    } else {
                        result.add(new Token(TokenTypes.BYTE, load_var, load_row, load_col));
                    }
                    load_var = "";
                    load_type = "";
                    load_byte = false;
                    bytefull = 2;
                }
                if (load_var == "" & load_type == "" & done == false) {
                    load_var += cur_char;
                    load_type = "colon";
                }
            } else if (cur_char == '$') {
                load_comm = true;
            } else if (whit.indexOf(cur_char) != -1) {
                load_comm = false;
                if (load_var != "" & load_type == "int") {
                    result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
                    load_byte = false;
                    load_bin = false;
                    load_oct = false;
                } else if (load_var != "" & load_type == "double") {
                    result.add(new Token(TokenTypes.FLOAT, load_var, load_row, load_col));
                } else if (load_var != "" & load_type == "id") {
                    if (keys.get(load_var) != null) {
                        result.add(new Token(keys.get(load_var), load_var, load_row, load_col));
                    } else if (load_var.toUpperCase() == load_var) {
                        result.add(new Token(TokenTypes.CONST, load_var, load_row, load_col));
                    } else {
                        result.add(new Token(TokenTypes.ID, load_var, load_row, load_col));
                    }
                } else if (load_type == "relative") {
                    if (relatives.get(load_var) != null) {
                        result.add(new Token(relatives.get(load_var), load_var, load_row, load_col));
                    } else {
                        Err.err(load_row, load_col, "Invalid relative: " + load_var);
                    }
                } else if (load_var != "" & load_type == "operator") {
                    if (ops.get(load_var) != null) {
                        result.add(new Token(ops.get(load_var), load_var, load_row, load_col));
                    } else {
                        Err.err(load_row, load_col, "Invalid operator: " + load_var);
                    }
                } else if (load_var != "" & load_type == "colon") {
                    result.add(new Token(TokenTypes.IS, load_var, load_row, load_col));
                } else if (load_var != "" & load_type == "byte") {
                    if (bytefull != 0) {
                        result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
                    } else {
                        result.add(new Token(TokenTypes.BYTE, load_var, load_row, load_col));
                    }
                    load_var = "";
                    load_type = "";
                    load_byte = false;
                    bytefull = 2;
                }

                load_var = "";
                load_type = "";

                if (cur_char == ';') {
                    result.add(new Token(TokenTypes.SEMI, ";", load_row, load_col));
                } else if (cur_char == '{') {
                    result.add(new Token(TokenTypes.OBRC, "{", load_row, load_col));
                } else if (cur_char == '[') {
                    result.add(new Token(TokenTypes.OBRK, "[", load_row, load_col));
                } else if (cur_char == '(') {
                    result.add(new Token(TokenTypes.OPAR, "(", load_row, load_col));
                } else if (cur_char == ')') {
                    result.add(new Token(TokenTypes.CPAR, ")", load_row, load_col));
                } else if (cur_char == ']') {
                    result.add(new Token(TokenTypes.CBRK, "]", load_row, load_col));
                } else if (cur_char == '}') {
                    result.add(new Token(TokenTypes.CBRC, "}", load_row, load_col));
                } else if (cur_char == ',') {
                    result.add(new Token(TokenTypes.COMMA, ",", load_row, load_col));
                } else if (cur_char == '@') {
                    result.add(new Token(TokenTypes.WRAP, "@", load_row, load_col));
                } else if (cur_char == '"') {
                    load_var += cur_char;
                    load_str = true;
                } else if (cur_char == '\'') {
                    load_var += cur_char;
                    load_chr = true;
                }
            } else {
                Err.err(load_row, load_col, "Invalid character: " + cur_char);
            } 

            if (eol) {
                result.add(new Token(TokenTypes.EOL, "eol", load_row, load_col));
                eol = false;
            }
        }

        if (load_var != "" & load_type == "int") {
            result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
            load_var = "";
            load_type = "";
            load_byte = false;
            load_bin = false;
            load_oct = false;
        } else if (load_var != "" & load_type == "double") {
            result.add(new Token(TokenTypes.FLOAT, load_var, load_row, load_col));
            load_var = "";
            load_type = "";
        } else if (load_var != "" & load_type == "id") {
            if (keys.get(load_var) != null) {
                result.add(new Token(keys.get(load_var), load_var, load_row, load_col));
            } else if (load_var.toUpperCase() == load_var) {
                result.add(new Token(TokenTypes.CONST, load_var, load_row, load_col));
            } else {
                result.add(new Token(TokenTypes.ID, load_var, load_row, load_col));
            }
            load_var = "";
            load_type = "";
        } else if (load_type == "relative") {
            if (relatives.get(load_var) != null) {
                result.add(new Token(relatives.get(load_var), load_var, load_row, load_col));
                load_var = "";
                load_type = "";
            } else {
                Err.err(load_row, load_col, "Invalid relative: " + load_var);
            }
        } else if (load_type == "operator") {
            if (ops.get(load_var) != null) {
                result.add(new Token(ops.get(load_var), load_var, load_row, load_col));
                load_var = "";
                load_type = "";
            } else {
                Err.err(load_row, load_col, "Invalid operator: " + load_var);
            }
        } else if (load_type == "colon") {
            result.add(new Token(TokenTypes.IS, load_var, load_row, load_col));
            load_var = "";
            load_type = "";
        } else if (load_str) {
            Err.err(load_row, load_col, "Unfinished string");
        } else if (load_chr) {
            Err.err(load_row, load_col, "Unfinished character");
        } else if (load_var != "" & load_type == "byte") {
            if (bytefull != 0) {
                result.add(new Token(TokenTypes.INT, load_var, load_row, load_col));
            } else {
                result.add(new Token(TokenTypes.BYTE, load_var, load_row, load_col));
            }
            load_var = "";
            load_type = "";
            load_byte = false;
            bytefull = 2;
        }

        result.add(new Token(TokenTypes.EOF, "-1", -1, -1));

	    try {
	        fi.close();
	    } catch (IOException exc) {
	        System.out.println("Error closing file.");
        }

        return result;
    }
   
}

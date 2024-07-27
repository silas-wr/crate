#include "crate.hpp"

vector<Token> lex(const string src)
{
  vector<Token> tlist;
  Token cur;

  int row = 0;
  int col = 0;
  bool eol = false;
  bool slash = false;
  bool ok = true;
  
  char c;
  
  string load_var;
  string load_type;

  string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
  string numeric = "0123456789";
  string octl = "012345678";
  string hex = "0123456789ABCDEF";
  string operators = "&|^~!=<>:+-*/%";
  string white = "{[(#?,;)]}\r\t\n ";

  bool unicode = false;
  bool octal = false;
  bool done = false;

  int uni = 4;
  int oct = 3;

  map<string, TokenTypes> keys;

  // keywords
  keys["import"] = IMPORT;
  keys["package"] = PACK;
  keys["from"] = FROM;
  keys["as"] = AS;
  keys["del"] = DEL;
  keys["assert"] = ASSERT;
  keys["return"] = RETURN;
  keys["unsigned"] = UNSIGN;
  keys["transitive"] = TRANSITIVE;
  keys["global"] = GLOBAL;
  
  // privacy
  keys["public"] = PUBLIC;
  keys["protected"] = PROTECT;
  keys["private"] = PRIVATE;
  keys["hidden"] = HIDDEN;

  // data structures
  keys["func"] = FN;
  keys["class"] = CLS;
  keys["crate"] = CRT;
  keys["struct"] = STC;

  // control
  keys["if"] = IF;
  keys["elif"] = ELIF;
  keys["else"] = ELSE;
  keys["switch"] = SWITCH;
  keys["case"] = CASE;
  keys["default"] = DEFAULT;
  keys["try"] = TRY;
  keys["except"] = EXCEPT;
  keys["while"] = WHILE;
  keys["break"] = BREAK;
  keys["continue"] = CONTINUE;

  // types
  keys["const"] = TCNT;
  keys["void"] = TNUL;
  keys["chr"] = TCHR;
  keys["str"] = TSTR;
  keys["byte"] = TBYT;
  keys["short"] = TSHR;
  keys["int"] = TINT;
  keys["long"] = TLNG;
  keys["double"] = TFLT;
  keys["type"] = TTYP;

  map<string, TokenTypes> ops;

  // assignment
  ops[":"] = IS;
  ops["::"] = ATTR;
  ops[":="] = ENUM;
  ops["<<"] = TYPE;
  ops[">>"] = RTYP;

  // pointer
  ops["~*"] = PNT;
  ops["~&"] = REF;
  
  // math
  ops["+"] = SUM;
  ops["-"] = SUB;
  ops["*"] = MUL;
  ops["/"] = DIV;
  ops["%"] = MOD;
  ops["**"] = EXP;

  // bin
  ops["&"] = AND;
  ops["|"] = OR;
  ops["^"] = XOR;
  ops["~"] = NOT;
  ops["~>"] = RSH;
  ops["<~"] = LSH;

  // compound assignment
  ops["++"] = INC;
  ops["--"] = DEC;
  ops["+:"] = PLEQ;
  ops["-:"] = SBEQ;
  ops["*:"] = MLEQ;
  ops["/:"] = DVEQ;
  ops["%:"] = MDEQ;
  ops["**:"] = EXEQ;
  ops["&:"] = ANEQ;
  ops["|:"] = OREQ;
  ops["^:"] = XREQ;
  ops["~:"] = NTEQ;
  ops[">:"] = RSEQ;
  ops["<:"] = LSEQ;

  // conditional
  ops["&&"] = AAND;
  ops["||"] = OOR;
  
  // comparison
  ops[">="] = GE;
  ops["=<"] = LE;
  ops["=="] = EQ;
  ops["!="] = NEQ;

  // generics
  ops["<"] = LAB;
  ops[">"] = RAB;

  // lambda
  ops["->"] = LAM;
  
  for (int i = 0; i < src.size(); i++) {

    c = src[i];

    // end of line
    if (c == '\n') {
      if (load_type == "comment") {
        load_type = ""; // end of comment
      } else if (load_type == "string") {
        cout << "[" << row << ", " << col << "] Unexpected EOL (unfinished-str-with-eol)";
        load_type = "";
        ok = false;
        slash = false;
      } else if (load_type == "char") {
        cout << "[" << row << ", " << col << "] Unexpected EOL (unfinished-chr-with-eol)";
        load_type = "";
        ok = false;
        slash = false;
      }
      col = 0;
      eol = true;
      row += 1;
    } else {
      col += 1;
    }

    // comment
    if (load_type == "comment") {
      ;      
    }
    // string
    else if (load_type == "string") {
      if (c == '\\') {
        if (slash) {
          slash = false;
        } else {
          slash = true;
        }
      } else {
        if (slash) {
          if (c == 'u') { 
            unicode = true; 
          } else if (c == 'o') {
            octal = true;
          } else {
            if (unicode) {
              if (hex.find(c) != -1) {
                uni--;
                if (uni == 0) {
                  unicode = false;
                  uni = 4;
                }
              } else {
                unicode = false;
                uni = 4;
                load_type = "";
                load_var = "";

                cout << "[" << row << ", " << col << "] Non-hexadecimal character in unicode sequence (bad-unicode).";
              }
            } else if (octal) {
              if (octl.find(c) != -1) {
                oct--;
                if (oct == 0) {
                  octal = false;
                  oct = 3;
                }
              } else {
                octal = false;
                oct = 3;
                load_type = "";
                load_var = "";

                cout << "[" << row << ", " << col << "] Non-octal character in octal sequence (bad-octal).";
              }
            } else {
              slash = false;
            }
          }
        } else {
          if (c == '"') {
            cur.ttype = STR;        
            cur.value = load_var;  
            cur.row = row;
            cur.col = col;
            tlist.push_back(cur);

	    load_type = "";
	    load_var = "";
          }
        }

	if (load_type == "") {
	  // no more string
	  ;
	} else {
	  load_var += c;
	}
      }
    }
    // character
    else if (load_type == "char") {
      if (done == true & c != '\'') {
      	cout << "[" << row << ", " << col << "] Expected end of character (expect-char-end)";
      	ok = false;
      	load_type = "";
      	load_var = "";
      }
      
      if (c == '\\') {
        if (slash) {
          slash = false;
          done = true;
        } else {
          slash = true;
        }
      } else {
        if (slash) {
          if (c == 'u') { 
            unicode = true; 
          } else if (c == 'o') {
            octal = true;
          } else {
            if (unicode) {
              if (hex.find(c) != -1) {
                uni--;
                if (uni == 0) {
                  unicode = false;
                  uni = 4;
                }
              } else {
                unicode = false;
                uni = 4;
                load_type = "";
                load_var = "";

                cout << "[" << row << ", " << col << "] Non-hexadecimal character in unicode sequence (bad-unicode).";
              }
            } else if (octal) {
              if (octl.find(c) != -1) {
                oct--;
                if (oct == 0) {
                  octal = false;
                  oct = 3;
                }
              } else {
                octal = false;
                oct = 3;
                load_type = "";
                load_var = "";

                cout << "[" << row << ", " << col << "] Non-octal character in octal sequence (bad-octal).";
              }
            } else {
              slash = false;
              done = true;
            }
          }
        } else {
          if (c == '\'') {
            cur.ttype = CHR;        
            cur.value = load_var;  
            cur.row = row;
            cur.col = col;
            tlist.push_back(cur);

	    done = false;
	    load_type = "";
	    load_var = "";
          }
        }

	if (load_type == "") {
	  // no more string
	  ;
	} else {
	  load_var += c;
	}
      }
    }
    // start of comment
    else if (c == '$') { 
      if (load_type == "") {
        ;
      } else if (load_type == "alpha") {
        if (keys.find(load_var) != keys.end()) {
          cur.ttype = keys[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        }
      } else if (load_type == "int") {
        cur.ttype = INT;        
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "float") {
        cur.ttype = FLOAT;        
        cur.value = load_var;  
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator " << load_var << " .\n";
          ok = false;
          load_type = "";
          load_var = "";
        }
      } else if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else {
        cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = false; // make it uncompilable
        load_type = "";
        load_var = "";
      }
      
      load_type = "";
      load_var = "";
      load_type = "comment";      
    } 
    // start of string
    else if (c == '"') {
      if (load_type == "") {
        ;
      } else if (load_type == "alpha") {
        if (keys.find(load_var) != keys.end()) {
          cur.ttype = keys[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        }
      } else if (load_type == "int") {
        cur.ttype = INT;        
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "float") {
        cur.ttype = FLOAT;        
        cur.value = load_var;  
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator " << load_var << " .\n";
          ok = false;
          load_type = "";
          load_var = "";
        }
      } else if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else {
        cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = false; // make it uncompilable
        load_type = "";
        load_var = "";
      }
      
      load_type = "";
      load_var = "";
      load_type = "string";
    }
    // start of character
    else if (c == '\'') {
      if (load_type == "") {
        ;
      } else if (load_type == "alpha") {
        if (keys.find(load_var) != keys.end()) {
          cur.ttype = keys[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        }
      } else if (load_type == "int") {
        cur.ttype = INT;        
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "float") {
        cur.ttype = FLOAT;        
        cur.value = load_var;  
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator " << load_var << " .\n";
          ok = false;
          load_type = "";
          load_var = "";
        }
      } else if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else {
        cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = false; // make it uncompilable
        load_type = "";
        load_var = "";
      }
      
      load_type = "";
      load_var = "";
      load_type = "char";
    }
    // alphabetical
    else if (alphabet.find(c) != -1) {
      if (load_type == "" | load_type == "alpha") {
        load_type = "alpha";
        load_var += c;
      } else if (load_type == "int" | load_type == "float") {
        cout << "[" << row << ", " << col << "] id character on tail of number\n";
        ok = false; // make it uncompilable    
        load_type = "";
        load_var = "";
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator " << load_var << " .\n";
          ok = false;
          load_type = "";
          load_var = "";
        }

        load_type = "alpha";
        load_var = "";
        load_var += c;
      } else if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
        load_type = "";
        load_var = "";
        load_type = "alpha";
        load_var += c;
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);

        load_type = "";
        load_var = "";
        load_type = "alpha";
        load_var += c;
      } else {
        cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = false; // make it uncompilable    
        load_type = "";
        load_var = "";
      }
    } 
    // numeric
    else if (numeric.find(c) != -1) {      
      if (load_type == "" | load_type == "int" | load_type == "float") {
        load_type = load_type == "float" ? "float" : "int";
        load_var += c;
      } else if (load_type == "alpha") {
        load_var += c;
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator " << load_var << " .\n";
          ok = false;
          load_type = "";
          load_var = "";
        }
        
        load_type = "";
        load_var = "";
        load_type = "int";
        load_var += c;
      } else if (load_type == "period") {
        load_type = "float";
        load_var += c;
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);

        load_type = "int";
        load_var = "";
        load_var += c;
      } else {
        cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = false; // make it uncompilable    
        load_type = "";
        load_var = "";
      }
    }
    // operators
    else if (operators.find(c) != -1) {
      if (load_type == "" | load_type == "operational") {
        load_type = "operational";
        load_var += c; 
      } else if (load_type == "alpha") {
        if (keys.find(load_var) != keys.end()) {
          cur.ttype = keys[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        }
        
        load_type = "";
        load_var = "";
        load_type = "operational";
        load_var += c;
      } else if (load_type == "int") {
        cur.ttype = INT;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
        load_type = "";
        load_var = "";
        load_type = "operational";
        load_var += c;
      } else if (load_type == "float") {
        cur.ttype = FLOAT;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
        load_type = "";
        load_var = "";
        load_type = "operational";
        load_var += c;
      } else if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
        load_type = "";
        load_var = "";
        load_type = "operational";
        load_var += c;
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
        load_type = "";
        load_var = "";
        load_type = "operational";
        load_var += c;
      } else {
        cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = false; // make it uncompilable
        load_type = "";
        load_var = "";
      }
    }
    // periods
    else if (c == '.') {
      if (load_type == "") {
        load_type = "period";
        load_var += c;
      } else if (load_type == "int") {
        load_type = "float";
        load_var += c;
      } else if (load_type == "float") {
        cout << "[" << row << ", " << col << "] Invalid float " << load_var << " .\n";
        ok = false;
        load_type = "";
        load_var = "";
      } else if (load_type == "period") {
        load_type = "splat";
        load_var += c;
      } else if (load_type == "splat") {
        load_var += c;
        cur.ttype = ELLIPSIS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
        load_type = "";
        load_var = "";
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator " << load_var << " .\n";
          ok = false;
          load_type = "";
          load_var = "";
        }
        load_type = "";
        load_var = "";
        load_type = "period";
        load_var += c;
      } else if (load_type == "alpha") {
        if (keys.find(load_var) != keys.end()) {
          cur.ttype = keys[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        }

        load_type = "";
        load_var = "";
        load_type = "period";
        load_var += c;
      } else {
        cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = false; // make it uncompilable
        load_type = "";
        load_var = "";
      }
    }
    // whitespace
    else if (white.find(c) != -1) {  
      if (load_type == "") {
        ;
      } else if (load_type == "alpha") {
        if (keys.find(load_var) != keys.end()) {
          cur.ttype = keys[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        }
      } else if (load_type == "int") {
        cur.ttype = INT;        
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "float") {
        cur.ttype = FLOAT;        
        cur.value = load_var;  
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator " << load_var << " .\n";
          ok = false;
          load_type = "";
          load_var = "";
        }
      } else if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else {
        cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = false; // make it uncompilable
        load_type = "";
        load_var = "";
      }
      
      load_type = "";
      load_var = "";

      switch (c) {
        case '{':
          cur.ttype = OBRC;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
          break;
        case '[':
          cur.ttype = OBRK;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
          break;
        case '(':
          cur.ttype = OPAR;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
          break;
        case '#':
          cur.ttype = TALL;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
          break;
        case '?':
          cur.ttype = TERN;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
          break;
        case ';':
          cur.ttype = SEMI;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
          break;
        case ')':
          cur.ttype = CPAR;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
          break;
        case ']':
          cur.ttype = CBRK;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
          break;
        case '}':
          cur.ttype = CBRC;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
          break;
        case ',':
          cur.ttype = COMM;
          cur.value = c;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        default:
          break;
      }
    } 
    // unknown character
    else {      
      cout << "[" << row << ", " << col << "] unknown " << c << "\n";
      ok = false; // make it uncompilable    
      load_type = "";
      load_var = "";
    }

    // end of line
    if (eol) {
      cur.ttype = EOL;
      cur.value = "";
      cur.row = row;
      cur.col = col;

      tlist.push_back(cur);

      // reset
      eol = false;
    }
  }

  if (load_type == "") {
        ;
      } else if (load_type == "alpha") {
        if (keys.find(load_var) != keys.end()) {
          cur.ttype = keys[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        }
      } else if (load_type == "int") {
        cur.ttype = INT;        
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "float") {
        cur.ttype = FLOAT;        
        cur.value = load_var;        
        tlist.push_back(cur);
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          cur.row = row;
          cur.col = col;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator " << load_var << " .\n";
          ok = false;
          load_type = "";
          load_var = "";
        }
      } else if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        cur.row = row;
        cur.col = col;
        tlist.push_back(cur);
      } else {
        cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = false; // make it uncompilable
        load_type = "";
        load_var = "";
      }
      
      load_type = "";
      load_var = "";

  cur.ttype = EOL;
  cur.value = "";
  cur.row = row;
  cur.col = col;
  tlist.push_back(cur);
  
  cur.ttype = EOF;
  cur.value = "";
  cur.row = row;
  cur.col = col;    
  tlist.push_back(cur);

  if (ok) {
    // no errors
    return tlist;
  } else {
    // errors
    exit(1);
  }
}

#include "crate.hpp"

vector<Token> lex(string src)
{
  vector<Token> tlist;
  Token cur;

  int row = 0;
  int col = 0;
  bool eol = false;
  bool ok = true;
  
  char c;
  
  string load_var;
  string load_type;

  string alphabet = "abcefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string numeric = "0123456789";
  string operators = "&|^~!=<>:+-*/";
  string white = "{[(#?,;)]}\r\t\n ";

  map<string, TokenTypes> keys;

  // keywords
  keys["import"] = IMPORT;
  keys["package"] = PACK;
  keys["from"] = FROM;
  keys["as"] = AS;
  keys["del"] = DEL;
  keys["assert"] = ASSERT;

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
  
  for (int i = 0; i < src.size(); i++) {

    c = src[i];

    // end of line
    if (c == '\n') {
      if (load_type == "comment") {
        load_type = ""; // end of comment
      }      
      row = 0;
      eol = true;
      col += 1;
    } else {
      row += 0;
    }

    // comment
    if (load_type == "comment") {
      ;      
    } 
    // start of comment
    else if (c == '$') {      
      load_type = "comment";      
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
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator.\n";
          ok = false;
        }

        load_type = "alpha";
        load_var = "";
        load_var += c;
      } else if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        tlist.push_back(cur);
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        tlist.push_back(cur);

        load_type = "";
        load_var = "";
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
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator.\n";
          ok = false;
        }
      } else if (load_type == "period") {
        load_type = "float";
        load_var += c;
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
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
      if (load_type == "alpha") {
        if (keys.find(load_var) != keys.end()) {
          cur.ttype = keys[load_var];
          cur.value = load_var;
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          tlist.push_back(cur);
        }
      }

      if (load_type == "int") {
        cur.ttype = INT;
        cur.value = load_var;
        tlist.push_back(cur);
      }

      if (load_type == "float") {
        cur.ttype = FLOAT;
        cur.value = load_var;
      }

      if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        tlist.push_back(cur);
      }
      
      if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
        tlist.push_back(cur);
      }
     
      load_type = "operational";  
      load_var = "";
      load_var += c;
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
        cout << "[" << row << ", " << col << "] Invalid operator.\n";
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
        load_type = "";
        load_var = "";
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator.\n";
          ok = false;
          load_type = "";
          load_var = "";
        }
      } else if (load_type == "alpha") {
        if (keys.find(load_var) != keys.end()) {
          cur.ttype = keys[load_var];
          cur.value = load_var;
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          tlist.push_back(cur);
        }
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
          tlist.push_back(cur);
        } else {
          cur.ttype = ID;
          cur.value = load_var;
          tlist.push_back(cur);
        }
      } else if (load_type == "int") {
        cur.ttype = INT;        
        cur.value = load_var;        
        tlist.push_back(cur);
      } else if (load_type == "float") {
        cur.ttype = FLOAT;        
        cur.value = load_var;        
        tlist.push_back(cur);
      } else if (load_type == "operational") {
        if (ops.find(load_var) != ops.end()) {
          cur.ttype = ops[load_var];
          cur.value = load_var;
          tlist.push_back(cur);
        } else {
          cout << "[" << row << ", " << col << "] Invalid operator.\n";
          ok = false;
          load_type = "";
          load_var = "";
        }
      } else if (load_type == "period") {
        cur.ttype = ARGS;
        cur.value = load_var;
        tlist.push_back(cur);
      } else if (load_type == "splat") {
        cur.ttype = KWARGS;
        cur.value = load_var;
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
          tlist.push_back(cur);
          break;
        case '[':
          cur.ttype = OBRK;
          cur.value = c;
          tlist.push_back(cur);
          break;
        case '(':
          cur.ttype = OPAR;
          cur.value = c;
          tlist.push_back(cur);
          break;
        case '#':
          cur.ttype = TALL;
          cur.value = c;
          tlist.push_back(cur);
          break;
        case '?':
          cur.ttype = TERN;
          cur.value = c;
          tlist.push_back(cur);
          break;
        case ';':
          cur.ttype = SEMI;
          cur.value = c;
          tlist.push_back(cur);
          break;
        case ')':
          cur.ttype = CPAR;
          cur.value = c;
          tlist.push_back(cur);
          break;
        case ']':
          cur.ttype = CBRK;
          cur.value = c;
          tlist.push_back(cur);
          break;
        case '}':
          cur.ttype = CBRC;
          cur.value = c;
          tlist.push_back(cur);
          break;
        case ',':
          cur.ttype = COMM;
          cur.value = c;
          tlist.push_back(cur);
        default:
          break;
      }
    } 
    // unknown character
    else {      
      cout << "[" << row << ", " << col << "] unknown\n";
      ok = false; // make it uncompilable    
      load_type = "";
      load_var = "";
    }

    // end of line
    if (eol) {
      cur.ttype = EOL;
      cur.value = "";

      tlist.push_back(cur);

      // reset
      eol = false;
    }
  }

  if (load_type == "") {
    ;
  } else if (load_type == "alpha") {
    // no keywords yet
    cur.ttype = ID;
    cur.value = load_var;
    tlist.push_back(cur);
  } else if (load_type == "int" | load_type == "float") {
    if (load_var.find('.') != -1) {
      cur.ttype = FLOAT;
    } else {
      cur.ttype = INT;
    }
    cur.value = load_var;        
    tlist.push_back(cur);
  } else if (load_type == "operational") {
    ;
  } else {
    cout << "[" << row << ", " << col << "] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
    ok = false; // make it uncompilable    
    load_type = "";
    load_var = "";
  }

  cur.ttype = EOL;
  cur.value = "";

  tlist.push_back(cur);
  
  cur.ttype = EOF;
  cur.value = "";
    
  tlist.push_back(cur);

  if (ok) {
    // no errors
    return tlist;
  } else {
    // errors
    exit(1);
  }
}

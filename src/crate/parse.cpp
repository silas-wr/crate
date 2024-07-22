#include "crate.hpp"

Program parse(vector<Token> tlist) {
  Program nlist;
  Node cur;
  Token tok;
  
  bool eol = true;
  bool eof = true;
  bool complex = false;
  bool ok = true;

  string load_type = "";
  vector<Token> load_var;

  vector<Node> ultimate;

  for (int i = 0; i < size(tlist); i++) {
    tok = tlist.at(i);

    switch (tok.ttype) {
      case 103:                                                                    // what to do with end-of-lines
        if (eol) {
          ;
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] " << "Unexpected EOL " << load_type <<"\n";
          ok = false;
        }
      case 104:                                                                    // what to do with end-of-files
        if (eof) {
          ;
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] " << "Unexpected EOF " << load_type <<"\n";
          ok = false;
        }
      case 0:                                                                   // what to do with identifiers
        eol = eof = false;
        if (load_type == "") {
          load_var.push_back(tok);
          load_type = "id";
        } else if (load_type == "id" | load_type == "const" | load_type == "importid" | load_type == "importct") {
          load_var.clear();
          load_type = "";

          cout << "[" << tok.row << ", " << tok.col << "] unexpected id " << load_type <<"\n";
          ok = false;
        } else if (load_type == "import") {
          load_var.push_back(tok);
          load_type = "importid";
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. " << load_type <<"\n";
          ok = false;
        }
      case 1:                                                                   // what to do with constants
        eol = eof = false;
        if (load_type == "") {
          load_var.push_back(tok);
          load_type = "const";
        } else if (load_type == "id" | load_type == "const" | load_type == "importid" | load_type == "importct") {
          load_var.clear();
          load_type = "";

          cout << "[" << tok.row << ", " << tok.col << "] unexpected const " << load_type <<"\n";
          ok = false;
        } else if (load_type == "import") {
          load_var.push_back(tok);
          load_type = "importct";
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. " << load_type <<"\n";
          ok = false;
        }
      case 2:                                                                 // what to do with `import`
        eol = eof = false;
        if (load_type == "") {
          load_var.push_back(tok);
          load_type = "import";
        } else if (load_type == "id" | load_type == "const" | load_type == "import" | load_type == "importid" | load_type == "importct") {
          load_var.clear();
          load_type = "";

          cout << "[" << tok.row << ", " << tok.col << "] unexpected import " << load_type <<"\n";
          ok = false;
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. " << load_type <<"\n";
          ok = false;
        }
      case 3:                                                                   // what to do with `pack`
      case 4:                                                                   // what to do with `from`
      case 5:                                                                   // what to do with `as`
      case 6:                                                                   // what to do with `delete`
      case 7:                                                                   // what to do with `assert`
      case 8:                                                                   // what to do with `return`
      case 9:                                                                   // what to do with `unsign`
      case 10:                                                                  // what to do with `transitive`
      case 11:                                                                  // what to do with `global`
      case 12:                                                                  // what to do with `public`
      case 13:                                                                  // what to do with `protected`
      case 14:                                                                  // what to do with `private`
      case 15:                                                                  // what to do with `hidden`
      case 16:                                                                  // what to do with `func`
      case 17:                                                                  // what to do with `class`
      case 18:                                                                  // what to do with `crate`
      case 19:                                                                  // what to do with `struct`
      case 20:                                                                  // what to do with `if`
      case 21:                                                                  // what to do with `elif`
      case 22:                                                                  // what to do with `else`
      case 23:                                                                  // what to do with `switch`
      case 24:                                                                  // what to do with `case`
      case 25:                                                                  // what to do with `default`
      case 26:                                                                  // what to do with `try`
      case 27:                                                                  // what to do with `except`
      case 28:                                                                  // what to do with `while`
      case 29:                                                                  // what to do with `break`
      case 30:                                                                  // what to do with `continue`
      case 31:                                                                  // what to do with `const`
      case 32:                                                                  // what to do with `void`
      case 33:                                                                  // what to do with `chr`
      case 34:                                                                  // what to do with `str`
      case 35:                                                                  // what to do with `byte`
      case 36:                                                                  // what to do with `short`
      case 37:                                                                  // what to do with `int`
      case 38:                                                                  // what to do with `long`
      case 39:                                                                  // what to do with `double`
      case 40:                                                                  // what to do with `type`
      case 41:                                                                  // what to do with assignment
      case 42:                                                                  // what to do with attribution
      case 43:                                                                  // what to do with enumerations
      case 44:                                                                  // what to do with typifiers
      case 45:                                                                  // what to do with type requirements
      case 46:                                                                  // what to do with pointer declarations
      case 47:                                                                  // what to do with references
      case 48:                                                                  // what to do with addition
      case 49:                                                                  // what to do with subtraction
      case 50:                                                                  // what to do with multiplication
      case 51:                                                                  // what to do with division
      case 52:                                                                  // what to do with modular arithmetic
      case 53:                                                                  // what to do with exponents
      case 54:                                                                  // what to do with AND operations
      case 55:                                                                  // what to do with OR operations
      case 56:                                                                  // what to do with XOR operations
      case 57:                                                                  // what to do with negations
      case 58:                                                                  // what to do with right shifts
      case 59:                                                                  // what to do with left shifts
      case 60:                                                                  // what to do with increments
      case 61:                                                                  // what to do with decrements
      case 62:                                                                  // what to do with +: assignment
      case 63:                                                                  // what to do with -: assignment
      case 64:                                                                  // what to do with *: assignment
      case 65:                                                                  // what to do with /: assignment
      case 66:                                                                  // what to do with %: assignment
      case 67:                                                                  // what to do with **: assignment
      case 68:                                                                  // what to do with &: assignment
      case 69:                                                                  // what to do with |: assignment
      case 70:                                                                  // what to do with ^: assignment
      case 71:                                                                  // what to do with ~: assignment
      case 72:                                                                  // what to do with >: assignment
      case 73:                                                                  // what to do with <: assignment
      case 74:                                                                  // what to do with && comparison
      case 75:                                                                  // what to do with || comparison
      case 76:                                                                  // what to do with >= comparison
      case 77:                                                                  // what to do with =< comparison
      case 78:                                                                  // what to do with == comparison
      case 79:                                                                  // what to do with != comparison
      case 80:                                                                  // what to do with opened angles
      case 81:                                                                  // what to do with closed angles
      case 82:                                                                  // what to do with lambdas
      case 83:                                                                  // what to do with args
      case 84:                                                                  // what to do with kwargs
      case 85:                                                                  // what to do with ellipses
      case 86:                                                                  // what to do with characters
      case 87:                                                                  // what to do with strings
      case 88:                                                                  // what to do with bytes
      case 89:                                                                  // what to do with short integers
      case 90:                                                                  // what to do with integers
      case 91:                                                                  // what to do with long integers
      case 92:                                                                  // what to do with floating-point numbers
      case 93:                                                                  // what to do with wildcards
      case 94:                                                                  // what to do with ternary operators
      case 95:                                                                  // what to do with opened parentheses
      case 96:                                                                  // what to do with closed parentheses
      case 97:                                                                  // what to do with opened brackets
      case 98:                                                                  // what to do with closed brackets
      case 99:                                                                  // what to do with opened braces
      case 100:                                                                 // what to do with closed braces
      case 101:                                                                 // what to do with commas
      case 102:                                                                 // what to do with semicolons
        if (load_type == "") {
          load_var.push_back(tok);
          cur.tokens = load_var;
          ;
          cur.ntype = NUL;
          ultimate.push_back(cur);
          load_var.clear();
        } else if (load_type == "import") {
          load_var.clear();
          load_type = "";

          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. \n";
          ok = false;
        } else if (load_type == "id") {
          load_var.push_back(tok);
          cur.tokens = load_var;
          ;
          cur.ntype = BLANDID;
          ultimate.push_back(cur);
          load_var.clear();
          
          eol = eof = true;
          load_type = "";
        } else if (load_type == "const") {
          load_var.push_back(tok);
          cur.tokens = load_var;
          ;
          cur.ntype = BLANDCT;
          ultimate.push_back(cur);
          load_var.clear();
          
          eol = eof = true;
          load_type = "";
        } else if (load_type == "importid") {
          load_var.push_back(tok);
          cur.tokens = load_var;
          ;
          cur.ntype = IMPOID;
          ultimate.push_back(cur);
          load_var.clear();
          
          eol = eof = true;
          load_type = "";
        } else if (load_type == "importct") {
          load_var.push_back(tok);
          cur.tokens = load_var;
          ;
          cur.ntype = IMPOCT;
          ultimate.push_back(cur);
          load_var.clear();

          eol = eof = true;
          load_type = "";
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. \n";
          ok = false;
        }
      default:                                                                     // what to do with everything else
        cout << "[" << tok.row << ", " << tok.col << "] " << "we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. \n";
        ok = false;
    }
  }

  if (ok) {
    nlist.nodes = ultimate;
    return nlist; 
  } else {
    exit(1);
  }
}

#include "crate.hpp"

Program parse(vector<Token> tlist) {
  Program nlist;
  Node cur;
  Token tok;
  
  bool eol = true;
  bool eof = true;
  bool complex = false;
  bool ok = true;

  string load_type;
  vector<Token> load_var;

  vector<Node> ultimate;

  for (int i = 0; i < size(tlist); i++) {
    tok = tlist.at(i);

    switch (tok.ttype) {
      case EOL:                                                                    // what to do with end-of-lines
        if (eol) {
          ;
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] " << "Unexpected EOL";
          ok = false;
        }
      case EOF:                                                                    // what to do with end-of-files
        if (eof) {
          ;
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] " << "Unexpected EOF";
          ok = false;
        }
      case ID:                                                                     // what to do with identifiers
        eol = eof = false;
        if (load_type == "") {
          load_var.push_back(tok);
          load_type = "id";
        } else if (load_type == "id" | load_type == "const" | load_type == "importid" | load_type == "importct") {
          load_var.clear();
          load_type = "";

          cout << "[" << tok.row << ", " << tok.col << "] unexpected id";
          ok = false;
        } else if (load_type == "import") {
          load_var.push_back(tok);
          load_type = "importid";
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github.";
          ok = false;
        }
      case CONST:                                                                  // what to do with constants
        eol = eof = false;
        if (load_type == "") {
          load_var.push_back(tok);
          load_type = "const";
        } else if (load_type == "id" | load_type == "const" | load_type == "importid" | load_type == "importct") {
          load_var.clear();
          load_type = "";

          cout << "[" << tok.row << ", " << tok.col << "] unexpected const";
          ok = false;
        } else if (load_type == "import") {
          load_var.push_back(tok);
          load_type = "importct";
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github.";
          ok = false;
        }
      case IMPORT:                                                                 // what to do with `import`
        eol = eof = false;
        if (load_type == "") {
          load_var.push_back(tok);
          load_type = "import";
        } else if (load_type == "id" | load_type == "const" | load_type == "import" | load_type == "importid" | load_type == "importct") {
          load_var.clear();
          load_type = "";

          cout << "[" << tok.row << ", " << tok.col << "] unexpected import";
          ok = false;
        } else {
          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github.";
          ok = false;
        }
      case PACK:                                                                   // what to do with `pack`
      case FROM:                                                                   // what to do with `from`
      case AS:                                                                     // what to do with `as`
      case DEL:                                                                    // what to do with `delete`
      case ASSERT:                                                                 // what to do with `assert`
      case RETURN:                                                                 // what to do with `return`
      case UNSIGN:                                                                 // what to do with `unsign`
      case TRANSITIVE:                                                             // what to do with `transitive`
      case GLOBAL:                                                                 // what to do with `global`
      case PUBLIC:                                                                 // what to do with `public`
      case PROTECT:                                                                // what to do with `protected`
      case PRIVATE:                                                                // what to do with `private`
      case HIDDEN:                                                                 // what to do with `hidden`
      case FN:                                                                     // what to do with `func`
      case CLS:                                                                    // what to do with `class`
      case CRT:                                                                    // what to do with `crate`
      case STC:                                                                    // what to do with `struct`
      case IF:                                                                     // what to do with `if`
      case ELIF:                                                                   // what to do with `elif`
      case ELSE:                                                                   // what to do with `else`
      case SWITCH:                                                                 // what to do with `switch`
      case CASE:                                                                   // what to do with `case`
      case DEFAULT:                                                                // what to do with `default`
      case TRY:                                                                    // what to do with `try`
      case EXCEPT:                                                                 // what to do with `except`
      case WHILE:                                                                  // what to do with `while`
      case BREAK:                                                                  // what to do with `break`
      case CONTINUE:                                                               // what to do with `continue`
      case TCNT:                                                                   // what to do with `const`
      case TNUL:                                                                   // what to do with `void`
      case TCHR:                                                                   // what to do with `chr`
      case TSTR:                                                                   // what to do with `str`
      case TBYT:                                                                   // what to do with `byte`
      case TSHR:                                                                   // what to do with `short`
      case TINT:                                                                   // what to do with `int`
      case TLNG:                                                                   // what to do with `long`
      case TFLT:                                                                   // what to do with `double`
      case TTYP:                                                                   // what to do with `type`
      case IS:                                                                     // what to do with assignment
      case ATTR:                                                                   // what to do with attribution
      case ENUM:                                                                   // what to do with enumerations
      case TYPE:                                                                   // what to do with typifiers
      case RTYP:                                                                   // what to do with type requirements
      case PNT:                                                                    // what to do with pointer declarations
      case REF:                                                                    // what to do with references
      case SUM:                                                                    // what to do with addition
      case SUB:                                                                    // what to do with subtraction
      case MUL:                                                                    // what to do with multiplication
      case DIV:                                                                    // what to do with division
      case MOD:                                                                    // what to do with modular arithmetic
      case EXP:                                                                    // what to do with exponents
      case AND:                                                                    // what to do with AND operations
      case OR:                                                                     // what to do with OR operations
      case XOR:                                                                    // what to do with XOR operations
      case NOT:                                                                    // what to do with negations
      case RSH:                                                                    // what to do with right shifts
      case LSH:                                                                    // what to do with left shifts
      case INC:                                                                    // what to do with increments
      case DEC:                                                                    // what to do with decrements
      case PLEQ:                                                                   // what to do with +: assignment
      case SBEQ:                                                                   // what to do with -: assignment
      case MLEQ:                                                                   // what to do with *: assignment
      case DVEQ:                                                                   // what to do with /: assignment
      case MDEQ:                                                                   // what to do with %: assignment
      case EXEQ:                                                                   // what to do with **: assignment
      case ANEQ:                                                                   // what to do with &: assignment
      case OREQ:                                                                   // what to do with |: assignment
      case XREQ:                                                                   // what to do with ^: assignment
      case NTEQ:                                                                   // what to do with ~: assignment
      case RSEQ:                                                                   // what to do with >: assignment
      case LSEQ:                                                                   // what to do with <: assignment
      case AAND:                                                                   // what to do with && comparison
      case OOR:                                                                    // what to do with || comparison
      case GE:                                                                     // what to do with >= comparison
      case LE:                                                                     // what to do with =< comparison
      case EQ:                                                                     // what to do with == comparison
      case NEQ:                                                                    // what to do with != comparison
      case LAB:                                                                    // what to do with opened angles
      case RAB:                                                                    // what to do with closed angles
      case LAM:                                                                    // what to do with lambdas
      case ARGS:                                                                   // what to do with args
      case KWARGS:                                                                 // what to do with kwargs
      case ELLIPSIS:                                                               // what to do with ellipses
      case CHR:                                                                    // what to do with characters
      case STR:                                                                    // what to do with strings
      case BYTE:                                                                   // what to do with bytes
      case SHORT:                                                                  // what to do with short integers
      case INT:                                                                    // what to do with integers
      case LONG:                                                                   // what to do with long integers
      case FLOAT:                                                                  // what to do with floating-point numbers
      case TALL:                                                                   // what to do with wildcards
      case TERN:                                                                   // what to do with ternary operators
      case OPAR:                                                                   // what to do with opened parentheses
      case CPAR:                                                                   // what to do with closed parentheses
      case OBRK:                                                                   // what to do with opened brackets
      case CBRK:                                                                   // what to do with closed brackets
      case OBRC:                                                                   // what to do with opened braces
      case CBRC:                                                                   // what to do with closed braces
      case COMM:                                                                   // what to do with commas
      case SEMI:                                                                   // what to do with semicolons
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

          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github.";
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
          cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github.";
          ok = false;
        }
      default:                                                                     // what to do with everything else
        cout << "[" << tok.row << ", " << tok.col << "] " << "we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github.";
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

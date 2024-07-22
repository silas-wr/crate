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

    cout << "\nToken " << i << " of type " << tok.ttype << ": " << tok.value << " with load_type '" << load_type << "'\n";

    if (tok.ttype == 103) {
      if (eol) {
          ;
      } else {
          cout << "[" << tok.row << ", " << tok.col << "] " << "Unexpected EOL " << load_type << "\n";
          ok = false;
      }
    } else if (tok.ttype == 104) {
      if (eof) {
        ;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] " << "Unexpected EOF " << load_type << "\n";
        ok = false;
      }
    } else if (tok.ttype == 0) {
      // Code for case 0
    } else if (tok.ttype == 1) {
      // Code for case 1
    } else if (tok.ttype == 2) {
      // Code for case 2
    } else if (tok.ttype == 102) {
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
    } else {
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

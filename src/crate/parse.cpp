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
          cout << "[" << tok.row << ", " << tok.col << "] " << "Unexpected EOL\n";
          ok = false;
      }
    } else if (tok.ttype == 104) {
      if (eof) {
        ;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] " << "Unexpected EOF\n";
        ok = false;
      }
    } else if (tok.ttype == 0) {
      eol = false;
      eof = false;
      if (load_type == "") {
        load_var.push_back(tok);
        load_type = "id";
      } else if (load_type == "id") {
        load_var.clear();
        load_type = "id";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected id. (unexpected-id-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type)\n";
        ok = false;
      }
    } else if (tok.ttype == 1) {
      ;
    } else if (tok.ttype == 2) {
      ;
    } else if (tok.ttype == 102) {
      eol = true;
      eof = true;
      if (load_type == "") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NUL;
        ultimate.push_back(cur);
        load_var.clear();
      } else if (load_type == "id") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = BLANDID;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type)\n";
        ok = false;
      }
    } else {
      cout << "[" << tok.row << ", " << tok.col << "] " << "we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-token)\n";
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

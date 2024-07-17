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
  vector<Node> nodes;

  for (int i = 0; i < size(tlist); i++) {
    tok = tlist.at(i);

    if (tok.ttype == EOL) {
      if (eol) {
        ;
      } else {
        cout << "[] " << "Unexpected EOL";
        ok = false;
      }
    } else if (tok.ttype == EOF) {
      if (eof) {
        ;
      } else {
        cout << "[] " << "Unexpected EOF";
        ok = false;
      }
    }
  }

  if (ok) {
    nlist.nodes = nodes;
    return nlist; 
  } else {
    exit(1);
  }
}

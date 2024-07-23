#include "crate.hpp"

Program parse(vector<Token> tlist) {
  Program nlist;
  Node cur;
  Token tok;
  
  bool eol = true;
  bool eof = true;
  bool complex = false;
  bool ok = true;

  list<string> id {"id", "const", "importid", "importct", "packid", "packct"};
  list<string> sky {"id", "const", "import", "importid", "importct", "packid", "packct"};

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
      } else if (load_type == "import") {
        load_var.push_back(tok);
        load_type = "importid";
      } else if (load_type == "pack") {
        load_var.push_back(tok);
        load_type = "packid";
      } else if (find(id.begin(), id.end(), load_type) != -1) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected id. (unexpected-id-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else if (tok.ttype == 1) {
      eol = false;
      eof = false;
      if (load_type == "") {
        load_var.push_back(tok);
        load_type = "const";
      } else if (load_type == "import") {
        load_var.push_back(tok);
        load_type = "importct";
      } else if (load_type == "pack") {
        load_var.push_back(tok);
        load_type = "packct";
      } else if (find(id.begin(), id.end(), load_type) != -1) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected const. (unexpected-const-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else if (tok.ttype == 2) {
      eol = false;
      eof = false;
      if (load_type == "") {
        load_var.push_back(tok);
        load_type = "import";
      } else if (find(sky.begin(), sky.end(), load_type) != -1) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected import. (unexpected-import-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else if (tok.ttype == 3) {
      eol = false;
      eof = false;
      if (load_type == "") {
        load_var.push_back(tok);
        load_type = "pack";
      } else if (find(sky.begin(), sky.end(), load_type) != -1) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected package. (unexpected-pack-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
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
      } else if (load_type == "const") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = BLANDCT;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "importid") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = IMPOID;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "importct") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = IMPOCT;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "packid") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = PACKID;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "packct") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = PACKCT;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "import" | load_type == "pack") {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected semi. (unexpected-semi-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else {
      cout << "[" << tok.row << ", " << tok.col << "] " << "we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-token-" << tok.ttype << ")\n";
      ok = false;
    }
  }

  cout << "\n";

  if (ok) {
    nlist.nodes = ultimate;
    return nlist; 
  } else {
    exit(1);
  }
}

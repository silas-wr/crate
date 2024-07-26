#include "crate.hpp"

Program parse(const vector<Token> tlist) {
  Program nlist;
  Node cur;
  Token tok;
  
  bool eol = true;
  bool eof = true;
  // bool complex = false; // For functions, crates, and such things
  bool ok = true;

  vector<string> id {"id", "importr", "packr", "fromg", "fromr", "iasr", "fasr", "delr", "globr", "incbr", "decbr", "incer", "decer"};
  
  vector<string> imp {"id", "import", "importr", "pack", "packr", "from", "imfr", "fromr", "ias", "fas", "iasr", "fasr", "del", "delr", "global", "globr",\
    "incb", "decb", "incbr", "decbr", "incer", "decer"};
  
  vector<string> pck {"id", "import", "importr", "pack", "packr", "from", "fromg", "imfr", "fromr", "ias", "fas", "iasr", "fasr", "del", "delr", "global",\
    "globr", "incb", "decb", "incbr", "decbr", "incer", "decer"};
  
  vector<string> fro {"id", "import", "importr", "pack", "packr", "from", "fromg", "imfr", "fromr", "ias", "fas", "iasr", "fasr", "del", "delr", "global",\
    "globr", "incb", "decb", "incbr", "decbr", "incer", "decer"};

  vector<string> as {"", "id", "import", "pack", "packr", "from", "fromg", "imfr", "ias", "fas", "iasr", "fasr", "del", "delr", "global", "globr", "incb",\
    "decb", "incbr", "decbr", "incer", "decer"};

  vector<string> del {"id", "import", "importr", "pack", "packr", "from", "fromg", "imfr", "fromr", "ias", "fas", "iasr", "fasr", "del", "delr", "global",\
    "globr", "incb", "decb", "incbr", "decbr", "incer", "decer"};

  vector<string> glob {"id", "import", "importr", "pack", "packr", "from", "fromg", "imfr", "fromr", "ias", "fas", "iasr", "fasr", "del", "delr", "global",\
    "globr", "incb", "decb", "incbr", "decbr", "incer", "decer"};

  vector<string> icdc {"import", "importr", "pack", "packr", "from", "fromg", "imfr", "fromr", "ias", "fas", "iasr", "fasr", "del", "delr", "global", "globr",\
    "incb", "decb", "incbr", "decbr", "incer", "decer"};
  
  vector<string> semi {"import", "pack", "from", "fromg", "imfr", "ias", "fas", "del", "global", "incb", "decb"};

  string load_type = "";
  // string comp_type = "";
  vector<Token> load_var;

  vector<Node> ultimate;

  for (int i = 0; i < size(tlist); i++) {
    tok = tlist.at(i);

    cout << "\nToken " << i << " of type " << tok.ttype << ": " << tok.value << " with load_type '" << load_type << "'\n";

    if (tok.ttype == 102) {
      if (eol) {
          ;
      } else {
          cout << "[" << tok.row << ", " << tok.col << "] " << "Unexpected EOL\n";
          ok = false;
      }
    } else if (tok.ttype == 103) {
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
      } else if (load_type == "from") {
        load_var.push_back(tok);
        load_type = "fromg";
      } else if (load_type == "import") {
        load_var.push_back(tok);
        load_type = "importr";
      } else if (load_type == "pack") {
        load_var.push_back(tok);
        load_type = "packr";
      } else if (load_type == "imfr") {
        load_var.push_back(tok);
        load_type = "fromr";
      } else if (load_type == "ias") {
        load_var.push_back(tok);
        load_type = "iasr";
      } else if (load_type == "fas") {
        load_var.push_back(tok);
        load_type = "fasr";
      } else if (load_type == "del") {
        load_var.push_back(tok);
        load_type = "delr";
      } else if (load_type == "global") {
        load_var.push_back(tok);
        load_type = "globr";
      } else if (load_type == "incb") {
        load_var.push_back(tok);
        load_type = "incbr";
      } else if (load_type == "decb") {
        load_var.push_back(tok);
        load_type = "decbr";
      } else if (find(id.begin(), id.end(), load_type) != id.end()) {
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
        load_type = "import";
      } else if (load_type == "inc") {
        load_var.push_back(tok);
        load_type = "incr";
      } else if (load_type == "dec") {
        load_var.push_back(tok);
        load_type = "decr";
      } else if (load_type == "fromg") {
        load_var.push_back(tok);
        load_type = "imfr";
      } else if (find(imp.begin(), imp.end(), load_type) != imp.end()) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected import. (unexpected-import-with-" << load_type << ")\n";
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
        load_type = "pack";
      } else if (find(pck.begin(), pck.end(), load_type) != pck.end()) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected package. (unexpected-pack-with-" << load_type << ")\n";
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
        load_type = "from";
      } else if (find(fro.begin(), fro.end(), load_type) != fro.end()) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected from. (unexpected-from-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else if (tok.ttype == 4) {
      eol = false;
      eof = false;
      if (load_type == "importr") {
        load_var.push_back(tok);
        load_type = "ias";
      } else if (load_type == "fromr") {
        load_var.push_back(tok);
        load_type = "fas";
      } else if (find(as.begin(), as.end(), load_type) != as.end()) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected as. (unexpected-as-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else if (tok.ttype == 5) {
      eol = false;
      eof = false;
      if (load_type == "") {
        load_var.push_back(tok);
        load_type = "del";
      } else if (find(del.begin(), del.end(), load_type) != del.end()) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected delete. (unexpected-del-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else if (tok.ttype == 10) {
      eol = false;
      eof = false;
      if (load_type == "") {
        load_var.push_back(tok);
        load_type = "global";
      } else if (find(glob.begin(), glob.end(), load_type) != glob.end()) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected global. (unexpected-global-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else if (tok.ttype == 59) {
      eol = false;
      eof = false;
      if (load_type == "") {
        load_var.push_back(tok);
        load_type = "incb";
      } else if (load_type == "id") {
        load_var.push_back(tok);
        load_type = "incer";
      } else if (find(icdc.begin(), icdc.end(), load_type) != icdc.end()) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected increment. (unexpected-inc-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else if (tok.ttype == 60) {
      eol = false;
      eof = false;
      if (load_type == "") {
        load_var.push_back(tok);
        load_type = "decb";
      } else if (load_type == "id") {
        load_var.push_back(tok);
        load_type = "decer";
      } else if (find(icdc.begin(), icdc.end(), load_type) != icdc.end()) {
        load_var.clear();
        load_type = "";
        cout << "[" << tok.row << ", " << tok.col << "] unexpected decrement. (unexpected-dec-with-" << load_type << ")\n";
        ok = false;
      } else {
        cout << "[" << tok.row << ", " << tok.col << "] we're so sorry. something went wrong with the parser. tell us at silas-wr/crate on github. (unknown-type-" << load_type << ")\n";
        ok = false;
      }
    } else if (tok.ttype == 101) {
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
        cur.ntype = NBLAND;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "importr") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NIMP;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "packr") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NPACK;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "fromr") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NFROM;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "iasr") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NIAS;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "fasr") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NFAS;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "delr") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NDEL;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "globr") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NGLOB;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "incbr") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NINCB;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "incer") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NINCE;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "decbr") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NDECB;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (load_type == "decer") {
        load_var.push_back(tok);
        cur.tokens = load_var;
        cur.ntype = NDECE;
        ultimate.push_back(cur);
        load_var.clear();
        load_type = "";
      } else if (find(semi.begin(), semi.end(), load_type) != semi.end()) {
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

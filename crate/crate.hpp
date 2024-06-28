#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

#undef EOF

enum TokenTypes {
  ID,
  IS,

  PERIOD,
  INT,
  FLOAT,

  IMPORT,

  SEMI,
  EOL,
  EOF
};

enum NodeTypes {
  
};

struct Token {
  TokenTypes ttype;
  string value;
};

struct Node {
  NodeTypes ntype;
  vector<Token> tokens;
};

struct Program {
  vector<Node> nodes;
};

vector<Token> lex(string src);
Program parse(vector<Token> tlist);
int compile(Program parsed);
int run(string classfile);
int strparse(string s);

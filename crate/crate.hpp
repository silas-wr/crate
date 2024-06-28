#include <iostream>
#include <string>
#include <vector>

#undef EOF

enum TokenTypes {
  ID,
  SEMI,
  EOL,
  EOF
};

enum NodeTypes {
  
};

struct Token {
  TokenTypes ttype;
  std::string value;
};

struct Node {
  NodeTypes ntype;
  std::vector<Token> tokens;
};

struct Program {
  std::vector<Node> nodes;
};

std::vector<Token> lex(std::string src);
Program parse(std::vector<Token> tlist);
int compile(Program parsed);
int run(std::string classfile);
int strparse(std::string s);

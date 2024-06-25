#include <iostream>
#include <string>
#include <vector>

enum TokenTypes {
  ID,
};

enum NodeTypes {
  N_ASSIGN,
};

struct Token {
  int ttype;
  std::string value;
};

struct Node {
  int ntype;
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

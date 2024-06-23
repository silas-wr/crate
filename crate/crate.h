#include <iostream>
#include <string>

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

struct Tokens {
  Token tlist[];
};

struct Node {
  int ntype;
  Tokens tokens;
};

struct Program {
  Node nodes[];
};

Token lex(std::string src)[];
Program parse(Tokens tlist);
int compile(Program parsed);
int run(std::string classfile);
int strparse(std::string s);

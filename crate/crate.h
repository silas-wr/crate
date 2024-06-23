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
  struct Token tlist[];
};

struct Node {
  int ntype;
  struct Tokens tokens;
};

struct Program {
  struct Node nodes[];
};

struct Token lex(std::string src)[];
struct Program parse(struct Tokens tlist);
int compile(struct Program parsed);
int run(std::string classfile);
int strparse(std::string s);

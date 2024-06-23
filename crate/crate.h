#include <iostream>
#include <string>

enum TokenTypes {
  ID,
};

enum NodeTypes {
  N_ASSIGN
};

struct Token {
  int ttype;
  std::string value;
};

struct Tokens {
  int tnum;
  struct Token tlist[];
};

struct Node {
  int ntype;
  struct Token tokens[];
};

struct Program {
  int nnum;
  struct Node nodes[];
};

struct Tokens lex(std::string src);
struct Program parse(struct Tokens tlist);
int compile(struct Program parsed);
int run(std::string classfile);
int strparse(std::string s);

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
  string value;
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

struct Tokens lex(string src);
struct Program parse(struct Tokens tlist);
int compile(struct Program parsed);
int run(string classfile);
int strparse(string s);

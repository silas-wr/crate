#include <stdio.h>
#include <stdarg.h>

struct Token {
  int ttype;
  char value[];
};

struct Tokens {
  struct Token[] tokens;
};

struct Node {
  int ntype;
  struct Token[] tokens;
};

struct Program {
  struct Node[] nodes;
};

struct Tokens lex(char src[]);
struct Program parse(struct Token tlist[]);
int compile(struct Program parsed);
int run(char file[]);
int strparse(char s[]);

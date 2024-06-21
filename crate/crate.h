#include <stdio.h>

struct Token {
  int ttype;
  char value[];
}

struct Node {
  struct Token tokens[];
  int ntype;
}

struct Program {
  struct Node nodes[];
}

struct Token lex(char name[])[];
struct Program parse(struct Token tlist[]);
int compile(struct Program parsed);
int run(char file[]);
int strparse(char s[]);

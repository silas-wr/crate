#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

#undef EOF

enum TokenTypes {
  // ids
  ID,
  CONST,
  
  // keys
  IMPORT,
  PACK,
  FROM,
  AS,
  DEL,
  ASSERT,

  // data structures
  FN,
  CLS,
  CRT,
  STC,

  // control
  IF,
  ELIF,
  ELSE,
  SWITCH,
  CASE,
  DEFAULT,
  TRY,
  EXCEPT,
  WHILE,
  BREAK,
  CONTINUE,
  
  // types
  TCNT,
  TNUL,
  TCHR,
  TSTR,
  TBYT,
  TSHR,
  TINT,
  TLNG,
  TFLT,
  TTYP,

  // assignment
  IS,
  ATTR,
  ENUM,
  TYPE,
  RTYP,

  // pointer
  PNT,
  REF,
  
  // math
  SUM,
  SUB,
  MUL,
  DIV,
  MOD,
  EXP,

  // bin
  AND,
  OR,
  XOR,
  NOT,
  RSH,
  LSH,

  // compound assignment
  INC,
  DEC,
  PLEQ,
  SBEQ,
  MLEQ,
  DVEQ,
  MDEQ,
  EXEQ,
  ANEQ,
  OREQ,
  XREQ,
  NTEQ,
  RSEQ,
  LSEQ,

  // conditional
  AAND,
  OOR,
  
  // comparison
  GE,
  LE,
  EQ,
  NEQ,

  // generics
  LAB,
  RAB,
  
  // whitespace
  TALL,
  TERN,
  OPAR,
  CPAR,
  OBRK,
  CBRK,
  OBRC,
  CBRC,
  SEMI,
  EOL,
  EOF,
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
int numparse(string s);

bool isUpper(const std::string& s) {
    return std::all_of(s.begin(), s.end(), [](unsigned char c){ return std::isupper(c); });
}

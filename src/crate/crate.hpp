#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <list>

using namespace std;

#undef EOF

enum TokenTypes {
  // ids
  ID,                    //0
  
  // keys
  IMPORT,                //1
  PACK,                  //2
  FROM,                  //3
  AS,                    //4
  DEL,                   //5
  ASSERT,                //6 later (flat complex)
  RETURN,                //7 later (type simple)
  UNSIGN,                //8 later (flat complex)
  TRANSITIVE,            //9 later (flat complex)
  GLOBAL,                //10

  // privacy
  PUBLIC,                //11
  PROTECT,               //12
  PRIVATE,               //13
  HIDDEN,                //14

  // data structures
  FN,                    //15
  CLS,                   //16
  CRT,                   //17
  STC,                   //18

  // control
  IF,                    //19
  ELIF,                  //20
  ELSE,                  //21
  SWITCH,                //22
  CASE,                  //23
  DEFAULT,               //24
  TRY,                   //25
  EXCEPT,                //26
  WHILE,                 //27
  BREAK,                 //28
  CONTINUE,              //29
  
  // type names
  TCNT,                  //30
  TNUL,                  //31
  TCHR,                  //32
  TSTR,                  //33
  TBYT,                  //34
  TSHR,                  //35
  TINT,                  //36
  TLNG,                  //37
  TFLT,                  //38
  TTYP,                  //39

  // assignment
  IS,                    //40
  ATTR,                  //41
  ENUM,                  //42
  TYPE,                  //43
  RTYP,                  //44

  // pointer
  PNT,                   //45
  REF,                   //46
  
  // math
  SUM,                   //47
  SUB,                   //48
  MUL,                   //49
  DIV,                   //50
  MOD,                   //51 
  EXP,                   //52

  // bin
  AND,                   //53
  OR,                    //54
  XOR,                   //55
  NOT,                   //56
  RSH,                   //57
  LSH,                   //58

  // compound assignment
  INC,                   //59
  DEC,                   //60
  PLEQ,                  //61
  SBEQ,                  //62
  MLEQ,                  //63
  DVEQ,                  //64
  MDEQ,                  //65
  EXEQ,                  //66
  ANEQ,                  //67
  OREQ,                  //68
  XREQ,                  //69
  NTEQ,                  //70
  RSEQ,                  //71
  LSEQ,                  //72

  // conditional
  AAND,                  //73
  OOR,                   //74

  // comparison
  GE,                    //75
  LE,                    //76
  EQ,                    //77
  NEQ,                   //78

  // generics
  LAB,                   //79
  RAB,                   //80

  // lambda
  LAM,                   //81

  // params
  ARGS,                  //82
  KWARGS,                //83
  ELLIPSIS,              //84

  // objects
  CHR,                   //85
  STR,                   //86
  BYTE,                  //87
  SHORT,                 //88
  INT,                   //89
  LONG,                  //90
  FLOAT,                 //91
  
  // whitespace
  TALL,                  //92
  TERN,                  //93
  OPAR,                  //94
  CPAR,                  //95
  OBRK,                  //96
  CBRK,                  //97
  OBRC,                  //98
  CBRC,                  //99
  COMM,                  //100
  SEMI,                  //101
  EOL,                   //102
  EOF,                   //103
};

enum NodeTypes {
  // null
  NUL,

  // bland
  NBLAND,

  // imports
  NIMP,
  NPACK,
  NFROM,
  NIAS, // import
  NFAS, // from import

  // var keywords
  NDEL,
  NGLOB,
};

struct Token {
  TokenTypes ttype;
  string value;
  int row;
  int col;
};

struct Node {
  NodeTypes ntype;
  vector<Node> nodes;
  vector<Token> tokens;
};

struct Program {
  vector<Node> nodes;
};

vector<Token> lex(const string);
Program parse(const vector<Token>);
int compile(Program);
int run(string);
int strparse(string);
int numparse(string);
void nodes(Node, int);
void prog(Program);

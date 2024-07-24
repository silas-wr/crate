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
  CONST,                 //1
  
  // keys
  IMPORT,                //2
  PACK,                  //3
  FROM,                  //4
  AS,                    //5
  DEL,                   //6
  ASSERT,                //7
  RETURN,                //8
  UNSIGN,                //9
  TRANSITIVE,            //10
  GLOBAL,                //11

  // privacy
  PUBLIC,                //12
  PROTECT,               //13
  PRIVATE,               //14
  HIDDEN,                //15

  // data structures
  FN,                    //16
  CLS,                   //17
  CRT,                   //18
  STC,                   //19

  // control
  IF,                    //20
  ELIF,                  //21
  ELSE,                  //22
  SWITCH,                //23
  CASE,                  //24
  DEFAULT,               //25
  TRY,                   //26
  EXCEPT,                //27
  WHILE,                 //28
  BREAK,                 //29
  CONTINUE,              //30
  
  // type names
  TCNT,                  //31
  TNUL,                  //32
  TCHR,                  //33
  TSTR,                  //34
  TBYT,                  //35
  TSHR,                  //36
  TINT,                  //37
  TLNG,                  //38
  TFLT,                  //39
  TTYP,                  //40

  // assignment
  IS,                    //41
  ATTR,                  //42
  ENUM,                  //43
  TYPE,                  //44
  RTYP,                  //45

  // pointer
  PNT,                   //46
  REF,                   //47
  
  // math
  SUM,                   //48
  SUB,                   //49
  MUL,                   //50
  DIV,                   //51
  MOD,                   //52 
  EXP,                   //53

  // bin
  AND,                   //54
  OR,                    //55
  XOR,                   //56
  NOT,                   //57
  RSH,                   //58
  LSH,                   //59

  // compound assignment
  INC,                   //60
  DEC,                   //61
  PLEQ,                  //62
  SBEQ,                  //63
  MLEQ,                  //64
  DVEQ,                  //65
  MDEQ,                  //66
  EXEQ,                  //67
  ANEQ,                  //68
  OREQ,                  //69
  XREQ,                  //70
  NTEQ,                  //71
  RSEQ,                  //72
  LSEQ,                  //73

  // conditional
  AAND,                  //74
  OOR,                   //75

  // comparison
  GE,                    //76
  LE,                    //77
  EQ,                    //78
  NEQ,                   //79

  // generics
  LAB,                   //80
  RAB,                   //81

  // lambda
  LAM,                   //82

  // params
  ARGS,                  //83
  KWARGS,                //84
  ELLIPSIS,              //85

  // objects
  CHR,                   //86
  STR,                   //87
  BYTE,                  //88
  SHORT,                 //89
  INT,                   //90
  LONG,                  //91
  FLOAT,                 //92
  
  // whitespace
  TALL,                  //93
  TERN,                  //94
  OPAR,                  //95
  CPAR,                  //96
  OBRK,                  //97
  CBRK,                  //98
  OBRC,                  //99
  CBRC,                  //100
  COMM,                  //101
  SEMI,                  //102
  EOL,                   //103
  EOF,                   //104
};

enum NodeTypes {
  NUL,
  NBLAND,
  NIMP,
  NPACK,
  NFROM,
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

vector<Token> lex(string);
Program parse(vector<Token>);
int compile(Program);
int run(string);
int strparse(string);
int numparse(string);
bool isUpper(const string&);
void nodes(Node, int);
void prog(Program);

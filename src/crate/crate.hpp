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
  PUBLIC,                //11 later (flat complex)
  PROTECT,               //12 later (flat complex)
  PRIVATE,               //13 later (flat complex)
  HIDDEN,                //14 later (flat complex)

  // data structures
  FN,                    //15 later (complex)
  CLS,                   //16 later (complex)
  CRT,                   //17 later (complex)
  STC,                   //18 later (complex)

  // control
  IF,                    //19 later (complex)
  ELIF,                  //20 later (complex)
  ELSE,                  //21 later (complex)
  SWITCH,                //22 later (complex)
  CASE,                  //23 later (complex)
  DEFAULT,               //24 later (complex)
  TRY,                   //25 later (complex)
  EXCEPT,                //26 later (complex)
  WHILE,                 //27 later (complex)
  BREAK,                 //28 later (require complex)
  CONTINUE,              //29 later (require complex)
  
  // type names
  TCNT,                  //30 later (flat complex)
  TNUL,                  //31 later (flat complex)
  TCHR,                  //32 later (flat complex)
  TSTR,                  //33 later (flat complex)
  TBYT,                  //34 later (flat complex)
  TSHR,                  //35 later (flat complex)
  TINT,                  //36 later (flat complex)
  TLNG,                  //37 later (flat complex)
  TFLT,                  //38 later (flat complex)
  TTYP,                  //39 later (flat complex)

  // assignment
  IS,                    //40 later (flat complex)
  ATTR,                  //41 later (flat complex)
  ENUM,                  //42 later (flat complex)
  TYPE,                  //43 later (flat complex)
  RTYP,                  //44 later (complex?)

  // pointer
  PNT,                   //45 later (flat complex)
  REF,                   //46 later (flat complex)
  
  // math
  SUM,                   //47 later (flat complex)
  SUB,                   //48 later (flat complex)
  MUL,                   //49 later (flat complex)
  DIV,                   //50 later (flat complex)
  MOD,                   //51 later (flat complex)
  EXP,                   //52 later (flat complex)

  // bin
  AND,                   //53 later (flat complex)
  OR,                    //54 later (flat complex)
  XOR,                   //55 later (flat complex)
  NOT,                   //56 later (flat complex)
  RSH,                   //57 later (flat complex)
  LSH,                   //58 later (flat complex)

  // compound assignment
  INC,                   //59
  DEC,                   //60
  PLEQ,                  //61 later (flat complex)
  SBEQ,                  //62 later (flat complex)
  MLEQ,                  //63 later (flat complex)
  DVEQ,                  //64 later (flat complex)
  MDEQ,                  //65 later (flat complex)
  EXEQ,                  //66 later (flat complex)
  ANEQ,                  //67 later (flat complex)
  OREQ,                  //68 later (flat complex)
  XREQ,                  //69 later (flat complex)
  NTEQ,                  //70 later (flat complex)
  RSEQ,                  //71 later (flat complex)
  LSEQ,                  //72 later (flat complex)

  // conditional
  AAND,                  //73 later (flat complex)
  OOR,                   //74 later (flat complex)

  // comparison
  GE,                    //75 later (flat complex)
  LE,                    //76 later (flat complex)
  EQ,                    //77 later (flat complex)
  NEQ,                   //78 later (flat complex)

  // generics
  LAB,                   //79 later (flat complex)
  RAB,                   //80 later (flat complex)

  // lambda
  LAM,                   //81 later (flat complex)

  // params
  ARGS,                  //82 later (flat complex)
  KWARGS,                //83 later (flat complex)
  ELLIPSIS,              //84 later (flat complex)

  // objects
  CHR,                   //85 later
  STR,                   //86 later
  BYTE,                  //87 later
  SHORT,                 //88 later
  INT,                   //89 later
  LONG,                  //90 later
  FLOAT,                 //91 later
  
  // whitespace
  TALL,                  //92 later (flat complex)
  TERN,                  //93 later (flat complex)
  OPAR,                  //94 later (flat complex)
  CPAR,                  //95 later (flat complex)
  OBRK,                  //96 later (flat complex)
  CBRK,                  //97 later (flat complex)
  OBRC,                  //98 later (flat complex)
  CBRC,                  //99 later (flat complex)
  COMM,                  //100 later (flat complex)
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

  // increment and decrement
  NINCB,
  NINCE,
  NDECB,
  NDECE,
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
string strparse(string);
int numparse(string);
void nodes(Node, int);
void prog(Program);

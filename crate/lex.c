#include "crate.h"

struct Tokens lex(char src[])
{
  int  i = 0;
  int  t = 0;
  char c;

  struct Token  newtok;
  struct Tokens tlist;
  
  while ((c = src[i++]) != EOF)
  {
    printf("%c", c);    
    t++;
  }

  tlist.tnum = t;

  return tlist;
}

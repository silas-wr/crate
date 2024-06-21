#include "crate.h"

struct Tokens lex(char src[])
{
  int  i = 0;
  char c;
  
  struct Tokens tlist;
  
  while ((c = src[i++]) != EOF)
  {
    printf("%c", c);
  }

  return tlist;
}

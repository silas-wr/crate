#include "crate.h"

struct Token lex(char (*src)[])[]
{
  char c;
  struct Token tlist[];
  
  while ((c = *src++) != EOF)
  {
    printf(c);
  }

  return tlist;
}

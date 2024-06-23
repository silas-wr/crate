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
    switch (c)
    {
      case 'a': case 'b': case 'c': case 'd' :case 'e': case 'f': case  'g': case 'h': case 'i': case 'j': 
      case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case  'q': case 'r': case 's': case 't': 
      case 'u': case 'v': case 'w': case 'x': case 'y': case 'z': case  'A': case 'B': case 'C': case 'D': 
      case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case  'K': case 'L': case 'M': case 'N': 
      case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case  'U': case 'V': case 'W': case 'X': 
      case 'Y': case 'Z': 
        printf("alphabetical");
        break;

      case '{': case '[': case '(': case ')': case ']': case '}': case ';': 
      case '#': case '\n': case '\t': case '\r': case ' ':
        printf("whitespace");
        break;

      case EOF:
        printf("EOF");
        break;

      default:
        printf("unknown");
        break;
    }
    
    t++;
  }

  tlist.tnum = t;

  return tlist;
}

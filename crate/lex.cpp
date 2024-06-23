#include "crate.h"

Tokens lex(std::string src)
{
  int  i = 0;
  int  t = 0;
  char c;

  crate::Tokens tlist = crate::Tokens();
  
  for (c = src[i]; i < sizeof(src); i++) {
    switch (c)
    {
      case 'a': case 'b': case 'c': case 'd' :case 'e': case 'f': case  'g': case 'h': case 'i': case 'j': 
      case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case  'q': case 'r': case 's': case 't': 
      case 'u': case 'v': case 'w': case 'x': case 'y': case 'z': case  'A': case 'B': case 'C': case 'D': 
      case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case  'K': case 'L': case 'M': case 'N': 
      case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case  'U': case 'V': case 'W': case 'X': 
      case 'Y': case 'Z': 
        std::cout << "alphabetical";
        break;

      case '{': case '[': case '(': case ')': case ']': case '}': case ';': 
      case '#': case '\n': case '\t': case '\r': case ' ':
        std::cout << "whitespace";
        break;

      case '\0':
        std::cout << "end" // end of code

      default:
        std::cout << "unknown";
        break;
    }
    
    t++;
  }

  tlist.tokens[] = { new Token(), new Token(), new Token() };

  return tlist;
}

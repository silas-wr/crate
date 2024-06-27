#include "crate.hpp"

std::vector<Token> lex(std::string src)
{
  int  i = 0;
  char c;

  std::vector<Token> tlist;
  Token cur;
  
  for (c = src[i]; i < src.size(); i++) {
    switch (c)
    {
      case 'a': case 'b': case 'c': case 'd' :case 'e': case 'f': case  'g': case 'h': case 'i': case 'j': 
      case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case  'q': case 'r': case 's': case 't': 
      case 'u': case 'v': case 'w': case 'x': case 'y': case 'z': case  'A': case 'B': case 'C': case 'D': 
      case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case  'K': case 'L': case 'M': case 'N': 
      case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case  'U': case 'V': case 'W': case 'X': 
      case 'Y': case 'Z': 
        std::cout << "alphabetical\n";
        break;

      case '{': case '[': case '(': case ')': case ']': case '}': case ';': 
      case '#': case '\n': case '\t': case '\r': case ' ':
        std::cout << "whitespace\n";
        break;
      
      default:
        std::cout << "unknown\n";
        break;
    }

    cur.ttype = EOF;
    cur.value = "";
    
    tlist.push_back(cur);
  }

  return tlist;
}

#include "crate.hpp"

std::vector<Token> lex(std::string src)
{
  int  i = 0;
  char c;

  std::vector<Token> tlist;
  Token cur;

  std::string alphabet = "abcefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string numeric = "0123456789";
  std::string operators = "&|^~!=<>:+-*/";
  std::string white = "{[(#?;)]}\r\t\n ";
  
  for (c = src[i]; i < src.size(); i++) {
    if (alphabet.find(c) != -1) {
      std::cout << "alphabetical";
    } else if (numeric.find(c) != -1) {
      std::cout << "numeric";
    } else if (operators.find(c) != -1) {
      std::cout << "operational";
    } else if (white.find(c) != -1) {
      std::cout << "whitespace";
    } else {
      std::cout << "unknown";
    }
  }

  
  cur.ttype = EOF;
  cur.value = "";
    
  tlist.push_back(cur);

  return tlist;
}

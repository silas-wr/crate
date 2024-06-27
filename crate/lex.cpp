#include "crate.hpp"

std::vector<Token> lex(std::string src)
{

  char c;
  
  std::vector<Token> tlist;
  Token cur;

  std::string alphabet = "abcefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string numeric = "0123456789";
  std::string operators = "&|^~!=<>:+-*/";
  std::string white = "{[(#?;)]}\r\t\n ";
  
  for (int i = 0; i < src.size(); i++) {

    c = src[i];
    
    if (numeric.find(c) != -1) {
      std::cout << "numeric\n";
    } else if (operators.find(c) != -1) {
      std::cout << "operational\n";
    } else if (alphabet.find(c) != -1) {
      std::cout << "alphabetical\n";
    } else if (white.find(c) != -1) {
      std::cout << "whitespace\n";
    } else {
      std::cout << "unknown\n";
    }
  }

  
  cur.ttype = EOF;
  cur.value = "";
    
  tlist.push_back(cur);

  return tlist;
}

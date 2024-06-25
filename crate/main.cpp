#include "crate.hpp"

int main()
{
  std::string sample = "hi";
  
  vector<Token> tokens = lex(sample);
  return 0;
}

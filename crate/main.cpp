#include "crate.hpp"

int main()
{
  std::string sample = "hi! this is a test";
  
  std::vector<Token> tokens = lex(sample);
  return 0;
}

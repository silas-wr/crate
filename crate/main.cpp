#include "crate.hpp"

int main()
{
  std::string sample = "hi";
  
  std::vector<Token> tokens = lex(sample);
  return 0;
}

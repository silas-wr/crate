#include "crate.hpp"

int main()
{
  std::string sample = "hi";
  
  crate::Tokens tokens = lex(sample);
  return 0;
}

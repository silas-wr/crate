#include "crate.hpp"

int main(int argc, char* argv[])
{
  std::string sample = "hi! this is a test";
  
  std::vector<Token> tokens = lex(sample);

  for(const Token& tk : tokens) 
    cout << "Token = " << tk.ttype << ", " << tk.value;
  
  return 0;
}

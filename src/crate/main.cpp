#include "crate.hpp"

int main(int argc, char* argv[])
{
  string fname;
  
  if (argc != 2) {
    cout << "Usage: crate FILE";
    exit(1);
  } else {
    string fname = argv[1];
  }

  string content = "";
  string line;
  
  ifstream fi(fname);
  
  while (getline(fi,line)){
    content += line;
    content += '\n';
  }
  
  fi.close();
  
  vector<Token> tokens = lex(content);

  for(const Token& tk : tokens) 
    cout << "Token = " << tk.ttype << ", " << tk.value << "\n";
  
  return 0;
}

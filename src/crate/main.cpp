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
  
  for(const Token& tk : lex(content)) 
    cout << "Token = " << tk.ttype << ", " << tk.value << "\n";
  
  return 0;
}

#include "crate.hpp"

int main(int argc, char* argv[])
{
  string fname;
  
  if (argc != 2) {
    cout << "Usage: crate FILE";
    exit(1);
  }

  string content = "";
  string line;
  
  ifstream fi(argv[1]);

  if (fi.is_open()) {
    ;
  } else {
    cout << "File '" << argv[1] << "' could not be opened.";
  }
  
  while (getline(fi,line)){
    content += line;
    content += '\n';
  }
  
  fi.close();

  vector<Token> tokens = lex(content);
  Program parsed = parse(tokens);
  
  return 0;
}

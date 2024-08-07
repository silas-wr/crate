#include "crate.hpp"

int main(int argc, char* argv[])
{  
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

  for (int tok = 0; tok < tokens.size(); tok++) {
    cout << "Token " << tokens.at(tok).ttype << ": " << tokens.at(tok).value << "\n";
  }
  
  Program parsed = parse(tokens);

  prog(parsed);
  
  return 0;
}

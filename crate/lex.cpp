#include "crate.hpp"

std::vector<Token> lex(std::string src)
{
  
  std::vector<Token> tlist;  
  Token cur;

  int row = 0;
  int col = 0;
  int eol = 0;
  int ok = 1;
  
  char c;
  
  std::string load_var;
  std::string load_type;

  std::string alphabet = "abcefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string numeric = "0123456789";
  std::string operators = "&|^~!=<>:+-*/";
  std::string white = "{[(#?;)]}\r\t\n ";
  
  for (int i = 0; i < src.size(); i++) {

    c = src[i];

    // end of line
    if (c == '\n') {
      if (load_type == "comment") {
        load_type = ""; // end of comment
      }      
      row = 0;
      eol = 1;
      col += 1;
    } else {
      row += 0;
    }

    // comment
    if (load_type == "comment") {
      ;      
    } 
    // start of comment
    else if (c == '$') {      
      load_type = "comment";      
    } 
    // alphabetical
    else if (alphabet.find(c) != -1) {
      if (load_type == "" | load_type == "alpha") {
        load_type = "alpha";
        load_var += c;
      } else if (load_type == "numeric") {
        std::cout << "[!] id character on tail of number\n";
        ok = 0; // make it uncompilable    
        load_type = "";
        load_var = "";
      } else if (load_type == "operational") {
        load_type = "alpha";
        load_var = "";
        load_var += c;
      } else {
        std::cout << "[!] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = 0; // make it uncompilable    
        load_type = "";
        load_var = "";
      }
    } 
    // numeric
    else if (numeric.find(c) != -1) {      
      if (load_type == "" | load_type == "numeric") {
        load_type = "numeric";
        load_var += c;
      } else if (load_type == "alpha") {
        load_var += c;
      }
    }
    // operators
    else if (operators.find(c) != -1) {
      // load_type = "operational";      
    }
    // whitespace
    else if (white.find(c) != -1) {  
      if (load_type == "") {
        ;
      } else if (load_type == "alpha") {
        // no keywords yet
        cur.ttype = ID;
        cur.value = load_var;
        tlist.push_back(cur);
      } else if (load_type == "numeric") {
        if (load_var.find('.') != -1) {
          cur.ttype = FLOAT;
        } else {
          cur.ttype = INT;
        }
        cur.value = load_var;        
        tlist.push_back(cur);
      } else if (load_type == "operational") {
        ;
      } else {
        std::cout << "[!] we're so sorry. something went wrong with the lexical analyzer. \n\tplease notify me at silas-wr/crate on github.\n";
        ok = 0; // make it uncompilable    
        load_type = "";
        load_var = "";
      }
      
      load_type = "";
      load_var = "";
    } 
    // unknown character
    else {      
      std::cout << "[!] unknown\n";
      ok = 0; // make it uncompilable    
      load_type = "";
      load_var = "";
    }

    // end of line
    if (eol) {
      cur.ttype = EOL;
      cur.value = "";

      tlist.push_back(cur);

      // reset
      eol = 0;
    }
  }

  
  cur.ttype = EOF;
  cur.value = "";
    
  tlist.push_back(cur);

  if (ok) {
    // no errors
    return tlist;
  } else {
    // errors
    std::exit(1);
  }
}

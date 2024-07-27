#include "crate.hpp"

/* string strparse(string str)
{
  // this code assumes that the string is syntactically correct, thanks to the lexer. all it does is produce the actual string, not a string containing it.
  // Ex. if i put `strparse("\\0");`, I will get a string containing the EOF character.
  // Ex. if i put `strparse("\\u1234);`, I will get a string containing the Unicode character U+1234.

  char c;
  string out = "";
  string unicode = "";
  string octal = "";
  int uni = 4;
  int oct = 3;
  int uchar = 0;
  int ochar = 0;
  bool usequence = false;
  bool osequence = false;
  bool slash = false;
  
  vector<string> octal {"\000", "\001", "\002", "\003", "\004", "\005", "\006", "\007", "\010", "\011", "\012", "\013", "\014", "\015", "\016",\
  "\017", "\020", "\021", "\022", "\023", "\024", "\025", "\026", "\027", "\030", "\031", "\032", "\033", "\034", "\035",\ 
  "\036", "\037", "\040", "\041", "\042", "\043", "\044", "\045", "\046", "\047", "\050", "\051", "\052", "\053", "\054",\
  "\055", "\056", "\057", "\060", "\061", "\062", "\063", "\064", "\065", "\066", "\067", "\070", "\071", "\072", "\073",\
  "\074", "\075", "\076", "\077", "\100", "\101", "\102", "\103", "\104", "\105", "\106", "\107", "\110", "\111", "\112",\
  "\113", "\114", "\115", "\116", "\117", "\120", "\006", "\007", "\010", "\011", "\012", "\013", "\014", "\015", "\016",\
  "\000", "\001", "\002", "\003", "\004", "\005", "\006", "\007", "\010", "\011", "\012", "\013", "\014", "\015", "\016",\ 
  "\000", "\001", "\002", "\003", "\004", "\005", "\006", "\007", "\010", "\011", "\012", "\013", "\014", "\015", "\016",\
  "\000", "\001", "\002", "\003", "\004", "\005", "\006", "\007", "\010", "\011", "\012", "\013", "\014", "\015", "\016",\
  "\000", "\001", "\002", "\003", "\004", "\005", "\006", "\007", "\010", "\011", "\012", "\013", "\014", "\015", "\016",\
  "\000", "\001", "\002", "\003", "\004", "\005", "\006", "\007", "\010", "\011", "\012", "\013", "\014", "\015", "\016",\ };
  
  for (int i = 0; i < str.size(); i++) {
    c = str[i];
    
    switch (c) {
      case '\\':
      	if (slash) {
      	  out += c;
      	  slash = false;
      	} else {
      	  slash = true;
      	}
        break;
      case '0':
      	if (slash) {
      	  out += '\0';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case 'a':
      	if (slash) {
      	  out += '\a';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case '"':
      	if (slash) {
      	  out += '\"';
      	  slash = false;
      	} else {
	  // this won't run: it'll have been corrected in the lexer.
	  ;	
      	}
      case '\'':
      	if (slash) {
      	  out += '\'';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case '?':
      	if (slash) {
      	  out += '\?';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case 'b':
      	if (slash) {
      	  out += '\b';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case 'f':
      	if (slash) {
      	  out += '\f';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case 'n':
      	if (slash) {
      	  out += '\n';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case 'r':
      	if (slash) {
      	  out += '\r';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case 't':
      	if (slash) {
      	  out += '\t';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case 'v':
      	if (slash) {
      	  out += '\v';
      	  slash = false;
      	} else {
      	  out += c;
      	}
      case 'u':
      	if (slash) {
      	  usequence = true;
      	} else {
      	  out += c;
      	}
      case 'o':
        if (slash) {
      	  osequence = true;
      	} else {
      	  out += c;
      	}
      default:
      	if (slash & !usequence & !osequence) {
      	  cout << "Invalid escape sequence \\" << c << " .";
      	  exit(1);
      	} else if (usequence) {
      	} else if (osequence) {
      	  if (ochars.find(c) != 1) {
      	    oct--;
      	    
      	    if (oct == 0) {
      	      oct = 3;
      	      out += ""
      	    }
      	  } else {
      	    cout << "Invalid octal sequence with " << c << " .";
       	    exit(1);
      	  }
      	} else {
      	  out += c;
      	}
  }
} */

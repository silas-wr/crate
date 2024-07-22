#include "crate.hpp"

bool isUpper(string s) {
    for (int i = 0; i < s.size(); i++) {
       if (isupper(s.at(i))) {
           ;
       } else {
           return false; // not uppercase
       }
    }
    
    return true; // no characters caused a false to be returned; thus, it must be uppercase
}

#include "crate.hpp"

bool isUpper(const string& s) {
    return all_of(s.begin(), s.end(), [](unsigned char c){ return isupper(c); });
}

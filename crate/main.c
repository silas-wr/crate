#include "crate.h"

main()
{
  char sample[] = {'h', 'i', EOF};
  
  lex(sample);
  return 0;
}

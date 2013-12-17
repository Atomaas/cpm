#include <string>
#include <iostream>
#include <cassert>

#include "WeinerST.hpp"

/*
  apple
  banana
  
  text = dbcadacadab$
  patt = abcadabcad#
 */

int main(int argc, char* argv[]) {
  std::cout << "Circular pattern matching\n";
  std::string text = "dbcadacadab$";
  std::string pattern = "abcadabcad#";
  WeinerST st;
  st.insertText(text);
  st.insertPattern(pattern);
  st.printMatches();
  return 0;
}

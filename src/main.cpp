#include <string>
#include <iostream>
#include <cassert>

#include "WeinerST.hpp"

/*
  text = dbcadacadab$
  patt = abcadabcad#
 */

int main(int argc, char* argv[]) {
  std::cout << "Circular pattern matching\n";
  std::string text = "dbcadacadab$";
  std::string pattern = "abcadabcad#";
  WeinerST st;
  st.insertText(text);
  std::cout << "T tree:\n";
  st.printTree();
  //
  st.insertPattern(pattern);
  std::cout << "T tree with P:\n";
  st.printTree();
  st.printMatches();
  //
  st.removePattern();
  std::cout << "T tree after P-removal:\n";
  st.printTree();
  //
  st.insertPattern(pattern);
  std::cout << "T tree after P-removal and re-insertion:\n";
  st.printTree();
  st.printMatches();
  //
  st.removePattern();
  std::cout << "T tree after 2x P-removal:\n";
  st.printTree();
  return 0;
}

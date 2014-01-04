#include <set>
#include <string>
#include <iostream>
#include <cassert>

#include "test.hpp"
#include "cpm.hpp"
#include "cpi2.hpp"

/*
  text = dbcadacadab$
  patt = abcadabcad#
 */

int main(int argc, char* argv[]) {
  // timeCPM();
  timeCPI2();
  
  // std::set<int> occ;
  // cpm::Cpi2 x("dbcadacadab");
  // occ  = x.cmatch("abcad");
  // std::cout << "Matches:\n";
  // for (std::set<int>::iterator iter = occ.begin(); iter != occ.end(); iter++) {
  //   std::cout << *iter << "\n";
  // }
  
  // std::string text = "dbcadacadab$";
  // std::string pattern = "abcadabcad#";
  // cpm::WeinerST st;
  // st.insertText(text);
  // std::cout << "T tree:\n";
  // st.printTree();
  // //
  // st.insertPattern(pattern);
  // std::cout << "T tree with P:\n";
  // st.printTree();
  // st.printMatches();
  // //
  // st.removePattern();
  // std::cout << "T tree after P-removal:\n";
  // st.printTree();
  // //
  // st.insertPattern(pattern);
  // std::cout << "T tree after P-removal and re-insertion:\n";
  // st.printTree();
  // st.printMatches();
  // //
  // st.removePattern();
  // std::cout << "T tree after 2x P-removal:\n";
  // st.printTree();
  return 0;
}

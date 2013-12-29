#ifndef CPM_HPP
#define CPM_HPP

#include <vector>
//#include <set>

#include "WeinerST.hpp"

namespace cpm {
  
  // These functions assume that '$' and '#' are not members of the input alphabet
  // and appends those characters to the text and pattern, respectively.
  std::set<int> cpm(std::string text, std::string pattern);
  std::vector< std::set<int> > cpm(std::string text_filepath, std::vector<std::string> pattern_filepaths);

} // namespace cpm

#endif // CPM_HPP

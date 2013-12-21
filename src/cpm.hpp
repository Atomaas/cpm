#ifndef CPM_HPP
#define CPM_HPP

#include <vector>
//#include <set>

#include "WeinerST.hpp"

namespace cpm {
  
  
  // This function assumes that the text and pattern have unique terminating characters:
  std::set<int> cpm(std::string &text, std::string &pattern);

  // This function assumes that '$' and '#' are not members of the input alphabet
  // and appends those characters to the text and pattern, respectively.
  std::vector< std::set<int> > cpm(std::string text_filepath, std::vector<std::string> pattern_filepaths);

} // namespace cpm

#endif // CPM_HPP

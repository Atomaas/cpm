#include <iostream>
#include <cassert>

#include "cpm.hpp"
#include "multv.hpp"
#include "cpi2.hpp"
#include "util.hpp"

namespace cpm {

  std::set<int> multvMatch(std::string text, std::string pattern) {
    cpm::Multv multv_index(text);
    return multv_index.cmatch(pattern);
  }
  
  std::vector< std::set<int> > multvMatch(std::string text_filepath, std::vector<std::string> pattern_filepaths) {
    std::string text = readFile(text_filepath);
    cpm::Multv multv_index(text);
    std::vector< std::set<int> > matches;
    for (std::vector<std::string>::iterator iter = pattern_filepaths.begin(); iter != pattern_filepaths.end(); iter++) {
      std::string pattern = readFile(*iter);
      multv_index.cmatch(pattern);
    }
    return matches;
  }

  std::set<int> cpi2Match(std::string text, std::string pattern) {
    cpm::Cpi2 cpi2_index(text);
    return cpi2_index.cmatch(pattern);
  }
  
  std::vector< std::set<int> > cpi2Match(std::string text_filepath, std::vector<std::string> pattern_filepaths) {
    std::string text = readFile(text_filepath);
    cpm::Cpi2 cpi2_index(text);
    std::vector< std::set<int> > matches;
    for (std::vector<std::string>::iterator iter = pattern_filepaths.begin(); iter != pattern_filepaths.end(); iter++) {
      std::string pattern = readFile(*iter);
      cpi2_index.cmatch(pattern);
    }
    return matches;
  }

} // namespace cpm

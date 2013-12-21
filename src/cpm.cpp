#include <cassert>

#include "cpm.hpp"
#include "util.hpp"

namespace cpm {

  std::set<int> cpm(std::string &text, std::string &pattern) {
    // add termination character
    // std::set<char> text_alpha = alphabet(text);
    // std::set<char> pattern_alpha = alphabet(pattern);
    // assert(text_alpha.find('$') == text_alpha.end());
    // assert(text_alpha.find('#') == text_alpha.end());
    // assert(pattern_alpha.find('$') == pattern_alpha.end());
    // assert(pattern_alpha.find('#') == pattern_alpha.end());
    // text.push_back('$');
    // pattern.push_back('#');
    //
    WeinerST st;
    st.insertText(text);
    st.insertPattern(pattern, false);
    return st.getMatches();
  }
  
  std::vector< std::set<int> > cpm(std::string text_filepath, std::vector<std::string> pattern_filepaths) {
    std::string text = readFile(text_filepath);
    // add termination character
    std::set<char> text_alpha = alphabet(text);
    assert(text_alpha.find('$') == text_alpha.end() && text_alpha.find('#') == text_alpha.end());
    text.push_back('$');
    //
    WeinerST st;
    st.insertText(text);
    std::vector< std::set<int> > matches;
    for (std::vector<std::string>::iterator iter = pattern_filepaths.begin(); iter != pattern_filepaths.end(); iter++) {
      std::string pattern = readFile(*iter);
      // add termination character
      std::set<char> pattern_alpha = alphabet(pattern);
      assert(pattern_alpha.find('$') == pattern_alpha.end() && pattern_alpha.find('#') == pattern_alpha.end());
      pattern.push_back('#');
      //
      st.insertPattern(pattern);
      matches.push_back(st.getMatches());
      st.removePattern();
    }
    return matches;
  }

} // namespace cpm

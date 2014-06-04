#include <cassert>

#include "multv.hpp"
#include "util.hpp"

namespace cpm {

  Multv::Multv(std::string &text) {
    std::set<char> text_alpha = alphabet(text);
    assert(text_alpha.find('$') == text_alpha.end() && text_alpha.find('#') == text_alpha.end());
    text.push_back('$'); // add termination character
    st_ = new WeinerST(text); // deleted in Multv destructor
  }
  
  Multv::~Multv() {
    assert(st_ != NULL);
    delete st_;
    st_ = NULL;
  }

  // Finds all occurrences of a circular pattern.
  std::set<int> Multv::cmatch(std::string &pattern) {
    assert(st_ != NULL);
    std::set<char> pattern_alpha = alphabet(pattern);
    assert(pattern_alpha.find('$') == pattern_alpha.end() && pattern_alpha.find('#') == pattern_alpha.end());
    pattern += pattern; // form PP
    pattern.push_back('#'); // add termination character
    st_->insertPattern(pattern, false);
    std::set<int> matches(st_->getMatches());
    st_->removePattern();
    return matches;
  }

};

#ifndef MULTV_HPP
#define MULTV_HPP

#include <set>
#include <string>

#include "WeinerST.hpp"

namespace cpm {

  // Mult-V data structure
  // (Suffix tree-based circular pattern index)
  class Multv {
  public:
    Multv(std::string &text);
    ~Multv();
    std::set<int> cmatch(std::string &pattern);
  private:
    WeinerST* st_;
  };

}; // namespace cpm

#endif // CPI2_HPP

#ifndef CPI2_HPP
#define CPI2_HPP

#include <set>
#include <string>

namespace cpm {

  // CPI-II data structure
  // Illiopoulos and Rahman - "Indexing circular patterns" (2008).
  class Cpi2 {
  public:
    Cpi2(std::string &text);
    ~Cpi2();
    std::set<int> cmatch(std::string &pattern);
  private:
    char* text_;
    int n_; // text length
    int* sa_; // suffix array
    int* inv_sa_; // inverse suffix array
  };

}; // namespace cpm

#endif // CPI2_HPP

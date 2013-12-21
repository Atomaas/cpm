#include <string>
#include <iostream>
#include <cassert>
#include "test.hpp"
#include "cpm.hpp"
#include "util.hpp"

std::string setToStr(std::set<int> x) {
  std::string s = "{";
  std::set<int>::iterator iter = x.begin();
  if (iter != x.end()) {
    s += intToStr(*iter);
    iter++;
    for (; iter != x.end(); iter++) {
      s += ", " + intToStr(*iter);
    }
    s += "}";
  }
  return s;
}

void timeCPM(const int num_trials /* = 1 */) {
  const std::string test_dir = "../test/";
  
  std::vector< std::string > text_filepaths;
  text_filepaths.push_back("t1.fas");
  // text_filepaths.push_back("c5.fa");
  // text_filepaths.push_back("c6.fa");
  
  std::vector< std::string > pattern_filepaths;
  pattern_filepaths.push_back("p1.fas");
  // pattern_filepaths.push_back("v1.fas");
  // pattern_filepaths.push_back("v2.fas");
  // pattern_filepaths.push_back("v3.fas");
  // pattern_filepaths.push_back("v4.fas");
  // pattern_filepaths.push_back("v5.fas");
  // pattern_filepaths.push_back("v6.fas");
  // pattern_filepaths.push_back("v7.fas");
  // pattern_filepaths.push_back("v8.fas");
  // pattern_filepaths.push_back("v9.fas");
  // pattern_filepaths.push_back("v10.fas");

  std::cout << "text,pattern,time,matches\n";

  for (std::vector< std::string >::iterator iter_t = text_filepaths.begin(); iter_t != text_filepaths.end(); iter_t++) {
    std::string text = readFile(test_dir + *iter_t);
    // add termination character
    std::set<char> text_alpha = alphabet(text);
    assert(text_alpha.find('$') == text_alpha.end() && text_alpha.find('#') == text_alpha.end());
    text.push_back('$');
    //
    for (std::vector< std::string >::iterator iter_p = pattern_filepaths.begin(); iter_p != pattern_filepaths.end(); iter_p++) {
      std::string pattern = readFile(test_dir + *iter_p);
      // add termination character
      std::set<char> pattern_alpha = alphabet(pattern);
      assert(pattern_alpha.find('$') == pattern_alpha.end() && pattern_alpha.find('#') == pattern_alpha.end());
      pattern.push_back('#');
      //
      std::set<int> matches;
      
      clock_t t0 = 0, t1 = 0;
      t0 = clock();
      for (int i = 0; i < num_trials; i++) {
        matches = cpm::cpm(text, pattern);
      }
      t1 = clock();
      double avg_dt = ((double)(t1 - t0)) / CLOCKS_PER_SEC / num_trials;

      std::cout << *iter_t << "," << *iter_p << ", " << avg_dt << "," << setToStr(matches) << "\n";
    }
  }
}

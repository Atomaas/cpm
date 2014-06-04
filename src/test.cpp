#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include "test.hpp"
#include "cpm.hpp"
#include "cpi2.hpp"
#include "util.hpp"

void timeMultv(const int num_trials /* = 1 */) {
  const std::string test_dir = "../test/test2/";
  std::vector< std::string > text_filepaths;
  // text_filepaths.push_back("t1.fas");
  //
  text_filepaths.push_back("t5.fas");
  // text_filepaths.push_back("t10.fas");
  // text_filepaths.push_back("t15.fas");
  // text_filepaths.push_back("t20.fas");
  // text_filepaths.push_back("t25.fas");
  // text_filepaths.push_back("t30.fas");
  
  std::vector< std::string > pattern_filepaths;
  // pattern_filepaths.push_back("p1.fas");
  //
  pattern_filepaths.push_back("p5a.fas");
  pattern_filepaths.push_back("p5b.fas");
  pattern_filepaths.push_back("p5c.fas");
  // pattern_filepaths.push_back("p10a.fas");
  // pattern_filepaths.push_back("p10b.fas");
  // pattern_filepaths.push_back("p10c.fas");
  // pattern_filepaths.push_back("p15a.fas");
  // pattern_filepaths.push_back("p15b.fas");
  // pattern_filepaths.push_back("p15c.fas");
  // pattern_filepaths.push_back("p20a.fas");
  // pattern_filepaths.push_back("p20b.fas");
  // pattern_filepaths.push_back("p20c.fas");
  // pattern_filepaths.push_back("p25a.fas");
  // pattern_filepaths.push_back("p25b.fas");
  // pattern_filepaths.push_back("p25c.fas");
  // pattern_filepaths.push_back("p30a.fas");
  // pattern_filepaths.push_back("p30b.fas");
  // pattern_filepaths.push_back("p30c.fas");
  
  std::cout << "text, pattern, time, matches\n";

  for (std::vector< std::string >::iterator iter_t = text_filepaths.begin(); iter_t != text_filepaths.end(); iter_t++) {
    std::string text = readFile(test_dir + *iter_t);
    stripchar(text, '\n');
    for (std::vector< std::string >::iterator iter_p = pattern_filepaths.begin(); iter_p != pattern_filepaths.end(); iter_p++) {
      std::string pattern = readFile(test_dir + *iter_p);
      std::set<int> matches;
      
      clock_t t0 = 0, t1 = 0;
      t0 = clock();
      for (int i = 0; i < num_trials; i++) {
        matches = cpm::multvMatch(text, pattern);
      }
      t1 = clock();
      double avg_dt = ((double)(t1 - t0)) / CLOCKS_PER_SEC / num_trials;
      std::cout << *iter_t << ", " << *iter_p << ", " << avg_dt << ", " << setToStr(matches) << "\n";
    }
  }
}

void timeCPI2(const int num_trials /* = 1 */) {
  const std::string test_dir = "../test/test2/";
  std::vector< std::string > text_filepaths;
  // Test 0
  // text_filepaths.push_back("t1.fas");
  //
  // Test 1
  // text_filepaths.push_back("c5.fa");
  // text_filepaths.push_back("c6.fa");
  //
  // Test 2
  text_filepaths.push_back("t5.fas");
  // text_filepaths.push_back("t10.fas");
  // text_filepaths.push_back("t15.fas");
  // text_filepaths.push_back("t20.fas");
  // text_filepaths.push_back("t25.fas");
  // text_filepaths.push_back("t30.fas");
  
  std::vector< std::string > pattern_filepaths;
  // Test 0
  // pattern_filepaths.push_back("p1.fas");
  //
  // Test 1
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
  //
  // Test 2
  pattern_filepaths.push_back("p5a.fas");
  pattern_filepaths.push_back("p5b.fas");
  pattern_filepaths.push_back("p5c.fas");
  // pattern_filepaths.push_back("p10a.fas");
  // pattern_filepaths.push_back("p10b.fas");
  // pattern_filepaths.push_back("p10c.fas");
  // pattern_filepaths.push_back("p15a.fas");
  // pattern_filepaths.push_back("p15b.fas");
  // pattern_filepaths.push_back("p15c.fas");
  // pattern_filepaths.push_back("p20a.fas");
  // pattern_filepaths.push_back("p20b.fas");
  // pattern_filepaths.push_back("p20c.fas");
  // pattern_filepaths.push_back("p25a.fas");
  // pattern_filepaths.push_back("p25b.fas");
  // pattern_filepaths.push_back("p25c.fas");
  // pattern_filepaths.push_back("p30a.fas");
  // pattern_filepaths.push_back("p30b.fas");
  // pattern_filepaths.push_back("p30c.fas");
  
  std::cout << "text, pattern, time, matches\n";

  for (std::vector< std::string >::iterator iter_t = text_filepaths.begin(); iter_t != text_filepaths.end(); iter_t++) {
    std::string text = readFile(test_dir + *iter_t);
    stripchar(text, '\n');
    cpm::Cpi2 cpi2_index(text);
    for (std::vector< std::string >::iterator iter_p = pattern_filepaths.begin(); iter_p != pattern_filepaths.end(); iter_p++) {
      std::string pattern = readFile(test_dir + *iter_p);
      std::set<int> matches;
      
      clock_t t0 = 0, t1 = 0;
      t0 = clock();
      for (int i = 0; i < num_trials; i++) {
        matches = cpi2_index.cmatch(pattern);
      }
      t1 = clock();
      double avg_dt = ((double)(t1 - t0)) / CLOCKS_PER_SEC / num_trials;
      std::cout << *iter_t << ", " << *iter_p << ", " << avg_dt << ", " << setToStr(matches) << "\n";
    }
  }
}

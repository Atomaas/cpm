#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <set>

std::set<char> alphabet(const std::string &s);
int alphabetSize(const std::string s);
std::string readFile(std::string filename);
// void getStringFromFile(std::string base_path, std::string &s, std::string &file_path);
std::string intToStr(int n);

#endif // UTIL_HPP

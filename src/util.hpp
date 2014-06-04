#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <set>

std::set<char> alphabet(const std::string &s);
int alphabetSize(const std::string s);
std::string intToStr(int n);
void stripchar(std::string &s, char c);
std::string readFile(std::string filename);
std::string setToStr(std::set<int> x);
// void getStringFromFile(std::string base_path, std::string &s, std::string &file_path);

#endif // UTIL_HPP

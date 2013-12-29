// #include <sys/stat.h>
// #include <dirent.h>
// #include <stack>
// #include <set>
#include <algorithm>
#include <fstream>
#include <sstream> // ostringstream
#include <cassert>

#include "util.hpp"

std::set<char> alphabet(const std::string &s) {
  std::set<char> alpha;
  for (int i = 0; i < (signed)s.size(); i++) {
    alpha.insert(s[i]);
  }
  return alpha;
}

int alphabetSize(const std::string &s) {
  return alphabet(s).size();
}

std::string intToStr(int n) {
  std::ostringstream ss;
  ss << n;
  return ss.str();
}

void stripchar(std::string &s, char c) {
  s.erase(std::remove(s.begin(), s.end(), c), s.end());
}

std::string readFile(std::string filename) {
  std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
  assert(in);
  std::string s = "";
  if (in) {
    in.seekg(0, std::ios::end);
    s.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&s[0], s.size());
    in.close();
  }
  return s;
}

// bool isFile(std::string path) {
//   struct stat st;
//   lstat(path.c_str(), &st);
//   return S_ISREG(st.st_mode);
// }

// void getStringFromFile(std::string base_path, std::string &s, std::string &file_path) {
//   static std::stack<std::string> dirs_to_visit;
//   static std::string current_path = "";
//   static DIR* current_dir = NULL;
//   if (base_path != "") {
//     if (base_path[base_path.length() - 1] == '/') {
//       base_path = base_path.substr(0, base_path.length() - 1);
//     }
//     current_path = base_path;
//     current_dir = opendir(current_path.c_str());
//     assert(current_dir != NULL);
//     while (!dirs_to_visit.empty()) {
//       dirs_to_visit.pop();
//     }
//   }
//   assert(current_dir != NULL);
//   while (true) {
//     struct dirent* ent = readdir(current_dir);
//     if (ent != NULL) {
//       if (ent->d_name[0] != '.') {
//         if (isFile(current_path + "/" + ent->d_name)) {
//           file_path = current_path + "/" + ent->d_name;
//           s = readFile(file_path);
//           break;
//         }
//         else {
//           dirs_to_visit.push(current_path + "/" + ent->d_name);
//         }
//       }
//     }
//     else {
//       closedir(current_dir);
//       if (!dirs_to_visit.empty()) {
//         current_path = dirs_to_visit.top();
//         current_dir = opendir(current_path.c_str());
//         assert(current_dir != NULL);
//         dirs_to_visit.pop();
//       }
//       else {
//         s = "";
//         file_path = "";
//         break;
//       }
//     }
//   }
// }

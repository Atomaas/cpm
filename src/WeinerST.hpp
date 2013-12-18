#ifndef WEINERST_HPP_
#define WEINERST_HPP_

#include <string>
#include <map>
#include <set>
#include <stack>
#include "WeinerInode.hpp"
#include "WeinerLeaf.hpp"
#include "TreeMutation.hpp"

class WeinerST {
public:
  WeinerST();
  void insertText(std::string &s);
  void insertPattern(std::string &s);
  void removePattern();
  void printMatches();
  void printTree();
private:
  void insertString(const bool text_node);
  void buildBaseTree(std::string &s);
  void extend(int i, const bool text_node);
  WeinerInode* breakEdge(WeinerNode* const child_node,
                         char edge_char,
                         int edge_label_prefix_length,
                         const bool text_node);
  char getLabelChar(Label label, int i);
  std::string getLabelString(Label label);
  void printTreeTraverse(WeinerNode* const node, int indent);
  WeinerInode* root_;
  WeinerLeaf* prev_leaf_;
  WeinerLeaf* text_prev_leaf_;
  std::string text_string_;
  std::string pattern_string_;
  std::set<int> matches_; // positions in the text that match a rotation of the pattern
  std::stack<TreeMutation*> tree_mutations_;
};

#endif // WEINERST_HPP_

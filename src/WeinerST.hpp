#ifndef WEINERST_HPP_
#define WEINERST_HPP_

#include <string>
#include <map>
#include <set>
#include <stack>
#include "WeinerInode.hpp"
#include "WeinerLeaf.hpp"

enum MutationType {AddIndicator};

/* AddIndicator (Node*)
   AddLink (Node*, c)
   breakedge
   - create a new node
   - 
 */

struct Mutation {
  MutationType mutation_type_;
  WeinerNode* node_;
  Mutation(MutationType mutation_type, WeinerNode* const node)
    : mutation_type_ (mutation_type),
      node_ (node)  {
    assert(node != NULL);
  }
};

class WeinerST {
public:
  WeinerST();
  void insertText(std::string &s);
  void insertPattern(std::string &s);
  void removePattern();
  void printMatches();
  void printTree();
private:
  void insertString(bool text_node);
  void buildBaseTree(std::string &s);
  void extend(int i, bool text_node);
  WeinerInode* breakEdge(WeinerNode* const child_node,
                         char edge_char,
                         int edge_label_prefix_length);
  char getLabelChar(Label label, int i);
  std::string getLabelString(Label label);
  void printTreeTraverse(WeinerNode* const node, int indent);
  WeinerInode* root_;
  WeinerLeaf* prev_leaf_;
  WeinerLeaf* text_prev_leaf_;
  std::string text_string_;
  std::string pattern_string_;
  std::set<int> matches_;
  std::stack<Mutation> tree_mutations_;
};

#endif // WEINERST_HPP_

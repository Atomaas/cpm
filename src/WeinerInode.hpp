#ifndef WEINERINODE_HPP_
#define WEINERINODE_HPP_

#include <string>
#include <map>
#include <set>

#include "WeinerNode.hpp"

class WeinerInode : public WeinerNode {
public:
  WeinerInode(WeinerInode* const parent,
              bool text_node,
              int edge_label_start,
              int edge_label_length,
              int path_label_start,
              int path_label_length);
  bool checkChild(char c);
  int getNumChildren();
  WeinerNode* getChild(char c);
  std::map<char, WeinerNode*> getChildren();
  void addChild(char c, WeinerNode* const node);
  void removeChild(char c);
  void replaceChild(char c, WeinerNode* const node);
  void addIndicator(char c);
  void removeIndicator(char c);
  bool checkIndicator(char c);
  std::set<char> getIndicatorVector();
  void setIndicatorVector(std::set<char> indicators);
  std::string getIndicatorString();
  void addLink(char c, WeinerInode* const node);
  void removeLink(char c);
  bool checkLink(char c);
  WeinerInode* getLink(char c);
  std::string getLinkString();
  bool isLeaf();
private:
  std::map<char, WeinerNode*> children_;
  std::set<char> indicator_;
  std::map<char, WeinerInode*> links_;
};

#endif // WEINERINODE_HPP_

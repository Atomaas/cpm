#ifndef WEINERLEAF_HPP_
#define WEINERLEAF_HPP_

#include "WeinerNode.hpp"

class WeinerLeaf : public WeinerNode {
public:
  WeinerLeaf(WeinerInode* const parent,
             bool text_node,
             int edge_label_start,
             int edge_label_length,
             int path_label_start,
             int path_label_length,
             int leaf_id);
  int getLeafId();
  bool isLeaf();
private:
  int leaf_id_;
};

#endif // WEINERLEAF_HPP_

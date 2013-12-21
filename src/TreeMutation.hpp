#ifndef TREEMUTATION_HPP
#define TREEMUTATION_HPP

#include "WeinerNode.hpp"
#include "WeinerInode.hpp"

namespace cpm {

enum MutationOp {DeleteNode, RemoveChild, RemoveIndicator, RemoveLink, ReplaceChild, SetEdgeLabel, SetParent};

struct TreeMutation {
  MutationOp mutation_op_;
  TreeMutation(MutationOp mutation_op);
  virtual ~TreeMutation();
};

struct DeleteNodeMut : public TreeMutation {
  WeinerNode* node_;
  DeleteNodeMut(WeinerNode* node);
};

struct RemoveCharMut : public TreeMutation {
  WeinerInode* node_;
  char c_;
  RemoveCharMut(MutationOp mutation_op, WeinerInode* node, char c);
};

struct ReplaceChildMut : public TreeMutation {
  WeinerInode* parent_node_;
  char c_;
  WeinerNode* new_child_node_;
  WeinerNode* old_child_node_;
  ReplaceChildMut(WeinerInode* parent_node, char c, WeinerNode* new_child_node, WeinerNode* old_child_node);
};

struct SetEdgeLabelMut : public TreeMutation {
  WeinerNode* node_;
  Label label_;
  SetEdgeLabelMut(WeinerNode* node, Label label);
};

struct SetParentMut : public TreeMutation {
  WeinerNode* child_node_;
  WeinerInode* parent_node_;
  SetParentMut(WeinerNode* child_node, WeinerInode* parent_node);
};

}

#endif // TREEMUTATION_HPP

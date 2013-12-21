#include <cassert>

#include "TreeMutation.hpp"

namespace cpm {

TreeMutation::TreeMutation(MutationOp mutation_op)
  : mutation_op_ (mutation_op) {
}

TreeMutation::~TreeMutation() {
}

DeleteNodeMut::DeleteNodeMut(WeinerNode* node)
  : TreeMutation(DeleteNode),
    node_ (node) {
  assert(node_ != NULL);
}

RemoveCharMut::RemoveCharMut(MutationOp mutation_op, WeinerInode* node, char c)
  : TreeMutation(mutation_op),
    node_ (node),
    c_ (c) {
  assert(node != NULL);
  if (mutation_op == RemoveChild) {
    assert(node->checkChild(c));
  }
  else if (mutation_op == RemoveIndicator) {
    assert(node->checkIndicator(c));
  }
  else if (mutation_op == RemoveLink) {
    assert(node->checkLink(c));
  }
  else {
    assert(false);
  }
}

ReplaceChildMut::ReplaceChildMut(WeinerInode* parent_node,
                                 char c,
                                 WeinerNode* new_child_node,
                                 WeinerNode* old_child_node)
  : TreeMutation(ReplaceChild),
    parent_node_ (parent_node),
    c_ (c),
    new_child_node_ (new_child_node),
    old_child_node_ (old_child_node) {
  assert(parent_node != NULL && new_child_node != NULL && old_child_node != NULL);
  assert(parent_node->getChild(c) == old_child_node);
}

SetEdgeLabelMut::SetEdgeLabelMut(WeinerNode* node, Label label)
  : TreeMutation(SetEdgeLabel),
    node_ (node),
    label_ (label) {
  assert(node != NULL);
}

SetParentMut::SetParentMut(WeinerNode* child_node, WeinerInode* parent_node)
  : TreeMutation(SetParent),
    child_node_ (child_node),
    parent_node_ (parent_node) {
  assert(child_node != NULL && parent_node != NULL);
}

} // namespace cpm

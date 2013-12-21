#include <cassert>

#include "WeinerNode.hpp"

namespace cpm {

WeinerNode::WeinerNode(WeinerInode* const parent,
                       bool text_node,
                       int edge_label_start,
                       int edge_label_length,
                       int path_label_start,
                       int path_label_length)
  : parent_ (parent),
    text_node_ (text_node),
    edge_label_start_ (edge_label_start),
    edge_label_length_ (edge_label_length),
    path_label_start_ (path_label_start),
    path_label_length_ (path_label_length) {
  assert(edge_label_start >= 0 && edge_label_length >= 0);
  assert(path_label_start >= 0 && path_label_length >= 0);
}

WeinerNode::~WeinerNode() {
}

WeinerInode* WeinerNode::getParent() {
  return parent_;
}

void WeinerNode::setParent(WeinerInode* const node) {
  parent_ = node;
}

Label WeinerNode::getEdgeLabel() {
  return Label(edge_label_start_, edge_label_length_, text_node_);
}

int WeinerNode::getEdgeLabelLength() {
  return edge_label_length_;
}

void WeinerNode::setEdgeLabel(Label label) {
  assert(label.text_ == text_node_);
  edge_label_start_ = label.start_;
  edge_label_length_ = label.length_;
}

Label WeinerNode::getPathLabel() {
  return Label(path_label_start_, path_label_length_, text_node_);
}

int WeinerNode::getPathLabelLength() {
  return path_label_length_;
}

bool WeinerNode::isTextNode() {
  return text_node_;
}

bool WeinerNode::isLeaf() {
  assert(false);
  return false;
}

} // namespace cpm

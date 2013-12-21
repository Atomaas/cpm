#ifndef WEINERNODE_HPP_
#define WEINERNODE_HPP_

namespace cpm {

class WeinerInode;

struct Label {
  int start_;
  int length_;
  bool text_;
  Label(int start, int length, bool text)
    : start_ (start),
      length_ (length),
      text_ (text) {
  }
};

class WeinerNode {
public:
  WeinerNode(WeinerInode* const parent,
             bool text_node,
             int edge_label_start,
             int edge_label_length,
             int path_label_start,
             int path_label_length);
  virtual ~WeinerNode();
  WeinerInode* getParent();
  void setParent(WeinerInode* const node);
  Label getEdgeLabel();
  int getEdgeLabelLength();
  void setEdgeLabel(Label label);
  Label getPathLabel();
  int getPathLabelLength();
  bool isTextNode();
  virtual bool isLeaf();
private:
  WeinerInode* parent_;
  bool text_node_;
  // text_node_ == true iff this node corresponds to the text (not just the pattern).
  // In other words, text_node_ iff:
  //   (1) this node was created when the text was inserted into the tree; or
  //   (2) this node is an ancestor of a node that satisfies (1).
  int edge_label_start_; // The characters on this node's in-edge.
  int edge_label_length_;
  int path_label_start_; // The concatenation of all the edge labels on the path from the root to this node.
  int path_label_length_;
};

} // namespace cpm

#endif // WEINERNODE_HPP_

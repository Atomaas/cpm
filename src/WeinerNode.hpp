#ifndef WEINERNODE_HPP_
#define WEINERNODE_HPP_

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
  bool text_node_; // node corresponds to the text (not only the pattern)
  int edge_label_start_;
  int edge_label_length_;
  int path_label_start_; // path from root to this node
  int path_label_length_;
};

#endif // WEINERNODE_HPP_

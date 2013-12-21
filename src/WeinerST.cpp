#include <iostream>
#include <cstdio>
#include <cassert>
#include "WeinerST.hpp"

namespace cpm {

  WeinerST::WeinerST()
    : root_ (NULL),
      prev_leaf_ (NULL),
      text_prev_leaf_ (NULL),
      text_string_ (""),
      pattern_string_ ("") { 
  }

  WeinerST::~WeinerST() {
    if (root_ != NULL) {
      deleteNodes(root_);
    }
  }

  void WeinerST::insertText(std::string &s) {
    assert(text_string_ == "" && text_prev_leaf_ == NULL);
    assert(pattern_string_ == "");
    assert(matches_.empty());
    assert(tree_mutations_.empty());
    //
    text_string_ = s;
    buildBaseTree(s);
    insertString(true);
    text_prev_leaf_ = prev_leaf_;
    //
    assert(text_string_ != "" && text_prev_leaf_ != NULL);
  }

  void WeinerST::insertPattern(std::string &s) {
    assert(text_string_ != "" && text_prev_leaf_ != NULL);
    assert(pattern_string_ == "");
    assert(root_->getNumChildren() > 0);
    assert(prev_leaf_ == text_prev_leaf_);
    assert(matches_.empty());
    assert(s != "");
    assert(tree_mutations_.empty());
    //
    pattern_string_ = s;
    insertString(false);
  }

  void WeinerST::removePattern() {
    assert(text_string_ != "" && text_prev_leaf_ != NULL);
    assert(pattern_string_ != "");
    //
    while (!tree_mutations_.empty()) {
      TreeMutation* mutp = tree_mutations_.top();
      tree_mutations_.pop();
      switch (mutp->mutation_op_) {
      case DeleteNode: {
        WeinerNode* node_to_del = dynamic_cast<DeleteNodeMut*>(mutp)->node_;
        assert(node_to_del != NULL);
        delete node_to_del;
        break;
      }
      case RemoveChild: {
        RemoveCharMut* rcmut = dynamic_cast<RemoveCharMut*>(mutp);
        rcmut->node_->removeChild(rcmut->c_);
        break;
      }
      case RemoveIndicator: {
        RemoveCharMut* rcmut = dynamic_cast<RemoveCharMut*>(mutp);
        rcmut->node_->removeIndicator(rcmut->c_);
        break;
      }
      case RemoveLink: {
        RemoveCharMut* rcmut = dynamic_cast<RemoveCharMut*>(mutp);
        rcmut->node_->removeLink(rcmut->c_);
        break;
      }
      case ReplaceChild: {
        ReplaceChildMut* rcmut = dynamic_cast<ReplaceChildMut*>(mutp);
        assert(rcmut->parent_node_->getChild(rcmut->c_) == rcmut->old_child_node_);
        rcmut->parent_node_->replaceChild(rcmut->c_, rcmut->new_child_node_);
        break;
      }
      case SetEdgeLabel: {
        SetEdgeLabelMut* selmut = dynamic_cast<SetEdgeLabelMut*>(mutp);
        selmut->node_->setEdgeLabel(selmut->label_);
        break;
      }
      case SetParent: {
        SetParentMut* spmut = dynamic_cast<SetParentMut*>(mutp);
        spmut->child_node_->setParent(spmut->parent_node_);
        break;
      }
      }
      delete mutp;
    }
    prev_leaf_ = text_prev_leaf_;
    pattern_string_ = "";
    matches_.clear();
    //
    assert(text_string_ != "" && text_prev_leaf_ != NULL);
    assert(root_->getNumChildren() > 0);
  }

  void WeinerST::insertString(const bool text_node) {
    const int m = (text_node ? text_string_.length() : pattern_string_.length());
    // printTree();
    for (int i = m - (text_node ?  2 : 1); i >= 0; i--) {
      // std::cout << i << std::endl;
      extend(i, text_node);
      // printTree();
    }
  }

  // Based on the description of Weiner's algorithm in Gusfield (1997)
  void WeinerST::extend(int i, const bool text_node) {
    std::string const &s = (text_node ? text_string_ : pattern_string_);
    char c = s[i];
    // Walk up the tree from prev_leaf_ looking for the first node with indicator c.
    WeinerInode* node1 = prev_leaf_->getParent();
    while (node1 != root_ && !node1->checkIndicator(c)) {
      node1->addIndicator(c); // * Tree mutation *
      if (!text_node) {
        tree_mutations_.push(new RemoveCharMut(RemoveIndicator, node1, c));
      }
      node1 = node1->getParent();
    }
    WeinerInode* head_node = NULL; // the node at which head(i) ends
    if (!node1->checkIndicator(c)) {
      // No node with indicator c found (c doesn't occur in s[i + 1..m]).
      // head(i) ends at the root.
      assert(node1 == root_);
      node1->addIndicator(c); // * Tree mutation *
      if (!text_node) {
        tree_mutations_.push(new RemoveCharMut(RemoveIndicator, node1, c));
      }
      head_node = root_;
    }
    else {
      // node1 is the first node on the path up from prev_leaf_ with indicator c.
      // Walk up the tree from node1 looking for the first node with a link for c.
      int path_length = 0; // Number of characters on the path between node1 and node2.
      WeinerInode* node2 = node1;
      WeinerInode* node2_prev = node1;
      while (node2 != root_ && !node2->checkLink(c)) {
        node2_prev = node2;
        path_length += node2->getEdgeLabelLength();
        node2 = node2->getParent();
      }
      if (!node2->checkLink(c)) {
        // No node with link c was found.
        assert(node2 == root_);
        assert(root_->checkChild(c));
        // head(i) ends t characters below the root on the c edge.
        int t = node1->getPathLabelLength() + 1;
        WeinerNode* child_node = root_->getChild(c);;
        Label child_edge_label = child_node->getEdgeLabel();
        assert(1 <= t && t < child_edge_label.length_);
        // head(i) ends in the middle of the edge.
        head_node = breakEdge(child_node, c, t, text_node);
        node1->addLink(c, head_node); // * Tree mutation *
        if (!text_node) {
          tree_mutations_.push(new RemoveCharMut(RemoveLink, node1, c));
        }
      }
      else {
        // node2 is the first node with a link for c on the path up from node1.
        // head(i) = cx, where x is node1's path label.
        // Follow the link from node2 to node3.
        // head(i) ends path_length (possibly 0) characters below node3 on the c2 edge,
        // where c2 is the first of the path_length characters on the path from node2 to node1.
        WeinerInode* node3 = node2->getLink(c);
        if (path_length == 0) {
          head_node = node3;
        }
        else {
          char c2 = getLabelChar(node2_prev->getEdgeLabel(), 0);
          assert(node2->getChild(c2) == node2_prev);
          assert(node3->checkChild(c2));
          WeinerNode* child_node = node3->getChild(c2);
          Label child_edge_label = child_node->getEdgeLabel();
          assert(path_length < child_edge_label.length_);
          // head(i) ends in the middle of the edge
          head_node = breakEdge(child_node, c2, path_length, text_node);
          node1->addLink(c, head_node); // * Tree mutation *
          if (!text_node) {
            tree_mutations_.push(new RemoveCharMut(RemoveLink, node1, c));
          }
        }
      }
    }
    // By this point, head_node has been found.
    // If s represents the pattern and head_node is a text node with
    // path length greater than the length pattern, then record a match.
    if (!text_node && 
        head_node->getPathLabelLength() >= ((signed)pattern_string_.length() - 1) / 2
        && head_node->isTextNode()) {
      matches_.insert(head_node->getPathLabel().start_);
    }
    // Create a new leaf numbered i and a new edge (head_node, i) labeled with tail(i).
    int tail_length = s.length() - i - head_node->getPathLabelLength();
    assert(tail_length > 0);
    int tail_start = s.length() - tail_length;
    assert (i <= tail_start);
    WeinerLeaf* new_leaf = new WeinerLeaf(head_node,
                                          text_node,
                                          tail_start, tail_length,
                                          i, s.length() - i,
                                          i); // * Tree mutation *
    head_node->addChild(s[tail_start], new_leaf); // * Tree mutation *
    if (!text_node) {
      tree_mutations_.push(new DeleteNodeMut(new_leaf));
      tree_mutations_.push(new RemoveCharMut(RemoveChild, head_node, s[tail_start]));
    }
    //
    prev_leaf_ = new_leaf;
  }

  void WeinerST::buildBaseTree(std::string &s) {
    const int m = s.length();
    root_ = new WeinerInode(NULL, true, 0, 0, 0, 0);
    prev_leaf_ = new WeinerLeaf(root_, true, m - 1, 1, m - 1, 1, m - 1);
    char c = s[s.length() - 1];
    root_->addChild(c, prev_leaf_);
    root_->addIndicator(c);
  }

  // Inserts a new node "in the middle of" an existing edge.
  WeinerInode* WeinerST::breakEdge(WeinerNode* const child_node,
                                   char edge_char,
                                   int edge_label_prefix_length,
                                   const bool text_node) {
    assert(edge_char == getLabelChar(child_node->getEdgeLabel(), 0));
    assert(0 < edge_label_prefix_length && edge_label_prefix_length < child_node->getEdgeLabelLength());
    Label child_edge_label = child_node->getEdgeLabel();
    Label child_path_label = child_node->getPathLabel();
    WeinerInode* parent_node = child_node->getParent();
    // * Tree mutation *
    WeinerInode* new_node = new WeinerInode(parent_node,
                                            child_node->isTextNode(),
                                            child_edge_label.start_, edge_label_prefix_length,
                                            child_path_label.start_, child_path_label.length_ - child_edge_label.length_ + edge_label_prefix_length);
    new_node->addChild(getLabelChar(child_edge_label, edge_label_prefix_length), child_node);
    if (!text_node) {
      tree_mutations_.push(new DeleteNodeMut(new_node));
    }
    if (child_node->isLeaf()) {
      int j = dynamic_cast<WeinerLeaf*>(child_node)->getLeafId() - 1;
      char indicator_char = child_node->isTextNode() ? text_string_[j] : pattern_string_[j];
      new_node->addIndicator(indicator_char); // * Tree mutation *
    }
    else {
      // * Tree mutation *
      new_node->setIndicatorVector(dynamic_cast<WeinerInode*>(child_node)->getIndicatorVector());
    }
    // * Tree mutation *
    child_node->setParent(new_node);
    child_node->setEdgeLabel(Label(child_edge_label.start_ + edge_label_prefix_length,
                                   child_edge_label.length_ - edge_label_prefix_length,
                                   child_edge_label.text_));
    parent_node->replaceChild(edge_char, new_node);
    if (!text_node) {
      tree_mutations_.push(new SetParentMut(child_node, parent_node));
      tree_mutations_.push(new SetEdgeLabelMut(child_node, child_edge_label));
      tree_mutations_.push(new ReplaceChildMut(parent_node, edge_char, child_node, new_node));
    }
    return new_node;
  }

  char WeinerST::getLabelChar(Label label, int i) {
    if (label.text_) {
      assert(0 <= label.start_ && label.start_ < (signed)text_string_.length() &&
             label.start_ + label.length_ <= (signed)text_string_.length());
      return text_string_[label.start_ + i];
    }
    else {
      assert(0 <= label.start_ && label.start_ < (signed)pattern_string_.length() &&
             label.start_ + label.length_ <= (signed)pattern_string_.length());
      return pattern_string_[label.start_ + i];
    }
  }

  std::string WeinerST::getLabelString(Label label) {
    if (label.text_) {
      assert(0 <= label.start_ && label.start_ < (signed)text_string_.length() &&
             label.start_ + label.length_ <= (signed)text_string_.length());
      return text_string_.substr(label.start_, label.length_);
    }
    else {
      assert(0 <= label.start_ && label.start_ < (signed)pattern_string_.length() &&
             label.start_ + label.length_ <= (signed)pattern_string_.length());
      return pattern_string_.substr(label.start_, label.length_);
    }
  }

  std::string strpow(std::string s, int e) {
    std::string s_out = "";
    for (int i = 0; i < e; i++) {
      s_out += s;
    }
    return s_out;
  }

  std::set<int> WeinerST::getMatches() {
    return matches_;
  }

  void WeinerST::printMatches() {
    std::cout << "Matches:\n";
    for (std::set<int>::iterator iter = matches_.begin(); iter != matches_.end(); iter++) {
      std::cout << *iter << "\n";
    }
  }

  void WeinerST::printTree() {
    std::cout << strpow("*", 80) + "\n";
    if (root_ == NULL) {
      std::cout << "* Empty tree.\n";
      return;
    }
    WeinerInode* inode = dynamic_cast<WeinerInode*>(root_);
    std::printf(((std::string)"* Root: Inode (" + (inode->isTextNode() ? "T" : "P") + ") (" + getLabelString(inode->getPathLabel())  + ") (Indi: %s) (Link: %s) \n").c_str(), inode->getIndicatorString().c_str(), inode->getLinkString().c_str());
    std::map<char, WeinerNode*> children = inode->getChildren();
    for (std::map<char, WeinerNode*>::iterator iter = children.begin(); iter != children.end(); iter++) {
      printTreeTraverse(iter->second, 2);
    }
    std::cout << "***\n*      prev_leaf_ = " << (void*)prev_leaf_ << "\n";
    std::cout << "* text_pref_leaf_ = " << (void*)text_prev_leaf_ << "\n";
    std::cout << strpow("*", 80) + "\n";
  }

  void WeinerST::printTreeTraverse(WeinerNode* const node, int indent) {
    std::string line_prefix = "* " + strpow(" ", indent) + "- ";
    if (node->isLeaf()) {
      WeinerLeaf* leaf = dynamic_cast<WeinerLeaf*>(node);
      std::printf((line_prefix + getLabelString(leaf->getEdgeLabel()) + " -> Leaf %d (" + (leaf->isTextNode() ? "T" : "P") + ") (" + getLabelString(leaf->getPathLabel())  + ")\n").c_str(), leaf->getLeafId());
    }
    else {
      WeinerInode* inode = dynamic_cast<WeinerInode*>(node);
      std::printf((line_prefix + getLabelString(inode->getEdgeLabel()) + " -> Inode (" + (inode->isTextNode() ? "T" : "P") + ") (" + getLabelString(inode->getPathLabel())  + ") (Indi: %s) (Link: %s) \n").c_str(), inode->getIndicatorString().c_str(), inode->getLinkString().c_str());
      std::map<char, WeinerNode*> children = inode->getChildren();
      for (std::map<char, WeinerNode*>::iterator iter = children.begin(); iter != children.end(); iter++) {
        printTreeTraverse(iter->second, indent + 2);
      }
    }
  }
  
  void WeinerST::deleteNodes(WeinerNode* const node) {
    if (node->isLeaf()) {
      return;
    }
    else {
      WeinerInode* inode = dynamic_cast<WeinerInode*>(node);
      std::map<char, WeinerNode*> children = inode->getChildren();
      for (std::map<char, WeinerNode*>::iterator iter = children.begin(); iter != children.end(); iter++) {
        deleteNodes(iter->second);
        delete iter->second;
        iter->second = NULL;
      }
    }
  }

} // namespace cpm

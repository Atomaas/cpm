#include <cstddef>
#include <cassert>

#include "WeinerLeaf.hpp"

namespace cpm {

WeinerLeaf::WeinerLeaf(WeinerInode* const parent,
                       bool text_node,
                       int edge_label_start,
                       int edge_label_length,
                       int path_label_start,
                       int path_label_length,
                       int leaf_id)
  : WeinerNode(parent,
               text_node,
               edge_label_start,
               edge_label_length,
               path_label_start,
               path_label_length),
    leaf_id_ (leaf_id) {
  assert(parent != NULL);
}

int WeinerLeaf::getLeafId() {
  return leaf_id_;
}

bool WeinerLeaf::isLeaf() {
  return true;
}

} // namespace cpm

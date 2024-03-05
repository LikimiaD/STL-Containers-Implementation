#ifndef SRC_RB_TREE_H
#define SRC_RB_TREE_H

#include <cstddef>
#include <iostream>
#include <stdexcept>

#define RED true
#define BLACK false

template <typename KeyType, typename ValueType>
class RBTree {
 public:
  struct Node {
    KeyType key;
    ValueType value;
    Node* left;
    Node* right;
    Node* parent;
    bool color;

    Node(const KeyType& k, const ValueType& v)
        : key(k),
          value(v),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          color(RED) {}
  };
  RBTree();
  RBTree(const RBTree& other);
  RBTree(RBTree&& other) noexcept;
  ~RBTree();

  RBTree& operator=(const RBTree& other);
  RBTree& operator=(RBTree&& other) noexcept;

  void insert(const KeyType& key, const ValueType& value);
  void remove(const KeyType& key);
  bool contains(const KeyType& key) const;
  void clear();
  int size() const;
  Node* find(const KeyType& key);
  Node* minimum();
  Node* maximum();
  Node* minimum(Node* node);
  Node* maximum(Node* node);
  Node* findNext(Node* node);
  bool isEmpty() const { return root == nullptr; }

 private:
  Node* root;
  int treeSize;

  void rotateLeft(Node*& pt);
  void rotateRight(Node*& pt);
  void fixViolation(Node*& pt);
  void insertBST(Node*& root, Node* pt);
  void removeBST(Node*& root, const KeyType& key);
  void clearNode(Node*& ptr);
  void rbTransplant(Node* u, Node* v);
  void fixRemoveViolation(Node* x, Node* xParent);
  Node* copyNode(const Node* node, Node* parent = nullptr);
};

template <typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::RBTree() : root(nullptr), treeSize(0) {}
template <typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::~RBTree() {
  clear();
}
template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::clear() {
  clearNode(this->root);
  this->root = nullptr;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::clearNode(Node*& ptr) {
  if (ptr != nullptr) {
    clearNode(ptr->left);
    clearNode(ptr->right);
    delete ptr;
    ptr = nullptr;
    this->treeSize -= 1;
  }
}

template <typename KeyType, typename ValueType>
int RBTree<KeyType, ValueType>::size() const {
  return this->treeSize;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::insert(const KeyType& key,
                                        const ValueType& value) {
  Node* newNode = new Node(key, value);
  insertBST(this->root, newNode);
  fixViolation(newNode);
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::insertBST(Node*& root, Node* newNode) {
  if (root == nullptr) {
    root = newNode;
    treeSize++;
    return;
  }

  if (newNode->key < root->key) {
    if (root->left == nullptr) {
      root->left = newNode;
      newNode->parent = root;
      treeSize++;
    } else {
      insertBST(root->left, newNode);
    }
  } else if (newNode->key > root->key) {
    if (root->right == nullptr) {
      root->right = newNode;
      newNode->parent = root;
      treeSize++;
    } else {
      insertBST(root->right, newNode);
    }
  }
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::rotateLeft(Node*& pt) {
  Node* pt_right = pt->right;
  pt->right = pt_right->left;

  if (pt->right != nullptr) {
    pt->right->parent = pt;
  }

  pt_right->parent = pt->parent;

  if (pt->parent == nullptr) {
    root = pt_right;
  } else if (pt == pt->parent->left) {
    pt->parent->left = pt_right;
  } else {
    pt->parent->right = pt_right;
  }

  pt_right->left = pt;
  pt->parent = pt_right;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::rotateRight(Node*& pt) {
  Node* pt_left = pt->left;
  pt->left = pt_left->right;

  if (pt->left != nullptr) {
    pt->left->parent = pt;
  }

  pt_left->parent = pt->parent;

  if (pt->parent == nullptr) {
    root = pt_left;
  } else if (pt == pt->parent->right) {
    pt->parent->right = pt_left;
  } else {
    pt->parent->left = pt_left;
  }

  pt_left->right = pt;
  pt->parent = pt_left;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fixViolation(Node*& newNode) {
  Node* parent = nullptr;
  Node* grandParent = nullptr;
  while ((newNode != root) && (newNode->color != BLACK) &&
         (newNode->parent->color == RED)) {
    parent = newNode->parent;
    grandParent = newNode->parent->parent;
    if (parent == grandParent->left) {
      Node* uncle = grandParent->right;
      if (uncle != nullptr && uncle->color == RED) {
        grandParent->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        newNode = grandParent;
      } else {
        if (newNode == parent->right) {
          rotateLeft(parent);
          newNode = parent;
          parent = newNode->parent;
        }
        rotateRight(grandParent);
        std::swap(parent->color, grandParent->color);
        newNode = parent;
      }
    } else {
      Node* uncle = grandParent->left;
      if (uncle != nullptr && uncle->color == RED) {
        grandParent->color = RED;
        parent->color = BLACK;
        uncle->color = BLACK;
        newNode = grandParent;
      } else {
        if (newNode == parent->left) {
          rotateRight(parent);
          newNode = parent;
          parent = newNode->parent;
        }
        rotateLeft(grandParent);
        std::swap(parent->color, grandParent->color);
        newNode = parent;
      }
    }
  }
  root->color = BLACK;
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::find(
    const KeyType& key) {
  Node* current = root;
  while (current != nullptr) {
    if (key == current->key) {
      return current;
    } else if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return nullptr;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::remove(const KeyType& key) {
  Node* nodeToDelete = root;
  Node* parent = nullptr;
  Node* child = nullptr;
  bool found = false;

  while (nodeToDelete != nullptr) {
    if (key == nodeToDelete->key) {
      found = true;
      break;
    }
    parent = nodeToDelete;
    nodeToDelete =
        key < nodeToDelete->key ? nodeToDelete->left : nodeToDelete->right;
  }

  if (!found) {
    throw std::invalid_argument("Key not found.");
  }

  bool originalColor = nodeToDelete->color;
  if (nodeToDelete->left == nullptr) {
    child = nodeToDelete->right;
    rbTransplant(nodeToDelete, nodeToDelete->right);
  } else if (nodeToDelete->right == nullptr) {
    child = nodeToDelete->left;
    rbTransplant(nodeToDelete, nodeToDelete->left);
  } else {
    Node* successor = minimum(nodeToDelete->right);
    originalColor = successor->color;
    child = successor->right;
    if (successor->parent == nodeToDelete) {
      if (child) child->parent = successor;
    } else {
      rbTransplant(successor, successor->right);
      successor->right = nodeToDelete->right;
      successor->right->parent = successor;
    }
    rbTransplant(nodeToDelete, successor);
    successor->left = nodeToDelete->left;
    successor->left->parent = successor;
    successor->color = nodeToDelete->color;
  }

  delete nodeToDelete;
  if (originalColor == BLACK) {
    fixRemoveViolation(child, parent);
  }
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::rbTransplant(Node* u, Node* v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v != nullptr) {
    v->parent = u->parent;
  }
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::minimum(
    Node* node) {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node*
RBTree<KeyType, ValueType>::minimum() {
  return minimum(this->root);
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::maximum(
    Node* node) {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node*
RBTree<KeyType, ValueType>::maximum() {
  return maximum(this->root);
}

template <typename KeyType, typename ValueType>
bool RBTree<KeyType, ValueType>::contains(const KeyType& key) const {
  Node* current = root;
  while (current != nullptr) {
    if (key == current->key) {
      return true;
    } else if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return false;
}

template <typename KeyType, typename ValueType>
void RBTree<KeyType, ValueType>::fixRemoveViolation(Node* x, Node* xParent) {
  Node* sibling;
  while (x != root && (x == nullptr || x->color == BLACK)) {
    if (x == xParent->left) {
      sibling = xParent->right;
      if (sibling->color == RED) {
        sibling->color = BLACK;
        xParent->color = RED;
        rotateLeft(xParent);
        sibling = xParent->right;
      }
      if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
          (sibling->right == nullptr || sibling->right->color == BLACK)) {
        sibling->color = RED;
        x = xParent;
        xParent = xParent->parent;
      } else {
        if (sibling->right == nullptr || sibling->right->color == BLACK) {
          if (sibling->left != nullptr) {
            sibling->left->color = BLACK;
          }
          sibling->color = RED;
          rotateRight(sibling);
          sibling = xParent->right;
        }
        sibling->color = xParent->color;
        xParent->color = BLACK;
        if (sibling->right != nullptr) {
          sibling->right->color = BLACK;
        }
        rotateLeft(xParent);
        x = root;
      }
    } else {
      sibling = xParent->left;
      if (sibling->color == RED) {
        sibling->color = BLACK;
        xParent->color = RED;
        rotateRight(xParent);
        sibling = xParent->left;
      }
      if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
          (sibling->left == nullptr || sibling->left->color == BLACK)) {
        sibling->color = RED;
        x = xParent;
        xParent = xParent->parent;
      } else {
        if (sibling->left == nullptr || sibling->left->color == BLACK) {
          if (sibling->right != nullptr) {
            sibling->right->color = BLACK;
          }
          sibling->color = RED;
          rotateLeft(sibling);
          sibling = xParent->left;
        }
        sibling->color = xParent->color;
        xParent->color = BLACK;
        if (sibling->left != nullptr) {
          sibling->left->color = BLACK;
        }
        rotateRight(xParent);
        x = root;
      }
    }
  }
  if (x != nullptr) x->color = BLACK;
}
template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* copyNode(
    const typename RBTree<KeyType, ValueType>::Node* node,
    typename RBTree<KeyType, ValueType>::Node* parent = nullptr) {
  if (node == nullptr) return nullptr;

  typename RBTree<KeyType, ValueType>::Node* newNode =
      new typename RBTree<KeyType, ValueType>::Node(node->key, node->value);
  newNode->color = node->color;
  newNode->parent = parent;

  newNode->left = copyNode<KeyType, ValueType>(node->left, newNode);
  newNode->right = copyNode<KeyType, ValueType>(node->right, newNode);

  return newNode;
}
template <typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>& RBTree<KeyType, ValueType>::operator=(
    const RBTree<KeyType, ValueType>& other) {
  if (this != &other) {
    clear();
    root = copyNode(other.root);
    treeSize = other.treeSize;
  }
  return *this;
}
template <typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>& RBTree<KeyType, ValueType>::operator=(
    RBTree<KeyType, ValueType>&& other) noexcept {
  if (this != &other) {
    clear();
    root = other.root;
    treeSize = other.treeSize;
    other.root = nullptr;
    other.treeSize = 0;
  }
  return *this;
}
template <typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::RBTree(const RBTree& other)
    : root(copyNode(other.root)), treeSize(other.treeSize) {}
template <typename KeyType, typename ValueType>
RBTree<KeyType, ValueType>::RBTree(RBTree&& other) noexcept
    : root(other.root), treeSize(other.treeSize) {
  other.root = nullptr;
  other.treeSize = 0;
}
template <typename KeyType, typename ValueType>
typename RBTree<KeyType, ValueType>::Node* RBTree<KeyType, ValueType>::findNext(
    Node* node) {
  if (node == nullptr) return nullptr;
  if (node->right != nullptr) {
    Node* current = node->right;
    while (current->left != nullptr) {
      current = current->left;
    }
    return current;
  }
  Node* parent = node->parent;
  while (parent != nullptr && node == parent->right) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}

#endif  // SRC_RB_TREE_H

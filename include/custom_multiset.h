#ifndef SRC_INCLUDE_CUSTOM_MULTISET_H_
#define SRC_INCLUDE_CUSTOM_MULTISET_H_

#include <initializer_list>
#include <iterator>
#include <utility>

#include "custom_vector.h"
#include "rb_tree.h"

template <typename Key>
class MultiSet {
 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;
  class MultiSetIterator {
   public:
    using Node = typename RBTree<Key, Key>::Node;
    using Iter = MultiSetIterator;

    MultiSetIterator() : nodePtr(nullptr) {}
    explicit MultiSetIterator(Node* node) : nodePtr(node) {}

    Key& operator*() const {
      if (!nodePtr) {
        throw std::runtime_error("Iterator does not point to a valid node");
      }
      return nodePtr->key;
    }

    Key* operator->() const {
      if (!nodePtr) {
        throw std::runtime_error("Iterator does not point to a valid node");
      }
      return &(nodePtr->key);
    }

    Iter& operator++() {
      if (nodePtr->right != nullptr) {
        nodePtr = nodePtr->right;
        while (nodePtr->left != nullptr) {
          nodePtr = nodePtr->left;
        }
      } else {
        Node* parent = nodePtr->parent;
        while (parent != nullptr && nodePtr == parent->right) {
          nodePtr = parent;
          parent = parent->parent;
        }
        nodePtr = parent;
      }
      return *this;
    }

    Iter operator++(int) {
      Iter temp = *this;
      ++(*this);
      return temp;
    }

    Iter& operator--() {
      if (nodePtr->left != nullptr) {
        nodePtr = nodePtr->left;
        while (nodePtr->right != nullptr) {
          nodePtr = nodePtr->right;
        }
      } else {
        Node* parent = nodePtr->parent;
        while (parent != nullptr && nodePtr == parent->left) {
          nodePtr = parent;
          parent = parent->parent;
        }
        nodePtr = parent;
      }
      return *this;
    }

    Iter operator--(int) {
      Iter temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const Iter& other) const {
      return nodePtr == other.nodePtr;
    }
    bool operator!=(const Iter& other) const {
      return nodePtr != other.nodePtr;
    }
    Node* getNodePtr() const { return nodePtr; }

   private:
    Node* nodePtr;
  };
  using iterator = MultiSetIterator;
  MultiSet();
  explicit MultiSet(std::initializer_list<value_type> const& items);
  MultiSet(const MultiSet& ms);
  MultiSet(MultiSet&& ms) noexcept;
  ~MultiSet();

  MultiSet& operator=(const MultiSet& ms);
  MultiSet& operator=(MultiSet&& ms) noexcept;

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(MultiSet& other);
  void merge(MultiSet& other);
  template <typename... Args>
  CustomVector<std::pair<iterator, bool>> insert_many(Args&&... args);

  size_type count(const key_type& key);
  iterator find(const key_type& key);
  bool contains(const key_type& key);
  std::pair<iterator, iterator> equal_range(const key_type& key);
  iterator lower_bound(const key_type& key);
  iterator upper_bound(const key_type& key);

 private:
  RBTree<key_type, value_type> tree;
};

template <typename Key>
MultiSet<Key>::MultiSet() : tree() {}
template <typename Key>
MultiSet<Key>::MultiSet(std::initializer_list<value_type> const& items)
    : tree() {
  for (const auto& item : items) {
    tree.insert(item, item);
  }
}
template <typename Key>
MultiSet<Key>::MultiSet(const MultiSet& ms) : tree(ms.tree) {}
template <typename Key>
MultiSet<Key>::MultiSet(MultiSet&& ms) noexcept : tree(std::move(ms.tree)) {}
template <typename Key>
MultiSet<Key>::~MultiSet() {}
template <typename Key>
MultiSet<Key>& MultiSet<Key>::operator=(const MultiSet<Key>& ms) {
  if (this != &ms) {
    tree = ms.tree;
  }
  return *this;
}
template <typename Key>
MultiSet<Key>& MultiSet<Key>::operator=(MultiSet<Key>&& ms) noexcept {
  if (this != &ms) {
    tree = std::move(ms.tree);
  }
  return *this;
}
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::begin() {
  auto node = tree.minimum();
  return iterator(node);
}
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::end() {
  return iterator(nullptr);
}
template <typename Key>
bool MultiSet<Key>::empty() const {
  return tree.size() == 0;
}
template <typename Key>
typename MultiSet<Key>::size_type MultiSet<Key>::size() const {
  return tree.size();
}
template <typename Key>
typename MultiSet<Key>::size_type MultiSet<Key>::max_size() const {
  return std::numeric_limits<size_type>::max();
}
template <typename Key>
void MultiSet<Key>::clear() {
  tree.clear();
}
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::insert(
    const value_type& value) {
  tree.insert(value, value);
  auto node = tree.find(value);
  return iterator(node);
}
template <typename Key>
void MultiSet<Key>::erase(iterator pos) {
  if (pos.getNodePtr()) {
    tree.remove(pos.getNodePtr()->key);
  }
}
template <typename Key>
void MultiSet<Key>::swap(MultiSet& other) {
  std::swap(tree, other.tree);
}
template <typename Key>
void MultiSet<Key>::merge(MultiSet& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}
template <typename Key>
template <typename... Args>
CustomVector<std::pair<typename MultiSet<Key>::iterator, bool>>
MultiSet<Key>::insert_many(Args&&... args) {
  CustomVector<std::pair<iterator, bool>> result;
  (void)std::initializer_list<int>{
      (result.push_back(insert(std::forward<Args>(args))), 0)...};
  return result;
}
template <typename Key>
typename MultiSet<Key>::size_type MultiSet<Key>::count(const key_type& key) {
  typename RBTree<Key, Key>::Node* found = tree.find(key);
  size_type cnt = 0;
  while (found != nullptr && found->key == key) {
    ++cnt;
    found = tree.findNext(found);
  }
  return cnt;
}
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::find(const key_type& key) {
  typename RBTree<Key, Key>::Node* found = tree.find(key);
  return iterator(found);
}
template <typename Key>
bool MultiSet<Key>::contains(const key_type& key) {
  return tree.find(key) != nullptr;
}
template <typename Key>
std::pair<typename MultiSet<Key>::iterator, typename MultiSet<Key>::iterator>
MultiSet<Key>::equal_range(const key_type& key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::lower_bound(
    const key_type& key) {
  typename RBTree<Key, Key>::Node* current = tree.minimum();
  while (current != nullptr && current->key < key) {
    current = tree.findNext(current);
  }
  return iterator(current);
}
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::upper_bound(
    const key_type& key) {
  typename RBTree<Key, Key>::Node* current = tree.minimum();
  while (current != nullptr && current->key <= key) {
    current = tree.findNext(current);
  }
  return iterator(current);
}

#endif /* SRC_INCLUDE_CUSTOM_MULTISET_H_ */

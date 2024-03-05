#ifndef SRC_INCLUDE_CUSTOM_MAP_H_
#define SRC_INCLUDE_CUSTOM_MAP_H_

#include <cstddef>
#include <initializer_list>
#include <utility>

#include "custom_vector.h"
#include "rb_tree.h"

template <typename Key, typename T>
class MapIterator {
 public:
  using Node = typename RBTree<Key, std::pair<const Key, T>>::Node;
  using MapIter = MapIterator;

  MapIterator();
  explicit MapIterator(Node* node);

  Key getKey() const;

  std::pair<const Key, T>& operator*() const;
  std::pair<const Key, T>* operator->() const;
  MapIterator& operator++();
  MapIterator operator++(int);
  MapIterator& operator--();
  MapIterator operator--(int);
  bool operator==(const MapIter& other) const;
  bool operator!=(const MapIter& other) const;

 private:
  Node* nodePtr;
};

template <typename Key, typename Value>
class Map {
 public:
  using key_type = Key;
  using iterator = MapIterator<Key, Value>;
  using mapped_type = Value;
  using value_type = std::pair<const Key, Value>;
  using map = Map;
  using size_type = std::size_t;

  explicit Map();
  explicit Map(std::initializer_list<value_type> const& items);
  explicit Map(const map& m);
  explicit Map(map&& m);
  ~Map();

  Map& operator=(map&& m);

  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& value);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& value);
  void erase(iterator pos);
  Value& operator[](const key_type& key);
  Value& at(const key_type& key);
  iterator begin();
  iterator end();
  size_type size() const;
  size_type max_size() const;
  bool empty() const;
  void clear();
  bool contains(const key_type& key) const;

  void swap(map& other);
  void merge(map& other);
  template <typename... Args>
  CustomVector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  RBTree<key_type, value_type> tree;
  int elementsCount;
};

template <typename Key, typename T>
MapIterator<Key, T>::MapIterator() : nodePtr(nullptr) {}
template <typename Key, typename T>
MapIterator<Key, T>::MapIterator(Node* node) : nodePtr(node) {}
template <typename Key, typename T>
std::pair<const Key, T>& MapIterator<Key, T>::operator*() const {
  return nodePtr->value;
}
template <typename Key, typename T>
std::pair<const Key, T>* MapIterator<Key, T>::operator->() const {
  return &(nodePtr->value);
}
template <typename Key, typename T>
MapIterator<Key, T>& MapIterator<Key, T>::operator++() {
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
template <typename Key, typename T>
MapIterator<Key, T> MapIterator<Key, T>::operator++(int) {
  MapIter temp = *this;
  ++(*this);
  return temp;
}
template <typename Key, typename T>
MapIterator<Key, T>& MapIterator<Key, T>::operator--() {
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
template <typename Key, typename T>
MapIterator<Key, T> MapIterator<Key, T>::operator--(int) {
  MapIter temp = *this;
  --(*this);
  return temp;
}
template <typename Key, typename T>
bool MapIterator<Key, T>::operator==(const MapIter& other) const {
  return nodePtr == other.nodePtr;
}
template <typename Key, typename T>
bool MapIterator<Key, T>::operator!=(const MapIter& other) const {
  return nodePtr != other.nodePtr;
}
template <typename Key, typename T>
Key MapIterator<Key, T>::getKey() const {
  if (nodePtr == nullptr) {
    throw std::runtime_error("Iterator does not point to a valid node");
  }
  return nodePtr->key;
}

template <typename Key, typename Value>
Map<Key, Value>::Map() : tree(), elementsCount(0) {}
template <typename Key, typename Value>
Map<Key, Value>::Map(const map& m)
    : tree(m.tree), elementsCount(m.elementsCount) {}
template <typename Key, typename Value>
Map<Key, Value>::Map(map&& m)
    : tree(std::move(m.tree)), elementsCount(m.elementsCount) {
  m.elementsCount = 0;
}
template <typename Key, typename Value>
void Map<Key, Value>::clear() {
  tree.clear();
  elementsCount = 0;
}
template <typename Key, typename Value>
Map<Key, Value>::Map(std::initializer_list<value_type> const& items) : Map() {
  for (const auto& item : items) {
    insert(item.first, item.second);
  }
}
template <typename Key, typename Value>
Map<Key, Value>::~Map() {
  clear();
}
template <typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(map&& m) {
  if (this != &m) {
    clear();
    tree = std::move(m.tree);
    elementsCount = m.elementsCount;
    m.elementsCount = 0;
  }
  return *this;
}
template <typename Key, typename Value>
std::pair<typename Map<Key, Value>::iterator, bool> Map<Key, Value>::insert(
    const Key& key, const Value& value) {
  auto node = tree.find(key);
  if (node != nullptr) {
    return std::make_pair(iterator(node), false);
  } else {
    tree.insert(key, std::make_pair(key, value));
    ++elementsCount;
    node = tree.find(key);
    return std::make_pair(iterator(node), true);
  }
}
template <typename Key, typename Value>
std::pair<typename Map<Key, Value>::iterator, bool>
Map<Key, Value>::insert_or_assign(const key_type& key,
                                  const mapped_type& value) {
  auto node = tree.find(key);
  if (node != nullptr) {
    node->value.second = value;
    return std::make_pair(iterator(node), false);
  } else {
    tree.insert(key, std::make_pair(key, value));
    ++elementsCount;
    node = tree.find(key);
    return std::make_pair(iterator(node), true);
  }
}
template <typename Key, typename Value>
typename Map<Key, Value>::iterator Map<Key, Value>::begin() {
  return iterator(tree.minimum());
}
template <typename Key, typename Value>
typename Map<Key, Value>::iterator Map<Key, Value>::end() {
  return iterator(nullptr);
}
template <typename Key, typename Value>
void Map<Key, Value>::erase(iterator pos) {
  Key key = pos.getKey();
  tree.remove(key);
  --elementsCount;
}
template <typename Key, typename Value>
Value& Map<Key, Value>::operator[](const key_type& key) {
  auto* node = tree.find(key);
  if (node == nullptr) {
    insert(key, Value{});
    node = tree.find(key);
  }
  return node->value.second;
}
template <typename Key, typename Value>
Value& Map<Key, Value>::at(const key_type& key) {
  auto* node = tree.find(key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return node->value.second;
}
template <typename Key, typename Value>
std::size_t Map<Key, Value>::size() const {
  return elementsCount;
}
template <typename Key, typename Value>
bool Map<Key, Value>::empty() const {
  return elementsCount == 0;
}
template <typename Key, typename Value>
bool Map<Key, Value>::contains(const key_type& key) const {
  return tree.contains(key);
}
template <typename Key, typename Value>
typename Map<Key, Value>::size_type Map<Key, Value>::max_size() const {
  return std::numeric_limits<size_type>::max();
}
template <typename Key, typename Value>
void Map<Key, Value>::swap(map& other) {
  std::swap(tree, other.tree);
  std::swap(elementsCount, other.elementsCount);
}
template <typename Key, typename Value>
void Map<Key, Value>::merge(map& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert_or_assign(it->first, it->second);
  }
}
template <typename Key, typename Value>
template <typename... Args>
CustomVector<std::pair<typename Map<Key, Value>::iterator, bool>>
Map<Key, Value>::insert_many(Args&&... args) {
  CustomVector<std::pair<iterator, bool>> results;
  (void)std::initializer_list<int>{
      (results.push_back(insert(std::forward<Args>(args))), 0)...};
  return results;
}
template <typename Key, typename Value>
std::pair<typename Map<Key, Value>::iterator, bool> Map<Key, Value>::insert(
    const value_type& value) {
  auto node = tree.find(value.first);
  if (node != nullptr) {
    return std::make_pair(iterator(node), false);
  } else {
    tree.insert(value.first, value);
    ++elementsCount;
    node = tree.find(value.first);
    return std::make_pair(iterator(node), true);
  }
}

#endif /* SRC_INCLUDE_CUSTOM_MAP_H_ */

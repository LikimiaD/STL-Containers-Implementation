#ifndef INCLUDE_CUSTOM_LIST_H_
#define INCLUDE_CUSTOM_LIST_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

template <class T>
class CustomList {
 public:
  struct Node {
    T data;
    Node* prev = nullptr;
    Node* next = nullptr;
    explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : data(data), prev(prev), next(next) {}
  };

  class CustomListIterator {
   public:
    using value_type = T;
    using pointer = Node*;
    using reference = Node&;

    explicit CustomListIterator(pointer ptr = nullptr) : nodePtr(ptr) {}

    T& operator*() const { return nodePtr->data; }
    T* operator->() const { return &(nodePtr->data); }

    CustomListIterator& operator++() {
      if (nodePtr) nodePtr = nodePtr->next;
      return *this;
    }
    CustomListIterator operator++(int) {
      CustomListIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    CustomListIterator& operator--() {
      if (nodePtr) nodePtr = nodePtr->prev;
      return *this;
    }
    CustomListIterator operator--(int) {
      CustomListIterator tmp = *this;
      --(*this);
      return tmp;
    }
    bool operator==(const CustomListIterator& other) const {
      return nodePtr == other.nodePtr;
    }
    bool operator!=(const CustomListIterator& other) const {
      return nodePtr != other.nodePtr;
    }
    Node* getNodePtr() const { return nodePtr; }

   private:
    pointer nodePtr;
  };

  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using const_reference = T const&;
  using size_type = std::size_t;
  using iterator = CustomListIterator;

  CustomList();
  explicit CustomList(size_type n);
  explicit CustomList(std::initializer_list<T> const& list);
  explicit CustomList(const CustomList<T>& other);
  explicit CustomList(CustomList<T>&& other);
  ~CustomList();

  CustomList& operator=(const CustomList<T>& other);
  CustomList& operator=(CustomList<T>&& other);

  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();
  iterator rbegin();
  iterator rend();

  const iterator cbegin() const;
  const iterator cend() const;
  const iterator crbegin() const;
  const iterator crend() const;

  size_type size() const;
  bool empty() const;
  void resize(size_type newSize);
  void resize(size_type newSize, const_reference value);
  void sort();
  size_type max_size() const;
  void unique(bool (**func)(const_reference value));
  void clear();

  void insert(size_type index, const T& value);
  void insert(size_type index, size_type range, reference value);
  void insert(size_type posIndex, std::initializer_list<T> initList);
  iterator insert(iterator pos, const_reference value);
  void erase(size_type index);
  void erase(iterator pos);
  void remove(const_reference value);
  void reverse();
  void assign(size_type index, const_reference value);
  void assign(std::initializer_list<T> initList);
  void assign(size_type index, size_type range, const_reference value);
  void unique();
  void unique(bool (*func)(const_reference, const_reference));
  template <typename... Args>
  void emplace(size_type index, Args&&... args);
  template <typename... Args>
  void emplace_front(Args&&... args);
  template <typename... Args>
  void emplace_back(Args&&... args);

  void push_front(const_reference value);
  void push_back(const_reference value);
  void pop_front();
  void pop_back();

  void swap(CustomList<T>& other);
  void splice(CustomList<T> const& other);
  void splice(iterator pos, CustomList<T> const& other);
  void merge(CustomList<T> const& other);

  template <typename... Args>
  void emplace(size_type index, Args... args);
  template <typename... Args>
  void emplace_front(Args... args);
  template <typename... Args>
  void emplace_back(Args... args);

 private:
  Node* head = nullptr;
  Node* tail = nullptr;
  std::size_t size_ = 0;

  int find_position(const iterator& it) const;
  void localSwap(Node* ptr1, Node* ptr2);
};

template <typename T>
CustomList<T>::CustomList() : head(nullptr), tail(nullptr), size_(0) {}
template <typename T>
CustomList<T>::CustomList(size_type n)
    : head(nullptr), tail(nullptr), size_(0) {
  for (std::size_t i = 0; i < n; i++) {
    push_back(T());
  }
}
template <typename T>
CustomList<T>::CustomList(std::initializer_list<T> const& initList) {
  head = nullptr;
  tail = nullptr;
  size_ = 0;
  for (const T& value : initList) {
    push_back(value);
  }
}
template <typename T>
CustomList<T>::CustomList(const CustomList<T>& other)
    : head(nullptr), tail(nullptr), size_(0) {
  Node* current = other.head;
  while (current != nullptr) {
    push_back(current->data);
    current = current->next;
  }
}
template <typename T>
CustomList<T>::CustomList(CustomList<T>&& other)
    : head(other.head), tail(other.tail), size_(other.size_) {
  other.head = nullptr;
  other.tail = nullptr;
  other.size_ = 0;
}
template <typename T>
CustomList<T>::~CustomList() {
  clear();
}
template <typename T>
CustomList<T>& CustomList<T>::operator=(const CustomList<T>& other) {
  if (this != &other) {
    clear();

    Node* current = other.head;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
    size_ = other.size_;
  }
  return *this;
}
template <typename T>
CustomList<T>& CustomList<T>::operator=(CustomList<T>&& other) {
  if (this != &other) {
    clear();

    head = other.head;
    tail = other.tail;
    size_ = other.size_;

    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
  }
  return *this;
}
template <typename T>
void CustomList<T>::push_back(const T& value) {
  Node* node = new Node(value);
  if (tail == nullptr) {
    head = tail = node;
  } else {
    tail->next = node;
    node->prev = tail;
    tail = node;
  }
  size_++;
}
template <typename T>
void CustomList<T>::clear() {
  Node* current = head;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head = tail = nullptr;
  size_ = 0;
}
template <typename T>
const T& CustomList<T>::front() {
  return head->data;
}
template <typename T>
const T& CustomList<T>::back() {
  return tail->data;
}
template <typename T>
typename CustomList<T>::iterator CustomList<T>::begin() {
  return iterator(head);
}
template <typename T>
typename CustomList<T>::iterator CustomList<T>::end() {
  return iterator(tail);
}
template <typename T>
const typename CustomList<T>::iterator CustomList<T>::cbegin() const {
  return iterator(head);
}
template <typename T>
const typename CustomList<T>::iterator CustomList<T>::cend() const {
  return iterator(nullptr);
}
template <typename T>
typename CustomList<T>::iterator CustomList<T>::rbegin() {
  return iterator(tail);
}
template <typename T>
typename CustomList<T>::iterator CustomList<T>::rend() {
  return iterator(nullptr);
}
template <typename T>
const typename CustomList<T>::iterator CustomList<T>::crbegin() const {
  return iterator(tail);
}
template <typename T>
const typename CustomList<T>::iterator CustomList<T>::crend() const {
  return iterator(nullptr);
}
template <typename T>
std::size_t CustomList<T>::size() const {
  return size_;
}
template <typename T>
bool CustomList<T>::empty() const {
  return head == nullptr;
}
template <typename T>
void CustomList<T>::pop_back() {
  if (size_ == 0) return;

  Node* ptr = tail;
  if (size_ == 1) {
    head = tail = nullptr;
  } else {
    tail = tail->prev;
    tail->next = nullptr;
  }
  delete ptr;
  size_--;
}
template <typename T>
void CustomList<T>::resize(std::size_t newSize) {
  while (size_ < newSize) {
    push_back(T());
  }
  while (size_ > newSize) {
    pop_back();
  }
}
template <typename T>
void CustomList<T>::resize(std::size_t newSize, const T& value) {
  while (size_ < newSize) {
    push_back(value);
  }
  while (size_ > newSize) {
    pop_back();
  }
}
template <typename T>
std::size_t CustomList<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(T);
}
template <typename T>
void CustomList<T>::push_front(const T& value) {
  Node* newHead = new Node(value);
  if (head != nullptr) {
    head->prev = newHead;
    newHead->next = head;
  } else {
    tail = newHead;
  }
  head = newHead;
  ++size_;
}
template <typename T>
void CustomList<T>::pop_front() {
  if (head == nullptr) return;

  Node* ptr = head;
  if (head == tail) {
    head = tail = nullptr;
  } else {
    head = ptr->next;
    head->prev = nullptr;
  }
  delete ptr;
  --size_;
}
template <typename T>
void CustomList<T>::remove(const T& value) {
  Node* ptr = head;
  while (ptr != nullptr) {
    if (ptr->data == value) {
      Node* toDelete = ptr;
      if (ptr == head) {
        pop_front();
        ptr = head;
      } else if (ptr == tail) {
        pop_back();
        break;
      } else {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        ptr = ptr->next;
        delete toDelete;
        --size_;
      }
    } else {
      ptr = ptr->next;
    }
  }
}
template <typename T>
void CustomList<T>::localSwap(Node* ptr1, Node* ptr2) {
  T tmp = ptr1->data;
  ptr1->data = ptr2->data;
  ptr2->data = tmp;
}
template <typename T>
void CustomList<T>::sort() {
  if (size_ > 1) {
    for (std::size_t i = 0; i < size_; i++) {
      Node* ptr = head;
      for (std::size_t j = 0; j < size_ - i; j++) {
        if (ptr->next != nullptr && ptr->next->data < ptr->data) {
          localSwap(ptr->next, ptr);
        }
        ptr = ptr->next;
      }
    }
  }
}
template <typename T>
void CustomList<T>::reverse() {
  if (size_ > 1) {
    Node* ptr1 = head;
    Node* ptr2 = tail;
    for (std::size_t i = 0; i < size_ % 2 + size_ / 2; i++) {
      localSwap(ptr1, ptr2);
      ptr1 = ptr1->next;
      ptr2 = ptr2->prev;
    }
  }
}
template <typename T>
void CustomList<T>::insert(std::size_t index, T const& value) {
  if (index > size_) throw std::out_of_range("Index out of range.");
  Node* newNode = new Node(value);
  if (index == 0) {
    newNode->next = head;
    if (head != nullptr) head->prev = newNode;
    head = newNode;
    if (size_ == 0) tail = newNode;
  } else {
    Node* ptr = head;
    for (std::size_t i = 0; i < index - 1; i++) {
      ptr = ptr->next;
    }
    newNode->next = ptr->next;
    newNode->prev = ptr;
    if (ptr->next != nullptr) ptr->next->prev = newNode;
    ptr->next = newNode;
    if (index == size_) tail = newNode;
  }
  size_++;
}

template <typename T>
void CustomList<T>::insert(std::size_t index, std::size_t range, T& value) {
  for (std::size_t i = 0; i < range; i++) {
    insert(index + i, value);
  }
}
template <typename T>
void CustomList<T>::insert(std::size_t posIndex,
                           std::initializer_list<T> initList) {
  insert(posIndex, initList.begin(), initList.end());
}
template <typename T>
typename CustomList<T>::iterator CustomList<T>::insert(iterator pos,
                                                       const_reference value) {
  if (pos.ptr_ == head) {
    Node* newNode = new Node(value, nullptr, head);
    if (head != nullptr) {
      head->prev = newNode;
    }
    head = newNode;
    if (tail == nullptr) {
      tail = newNode;
    }
  } else {
    Node* current = head;
    while (current != nullptr && current->next != pos.ptr_) {
      current = current->next;
    }
    if (current != nullptr) {
      Node* newNode = new Node(value, current, current->next);
      if (current->next != nullptr) {
        current->next->prev = newNode;
      }
      current->next = newNode;
      if (newNode->next == nullptr) {
        tail = newNode;
      }
    }
  }
  size_++;
  return iterator(pos.ptr_);
}
template <typename T>
void CustomList<T>::erase(iterator pos) {
  Node* posNode = pos.getNodePtr();
  if (posNode == nullptr) return;
  if (posNode == head) {
    pop_front();
  } else if (posNode == tail) {
    pop_back();
  } else {
    posNode->prev->next = posNode->next;
    if (posNode->next != nullptr) {
      posNode->next->prev = posNode->prev;
    }
    delete posNode;
    size_--;
  }
}
template <typename T>
void CustomList<T>::erase(std::size_t index) {
  if (index >= size_) throw std::out_of_range("Index out of range.");
  if (index == 0) {
    Node* ptr = head;
    head = head->next;
    if (head != nullptr) {
      head->prev = nullptr;
    } else {
      tail = nullptr;
    }
    delete ptr;
  } else {
    Node* ptr = head;
    for (std::size_t i = 0; i < index; i++) {
      ptr = ptr->next;
    }
    if (ptr->next != nullptr) {
      ptr->next->prev = ptr->prev;
    } else {
      tail = ptr->prev;
    }
    if (ptr->prev != nullptr) {
      ptr->prev->next = ptr->next;
    }
    delete ptr;
  }
  size_--;
}
template <typename T>
void CustomList<T>::assign(std::size_t index, const T& value) {
  if (index >= size_) throw std::out_of_range("Index out of range.");
  if (index == 0) {
    head->data = value;
  } else {
    Node* ptr = head;
    for (std::size_t i = 0; i < index; i++) {
      ptr = ptr->next;
    }
    ptr->data = value;
  }
}
template <typename T>
void CustomList<T>::assign(std::initializer_list<T> initList) {
  if (initList.size() > size_) {
    clear();
    for (const auto& value : initList) {
      push_back(value);
    }
  } else {
    Node* ptr = head;
    for (const auto& value : initList) {
      if (ptr != nullptr) {
        ptr->data = value;
        ptr = ptr->next;
      }
    }
  }
}
template <typename T>
void CustomList<T>::assign(std::size_t index, std::size_t range,
                           const T& value) {
  if (index + range > size_) throw std::out_of_range("Range out of bounds.");
  Node* ptr = head;
  for (std::size_t i = 0; i < index; ++i) ptr = ptr->next;
  for (std::size_t i = 0; i < range; ++i) {
    if (ptr != nullptr) {
      ptr->data = value;
      ptr = ptr->next;
    }
  }
}
template <typename T>
void CustomList<T>::unique() {
  Node* current = head;
  while (current != nullptr && current->next != nullptr) {
    Node* runner = current;
    while (runner->next != nullptr) {
      if (runner->next->data == current->data) {
        Node* duplicate = runner->next;
        runner->next = runner->next->next;
        if (runner->next != nullptr) {
          runner->next->prev = runner;
        } else {
          tail = runner;
        }
        delete duplicate;
        size_--;
      } else {
        runner = runner->next;
      }
    }
    current = current->next;
  }
}
template <typename T>
void CustomList<T>::unique(bool (*func)(const T&, const T&)) {
  Node* current = head;
  while (current != nullptr && current->next != nullptr) {
    Node* runner = current;
    while (runner->next != nullptr) {
      if (func(runner->next->data, current->data)) {
        Node* duplicate = runner->next;
        runner->next = runner->next->next;
        if (runner->next != nullptr) {
          runner->next->prev = runner;
        } else {
          tail = runner;
        }
        delete duplicate;
        size_--;
      } else {
        runner = runner->next;
      }
    }
    current = current->next;
  }
}

template <typename T>
void CustomList<T>::swap(CustomList<T>& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size_, other.size_);
}
template <typename T>
void CustomList<T>::merge(CustomList<T> const& other) {
  Node* thisPtr = head;
  Node* otherPtr = other.head;
  CustomList<T> resultList;
  while (thisPtr != nullptr && otherPtr != nullptr) {
    if (thisPtr->data < otherPtr->data) {
      resultList.push_back(thisPtr->data);
      thisPtr = thisPtr->next;
    } else {
      resultList.push_back(otherPtr->data);
      otherPtr = otherPtr->next;
    }
  }
  while (thisPtr != nullptr) {
    resultList.push_back(thisPtr->data);
    thisPtr = thisPtr->next;
  }
  while (otherPtr != nullptr) {
    resultList.push_back(otherPtr->data);
    otherPtr = otherPtr->next;
  }
  swap(resultList);
  other.clear();
}
template <typename T>
void CustomList<T>::splice(CustomList<T> const& other) {
  if (other.head != nullptr) {
    if (head == nullptr) {
      head = other.head;
      tail = other.tail;
    } else {
      tail->next = other.head;
      other.head->prev = tail;
      tail = other.tail;
    }
    size_ += other.size_;
    other.head = other.tail = nullptr;
    other.size_ = 0;
  }
}
template <typename T>
template <typename... Args>
void CustomList<T>::emplace(std::size_t index, Args&&... args) {
  if (index > size_) throw std::out_of_range("Index out of range.");
  if (index == 0) {
    emplace_front(std::forward<Args>(args)...);
    return;
  }
  Node* ptr = head;
  for (std::size_t i = 0; i < index - 1; i++) ptr = ptr->next;
  T value(std::forward<Args>(args)...);
  Node* newNode = new Node(value);
  newNode->next = ptr->next;
  if (ptr->next != nullptr) {
    ptr->next->prev = newNode;
  } else {
    tail = newNode;
  }
  newNode->prev = ptr;
  ptr->next = newNode;
  size_++;
}
template <typename T>
template <typename... Args>
void CustomList<T>::emplace_front(Args&&... args) {
  T value(std::forward<Args>(args)...);
  Node* newNode = new Node(value);
  if (head != nullptr) {
    newNode->next = head;
    head->prev = newNode;
  } else {
    tail = newNode;
  }
  head = newNode;
  size_++;
}
template <typename T>
template <typename... Args>
void CustomList<T>::emplace_back(Args&&... args) {
  Node* newNode = new Node(T(std::forward<Args>(args)...));
  tail->next = newNode;
  newNode->prev = tail;
  tail = newNode;
}
template <typename T>
int CustomList<T>::find_position(const iterator& it) const {
  Node* current = head;
  int index = 0;
  while (current != nullptr) {
    if (current == it.nodePtr) return index;
    current = current->next;
    ++index;
  }
  return -1;
}

#endif  // INCLUDE_CUSTOM_LIST_H_

#ifndef INCLUDE_CUSTOM_SET_H_
#define INCLUDE_CUSTOM_SET_H_

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <limits>
#include <utility>

template <class T>
class CustomSet {
 public:
  class CustomSetIterator {
   public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    explicit CustomSetIterator(pointer ptr = nullptr) : ptr_(ptr) {}

    reference operator*() const { return *ptr_; }
    pointer operator->() const { return ptr_; }
    CustomSetIterator& operator++() {
      ptr_++;
      return *this;
    }
    CustomSetIterator& operator--() {
      ptr_--;
      return *this;
    }
    CustomSetIterator operator++(int) {
      CustomSetIterator tmp = *this;
      ptr_++;
      return tmp;
    }
    CustomSetIterator operator--(int) {
      CustomSetIterator tmp = *this;
      ptr_--;
      return tmp;
    }
    CustomSetIterator operator-(int n) const {
      return CustomSetIterator(ptr_ - n);
    }
    CustomSetIterator operator+(int n) const {
      return CustomSetIterator(ptr_ + n);
    }
    friend bool operator==(const CustomSetIterator& a,
                           const CustomSetIterator& b) {
      return a.ptr_ == b.ptr_;
    }
    friend bool operator!=(const CustomSetIterator& a,
                           const CustomSetIterator& b) {
      return a.ptr_ != b.ptr_;
    }
    friend std::ptrdiff_t operator-(const CustomSetIterator& lhs,
                                    const CustomSetIterator& rhs) {
      return lhs.ptr_ - rhs.ptr_;
    }

   private:
    pointer ptr_;
  };
  using value_type = T;
  using size_type = std::size_t;
  using reference = T&;
  using const_referenece = const T&;
  using iterator = CustomSetIterator;
  using set = CustomSet;

  CustomSet();
  explicit CustomSet(std::initializer_list<T> initList);
  explicit CustomSet(const set& other);
  explicit CustomSet(set&& other);
  ~CustomSet();

  CustomSet<T>& operator=(const set& other);
  CustomSet<T>& operator=(set&& other);

  iterator begin();
  iterator end();
  const iterator cbegin() const;
  const iterator cend() const;
  iterator rbegin();
  iterator rend();
  const iterator crbegin() const;
  const iterator crend() const;

  size_type size() const;
  size_type max_size() const;
  bool empty() const;
  bool contains(const value_type* value);

  std::pair<iterator, bool> insert(const value_type& value);
  void erase(const T& value);
  void erase(iterator pos);
  void clear();

  iterator find(const T& value);
  size_type count(const T& value);

  template <typename... Args>
  void emplace(Args&&... args);

  void swap(set& other);
  void merge(set const& other);

  std::function<bool(const T&, const T&)> key_comp();
  std::function<bool(const T&, const T&)> value_comp();
  iterator upper_bound(const T& value);
  template <typename... Args>
  iterator emplace_hint(iterator position, Args&&... args);

 private:
  std::size_t size_;
  std::size_t capacity_;
  T* array_;

  void resize();
};

template <typename T>
CustomSet<T>::CustomSet() : size_(0), capacity_(0), array_(nullptr) {}
template <typename T>
CustomSet<T>::~CustomSet() {
  delete[] array_;
}
template <typename T>
CustomSet<T>::CustomSet(const CustomSet<T>& other)
    : size_(other.size_),
      capacity_(other.capacity_),
      array_(new T[other.capacity_]) {
  std::copy(other.array_, other.array_ + other.size_, array_);
}
template <typename T>
CustomSet<T>::CustomSet(set&& other) {
  if (array_ == nullptr) {
    clear();
  }
  size_ = other.size_;
  capacity_ = other.capacity_;
  array_ = other.array_;

  other.size_ = 0;
  other.capacity_ = 0;
  other.array_ = nullptr;
}
template <typename T>
CustomSet<T>& CustomSet<T>::operator=(set&& other) {
  if (this != &other) {
    clear();

    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = other.array_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.array_ = nullptr;
  }
  return *this;
}
template <typename T>
CustomSet<T>& CustomSet<T>::operator=(const CustomSet<T>& other) {
  if (this != &other) {
    T* newArray = new T[other.capacity_];
    for (std::size_t i = 0; i < other.size_; i++) {
      newArray[i] = other.array_[i];
    }
    delete[] array_;
    array_ = newArray;
    size_ = other.size_;
    capacity_ = other.capacity_;
  }
  return *this;
}
template <typename T>
void CustomSet<T>::resize() {
  T* ptr = new T[capacity_ == 0 ? 1 : capacity_ * 2];
  for (size_t i = 0; i < size_; i++) {
    ptr[i] = array_[i];
  }
  delete[] array_;
  array_ = ptr;
  capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
}
template <typename T>
std::pair<typename CustomSet<T>::iterator, bool> CustomSet<T>::insert(
    const value_type& value) {
  for (std::size_t i = 0; i < size_; ++i) {
    if (array_[i] == value) {
      return std::make_pair(iterator(array_ + i), false);
    }
  }
  if (size_ == capacity_) {
    resize();
  }
  array_[size_] = value;
  ++size_;
  return std::make_pair(iterator(array_ + size_ - 1), true);
}
template <typename T>
void CustomSet<T>::erase(CustomSet::iterator pos) {
  if (pos < begin() || pos >= end()) {
    return;
  }
  for (iterator it = pos; it != end() - 1; ++it) {
    *it = std::move(*(it + 1));
  }
  --size_;
}
template <typename T>
CustomSet<T>::CustomSet(std::initializer_list<T> initList)
    : size_(0), capacity_(initList.size()), array_(new T[capacity_]) {
  for (const T& value : initList) {
    insert(value);
  }
}
template <typename T>
typename CustomSet<T>::iterator CustomSet<T>::begin() {
  return iterator(array_);
}
template <typename T>
typename CustomSet<T>::iterator CustomSet<T>::end() {
  return iterator(array_ + size_);
}
template <typename T>
const typename CustomSet<T>::iterator CustomSet<T>::cbegin() const {
  return iterator(array_);
}
template <typename T>
const typename CustomSet<T>::iterator CustomSet<T>::cend() const {
  return iterator(array_ + size_);
}
template <typename T>
typename CustomSet<T>::iterator CustomSet<T>::rbegin() {
  return iterator(array_ + size_ - 1);
}
template <typename T>
typename CustomSet<T>::iterator CustomSet<T>::rend() {
  return iterator(array_ - 1);
}
template <typename T>
const typename CustomSet<T>::iterator CustomSet<T>::crbegin() const {
  return iterator(array_ + size_ - 1);
}
template <typename T>
const typename CustomSet<T>::iterator CustomSet<T>::crend() const {
  return iterator(array_ - 1);
}
template <typename T>
std::size_t CustomSet<T>::size() const {
  return size_;
}
template <typename T>
std::size_t CustomSet<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(T);
}
template <typename T>
bool CustomSet<T>::empty() const {
  return size_ == 0;
}
template <typename T>
bool CustomSet<T>::contains(const T* value) {
  bool answer = false;
  if (array_ != nullptr) {
    for (std::size_t i = 0; i < size_; i++)
      if (array_[i] == value) {
        answer = true;
        break;
      }
  }
  return answer;
}
template <typename T>
void CustomSet<T>::erase(const T& value) {
  for (std::size_t i = 0; i < size_; ++i) {
    if (array_[i] == value) {
      for (std::size_t j = i; j < size_ - 1; ++j) {
        array_[j] = array_[j + 1];
      }
      --size_;
      return;
    }
  }
}
template <typename T>
void CustomSet<T>::clear() {
  delete[] array_;
  array_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}
template <typename T>
typename CustomSet<T>::iterator CustomSet<T>::find(const T& value) {
  for (std::size_t i = 0; i < size_; ++i) {
    if (array_[i] == value) {
      return iterator(array_ + i);
    }
  }
  return end();
}
template <typename T>
std::size_t CustomSet<T>::count(const T& value) {
  for (std::size_t i = 0; i < size_; ++i) {
    if (array_[i] == value) {
      return 1;
    }
  }
  return 0;
}
template <typename T>
template <typename... Args>
void CustomSet<T>::emplace(Args&&... args) {
  T temp(std::forward<Args>(args)...);
  if (find(temp) != nullptr) {
    return;
  }
  if (size_ == capacity_) {
    resize();
  }
  new (&array_[size_]) T(std::move(temp));
  ++size_;
}
template <typename T>
void CustomSet<T>::swap(CustomSet<T>& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(array_, other.array_);
}
template <typename T>
void CustomSet<T>::merge(set const& other) {
  for (std::size_t i = 0; i < other.size_; i++) {
    if (!contains(other.array_[i])) {
      if (size_ == capacity_) {
        resize();
      }
      array_[size_++] = other.array_[i];
    }
  }
}
template <typename T>
std::function<bool(const T&, const T&)> key_comp() {
  return std::less<T>();
}

template <typename T>
std::function<bool(const T&, const T&)> value_comp() {
  return std::less<T>();
}
template <typename T>
typename CustomSet<T>::iterator CustomSet<T>::upper_bound(const T& value) {
  auto comp = key_comp();
  for (std::size_t i = 0; i < size_; ++i) {
    if (comp(value, array_[i])) {
      return iterator(array_ + i);
    }
  }
  return iterator(array_ + size_);
}
template <typename T>
template <typename... Args>
typename CustomSet<T>::iterator CustomSet<T>::emplace_hint(iterator pos,
                                                           Args&&... args) {
  if (size_ == capacity_) resize();
  std::size_t index = pos - begin();
  for (std::size_t i = size_; i > index; --i) {
    array_[i] = std::move(array_[i - 1]);
  }
  new (array_ + index) T(std::forward<Args>(args)...);
  ++size_;
  return iterator(array_ + index);
}

#endif  // INCLUDE_CUSTOM_SET_H_

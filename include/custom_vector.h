#ifndef INCLUDE_CUSTOM_VECTOR_H_
#define INCLUDE_CUSTOM_VECTOR_H_

#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

template <class T>
class CustomVector {
 public:
  class CustomVectorIterator {
   public:
    using pointer = T*;
    using reference = T&;

    explicit CustomVectorIterator(pointer ptr) : ptr_(ptr){};

    reference operator*() const { return *ptr_; }
    CustomVectorIterator& operator++() {
      ptr_++;
      return *this;
    }
    CustomVectorIterator operator++(int) {
      CustomVectorIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    CustomVectorIterator& operator--() {
      ptr_--;
      return *this;
    }
    CustomVectorIterator operator--(int) {
      CustomVectorIterator tmp = *this;
      --(*this);
      return tmp;
    }
    bool operator==(const CustomVectorIterator& other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const CustomVectorIterator& other) const {
      return ptr_ != other.ptr_;
    }

   private:
    pointer ptr_;
  };

  using value_type = T;
  using reference = T&;
  using const_reference = T const&;
  using iterator = CustomVectorIterator;
  using size_type = std::size_t;
  using vector = CustomVector;
  using vector_reference = CustomVector&;

  CustomVector();
  explicit CustomVector(std::size_t initialCapacity);
  CustomVector(const CustomVector<T>& other);
  explicit CustomVector(vector&& other) noexcept;
  ~CustomVector();

  // Operators
  CustomVector& operator=(vector_reference other);
  CustomVector& operator=(vector&& other);

  // Iterators
  iterator begin();
  iterator end();
  iterator rbegin();
  iterator rend();
  const iterator cbegin() const;
  const iterator cend() const;
  const iterator crbegin() const;
  const iterator crend() const;

  // Capacity
  void reserve(size_type newCapacity);
  void resize(size_type newSize, const_reference value);
  size_type size() const;
  size_type capacity() const;
  bool empty() const;
  size_type max_size() const;
  void shrink_to_fit() const;

  // Element access
  reference operator[](size_type index);
  const_reference operator[](size_type index) const;
  reference at(size_type index);
  const_reference front() const;
  const_reference back() const;
  reference data() const;

  // Modifiers
  void assign(size_type count, const_reference value);
  void push_back(const_reference value);
  void pop_back();
  void insert(size_type index, const_reference value);
  iterator insert(iterator pos, const_reference value);
  void erase(size_type index);
  void clear();
  void swap(vector_reference other);

  template <typename... Args>
  void emplace_back(Args&&... args);
  template <typename... Args>
  void emplace(size_type index, Args&&... args);

 private:
  T* array;
  std::size_t size_;
  std::size_t capacity_;

  void reallocate(std::size_t newCapacity);
};

template <class T>
T& CustomVector<T>::at(size_type index) {
  if (index >= this->size_) {
    throw std::out_of_range("Index out of range.");
  }

  return this->array[index];
}

template <typename T>
CustomVector<T>::CustomVector() : array(nullptr), size_(0), capacity_(0) {}

template <typename T>
CustomVector<T>::CustomVector(size_type initialCapacity)
    : array(new T[initialCapacity]), size_(0), capacity_(initialCapacity) {}

template <typename T>
CustomVector<T>::CustomVector(const CustomVector<T>& other)
    : array(new T[other.capacity_]),
      size_(other.size_),
      capacity_(other.capacity_) {
  for (std::size_t i = 0; i < size_; ++i) {
    array[i] = other.array[i];
  }
}
template <typename T>
CustomVector<T>::CustomVector(CustomVector<T>&& other) noexcept
    : array(other.array), size_(other.size_), capacity_(other.capacity_) {
  other.array = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}
template <typename T>
CustomVector<T>::~CustomVector() {
  delete[] array;
}

template <typename T>
typename CustomVector<T>::vector_reference CustomVector<T>::operator=(
    vector_reference other) {
  if (this != &other) {
    T* newArray = new T[other.capacity_];
    for (size_type i = 0; i < other.size_; ++i) {
      newArray[i] = other.array[i];
    }
    delete[] array;
    array = newArray;
    size_ = other.size_;
    capacity_ = other.capacity_;
  }
  return *this;
}

template <class T>
CustomVector<T>& CustomVector<T>::operator=(CustomVector<T>&& other) {
  if (this != &other) {
    delete[] array;
    array = other.array;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.array = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

template <typename T>
T& CustomVector<T>::operator[](size_type index) {
  return array[index];
}

template <typename T>
const T& CustomVector<T>::operator[](size_type index) const {
  return array[index];
}

template <typename T>
void CustomVector<T>::reallocate(size_type newCapacity) {
  if (newCapacity <= capacity_) {
    throw std::invalid_argument(
        "New capacity must be greater than current capacity.");
  }
  T* newArray = new T[newCapacity];
  for (std::size_t i = 0; i < size_; i++) {
    newArray[i] = std::move(array[i]);
  }
  delete[] array;
  array = newArray;
  capacity_ = newCapacity;
}

template <typename T>
void CustomVector<T>::push_back(const T& value) {
  if (size_ == capacity_) {
    reallocate(capacity_ > 0 ? capacity_ * 2 : 1);
  }
  array[size_++] = value;
}

template <typename T>
void CustomVector<T>::reserve(std::size_t newCapacity) {
  if (newCapacity > capacity_) {
    reallocate(newCapacity);
  }
}

template <typename T>
std::size_t CustomVector<T>::size() const {
  return size_;
}

template <typename T>
std::size_t CustomVector<T>::capacity() const {
  return capacity_;
}

template <typename T>
bool CustomVector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename CustomVector<T>::const_reference CustomVector<T>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty.");
  }
  return array[0];
}

template <typename T>
typename CustomVector<T>::const_reference CustomVector<T>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty.");
  }
  return array[size_ - 1];
}

template <typename T>
typename CustomVector<T>::reference CustomVector<T>::data() const {
  return array;
}

template <typename T>
void CustomVector<T>::resize(std::size_t newSize, const T& value) {
  if (newSize > capacity_) {
    reallocate(newSize);
  }
  for (std::size_t i = size_; i < newSize; ++i) {
    array[i] = value;
  }
  size_ = newSize;
}

template <typename T>
void CustomVector<T>::pop_back() {
  if (size_ > 0) {
    size_ -= 1;
  }
}

template <typename T>
void CustomVector<T>::clear() {
  delete[] array;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
void CustomVector<T>::assign(std::size_t count, const T& value) {
  clear();
  if (count > capacity_) {
    reallocate(count);
  }
  for (std::size_t i = 0; i < count; i++) {
    array[i] = value;
  }
  size_ = count;
}

template <typename T>
void CustomVector<T>::insert(std::size_t index, const T& value) {
  if (index > size_) {
    throw std::out_of_range("Index is out of range.");
  }
  if (size_ == capacity_) {
    reallocate(capacity_ > 0 ? capacity_ * 2 : 1);
  }
  for (std::size_t i = size_; i > index; --i) {
    array[i] = std::move(array[i - 1]);
  }
  array[index] = value;
  ++size_;
}

template <typename T>
void CustomVector<T>::erase(std::size_t index) {
  if (index >= size_) {
    throw std::out_of_range("Index is out of range.");
  }
  for (std::size_t i = index; i < size_ - 1; i++) {
    array[i] = std::move(array[i + 1]);
  }
  --size_;
}

template <typename T>
void CustomVector<T>::swap(CustomVector<T>& other) {
  std::swap(array, other.array);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <typename... Args>
void CustomVector<T>::emplace_back(Args&&... args) {
  if (size_ == capacity_) {
    reallocate(capacity_ > 0 ? capacity_ * 2 : 1);
  }
  new (&array[size_]) T(std::forward<Args>(args)...);
  ++size_;
}

template <typename T>
template <typename... Args>
void CustomVector<T>::emplace(std::size_t index, Args&&... args) {
  if (index > size_) {
    throw std::out_of_range("Index out of range.");
  }
  if (size_ == capacity_) {
    reallocate(capacity_ > 0 ? capacity_ * 2 : 1);
  }
  for (std::size_t i = size_; i > index; --i) {
    array[i] = std::move(array[i - 1]);
  }
  new (&array[index]) T(std::forward<Args>(args)...);
  ++size_;
}

template <typename T>
typename CustomVector<T>::iterator CustomVector<T>::begin() {
  return iterator(array);
}

template <typename T>
typename CustomVector<T>::iterator CustomVector<T>::end() {
  return iterator(array + size_);
}

template <typename T>
const typename CustomVector<T>::iterator CustomVector<T>::cbegin() const {
  return iterator(array);
}

template <typename T>
const typename CustomVector<T>::iterator CustomVector<T>::cend() const {
  return iterator(array + size_);
}

template <typename T>
typename CustomVector<T>::iterator CustomVector<T>::rbegin() {
  return iterator(array + size_ - 1);
}

template <typename T>
typename CustomVector<T>::iterator CustomVector<T>::rend() {
  return iterator(array - 1);
}

template <typename T>
const typename CustomVector<T>::iterator CustomVector<T>::crbegin() const {
  return iterator(array + size_ - 1);
}

template <typename T>
const typename CustomVector<T>::iterator CustomVector<T>::crend() const {
  return iterator(array - 1);
}

template <typename T>
typename CustomVector<T>::size_type CustomVector<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template <typename T>
void CustomVector<T>::shrink_to_fit() const {
  if (size_ < capacity_) {
    T* newArray = new T[size_];
    for (std::size_t i = 0; i < size_; i++) {
      newArray[i] = std::move(array[i]);
    }
    delete[] array;
    array = newArray;
    this->capacity_ = this->size_;
  }
}
template <typename T>
typename CustomVector<T>::iterator CustomVector<T>::insert(
    iterator pos, const_reference value) {
  size_t index = pos - begin();
  if (size_ == capacity_) {
    size_t newCapacity = capacity_ > 0 ? capacity_ * 2 : 1;
    reallocate(newCapacity);
  }
  for (size_t i = size_; i > index; --i) {
    array[i] = std::move(array[i - 1]);
  }
  array[index] = value;
  ++size_;
  return iterator(&array[index]);
}

#endif  // INCLUDE_CUSTOM_VECTOR_H_

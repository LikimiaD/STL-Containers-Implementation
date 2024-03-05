#ifndef INCLUDE_CUSTOM_QUEUE_H_
#define INCLUDE_CUSTOM_QUEUE_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template <class T>
class CustomQueue {
  using value_type = T;
  using value_ptr = T*;
  using reference = T&;
  using size_type = std::size_t;
  using const_reference = const T&;
  using queue = CustomQueue;

 public:
  CustomQueue();
  explicit CustomQueue(std::initializer_list<value_type> const& items);
  explicit CustomQueue(const queue& other);
  explicit CustomQueue(queue&& q);
  ~CustomQueue();
  queue& operator=(const queue& other);
  queue& operator=(queue&& other);

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

  bool empty();
  size_type size();

  void swap(queue& other);
  void pop();
  void push(const_reference value);

  template <typename... Args>
  void emplace(Args&&... args);

 private:
  size_type size_;
  size_type capacity_;
  value_ptr array_;

  void resize();
};

template <typename T>
CustomQueue<T>::CustomQueue() : size_(0), capacity_(0), array_(nullptr) {}
template <typename T>
CustomQueue<T>::~CustomQueue() {
  delete[] array_;
}
template <typename T>
CustomQueue<T>::CustomQueue(const CustomQueue<T>& other) {
  size_ = other.size_;
  capacity_ = other.capacity_;
  if (other.array_ != nullptr) {
    array_ = new T[other.capacity_];
    for (std::size_t i = 0; i < other.size_; ++i) array_[i] = other.array_[i];
  } else {
    array_ = nullptr;
  }
}
template <typename T>
CustomQueue<T>::CustomQueue(CustomQueue<T>&& q)
    : size_(q.size_), capacity_(q.capacity_), array_(q.array_) {
  q.array_ = nullptr;
  q.size_ = 0;
  q.capacity_ = 0;
}
template <typename T>
CustomQueue<T>::CustomQueue(std::initializer_list<T> const& list)
    : size_(0), capacity_(0), array_(nullptr) {
  for (const T& value : list) {
    push(value);
  }
}
template <typename T>
CustomQueue<T>& CustomQueue<T>::operator=(const CustomQueue<T>& other) {
  if (this != &other) {
    CustomQueue<T> temp(other);
    swap(temp);
  }
  return *this;
}
template <typename T>
CustomQueue<T>& CustomQueue<T>::operator=(CustomQueue<T>&& other) {
  if (this != &other) {
    delete[] array_;
    array_ = other.array_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.array_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}
template <typename T>
void CustomQueue<T>::swap(CustomQueue<T>& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(array_, other.array_);
}
template <typename T>
void CustomQueue<T>::pop() {
  if (size_ > 0) {
    array_[0].~T();
    for (std::size_t i = 1; i < size_; ++i) {
      array_[i - 1] = std::move(array_[i]);
    }
    --size_;
  }
}
template <typename T>
void CustomQueue<T>::resize() {
  T* newArray = new T[(capacity_ == 0 ? 1 : capacity_) * 2];
  for (std::size_t i = 0; i < size_; ++i) {
    newArray[i] = std::move(array_[i]);
  }
  delete[] array_;
  array_ = newArray;
  capacity_ = (capacity_ == 0 ? 1 : capacity_) * 2;
}
template <typename T>
void CustomQueue<T>::push(const T& value) {
  if (size_ == capacity_ || array_ == nullptr) {
    resize();
  }
  array_[size_++] = value;
}
template <typename T>
template <typename... Args>
void CustomQueue<T>::emplace(Args&&... args) {
  if (size_ == capacity_) {
    resize();
  }
  new (&array_[size_++]) T(std::forward<Args>(args)...);
}

template <class T>
typename CustomQueue<T>::reference CustomQueue<T>::front() {
  if (size_ == 0) {
    throw std::out_of_range("Queue is empty");
  }
  return array_[0];
}

template <class T>
typename CustomQueue<T>::const_reference CustomQueue<T>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("Queue is empty");
  }
  return array_[0];
}

template <class T>
typename CustomQueue<T>::reference CustomQueue<T>::back() {
  if (size_ == 0) {
    throw std::out_of_range("Queue is empty");
  }
  return array_[size_ - 1];
}

template <class T>
typename CustomQueue<T>::const_reference CustomQueue<T>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("Queue is empty");
  }
  return array_[size_ - 1];
}

template <class T>
bool CustomQueue<T>::empty() {
  return size_ == 0;
}

template <class T>
std::size_t CustomQueue<T>::size() {
  return size_;
}

#endif  // INCLUDE_CUSTOM_QUEUE_H_

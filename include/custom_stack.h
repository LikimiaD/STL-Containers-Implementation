#ifndef INCLUDE_CUSTOM_STACK_H_
#define INCLUDE_CUSTOM_STACK_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template <class T>
class CustomStack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  using stack = CustomStack;

  CustomStack();
  explicit CustomStack(std::initializer_list<T> const& value);
  explicit CustomStack(const stack& s);
  explicit CustomStack(stack&& s);
  ~CustomStack();

  stack& operator=(const stack& other);
  stack& operator=(stack&& other);

  bool empty() const;
  size_type size() const;
  const_reference top() const;

  void push(const_reference value);
  void pop();
  void swap(stack& other);

  template <typename... Args>
  void emplace(Args&&... args);

 private:
  std::size_t size_;
  std::size_t capacity_;
  T* array_;

  void resize();
};

template <typename T>
CustomStack<T>::CustomStack() : size_(0), capacity_(0), array_(nullptr) {}
template <typename T>
CustomStack<T>::CustomStack(const CustomStack<T>& other)
    : size_(other.size_),
      capacity_(other.capacity_),
      array_(new T[other.capacity_]) {
  for (std::size_t i = 0; i < size_; i++) {
    array_[i] = other.array_[i];
  }
}
template <typename T>
CustomStack<T>::CustomStack(stack&& s)
    : size_(s.size_), capacity_(s.capacity_), array_(s.array_) {
  s.array_ = nullptr;
  s.size_ = 0;
  s.capacity_ = 0;
}
template <typename T>
CustomStack<T>::CustomStack(std::initializer_list<T> const& value)
    : size_(0), capacity_(0), array_(nullptr) {
  for (const T& item : value) {
    push(item);
  }
}
template <typename T>
CustomStack<T>& CustomStack<T>::operator=(const CustomStack<T>& other) {
  if (this != &other) {
    delete[] array_;
    array_ = new T[other.capacity_];
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (std::size_t i = 0; i < size_; i++) {
      array_[i] = std::move(other.array_[i]);
    }
  }
  return *this;
}
template <typename T>
CustomStack<T>& CustomStack<T>::operator=(CustomStack<T>&& other) {
  if (this != &other) {
    delete[] array_;
    array_ = other.array_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.capacity_ = 0;
    other.size_ = 0;
    other.array_ = nullptr;
  }
  return *this;
}
template <typename T>
CustomStack<T>::~CustomStack() {
  delete[] array_;
  size_ = 0;
  capacity_ = 0;
}
template <typename T>
bool CustomStack<T>::empty() const {
  return size_ == 0;
}
template <typename T>
std::size_t CustomStack<T>::size() const {
  return size_;
}
template <typename T>
const T& CustomStack<T>::top() const {
  if (size_ == 0) throw std::out_of_range("Stack is empty.");
  return array_[size_ - 1];
}
template <typename T>
void CustomStack<T>::resize() {
  capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
  T* newArray = new T[capacity_];
  for (std::size_t i = 0; i < size_; i++) newArray[i] = std::move(array_[i]);
  delete[] array_;
  array_ = newArray;
}
template <typename T>
void CustomStack<T>::push(const T& value) {
  if (size_ == capacity_) {
    resize();
  }
  array_[size_++] = value;
}
template <typename T>
void CustomStack<T>::pop() {
  if (size_ == 0) throw std::out_of_range("Stack is empty.");
  --size_;
}
template <typename T>
template <typename... Args>
void CustomStack<T>::emplace(Args&&... args) {
  if (size_ == capacity_) {
    resize();
  }
  new (&array_[size_]) T(std::forward<Args>(args)...);
  size_++;
}
template <typename T>
void CustomStack<T>::swap(CustomStack<T>& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(array_, other.array_);
}

#endif  // INCLUDE_CUSTOM_STACK_H_

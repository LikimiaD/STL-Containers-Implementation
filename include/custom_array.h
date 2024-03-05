#ifndef CUSTOM_ARRAY_H_
#define CUSTOM_ARRAY_H_

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>

template <typename T, std::size_t N>
class CustomArray {
 private:
  T array_[N];

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;
  using array = CustomArray;

  explicit CustomArray();
  explicit CustomArray(std::initializer_list<value_type> const& items);
  explicit CustomArray(const array& a);
  explicit CustomArray(array&& a) noexcept;
  ~CustomArray();

  CustomArray& operator=(const array& other);
  CustomArray& operator=(array&& other) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size() const;

  void swap(array& other);
  void fill(const_reference value);
};

template <typename T, std::size_t N>
CustomArray<T, N>::CustomArray() {
  for (std::size_t i = 0; i < N; ++i) array_[i] = T();
}
template <typename T, std::size_t N>
CustomArray<T, N>::CustomArray(std::initializer_list<T> const& items) {
  std::size_t i = 0;
  for (const T& value : items) {
    if (i < N)
      array_[i++] = value;
    else
      break;
  }
  for (; i < N; ++i) array_[i] = T();
}
template <typename T, std::size_t N>
CustomArray<T, N>::CustomArray(array&& a) noexcept {
  for (std::size_t i = 0; i < N; ++i) array_[i] = std::move(a.array_[i]);
}
template <typename T, std::size_t N>
CustomArray<T, N>::~CustomArray() {}
template <typename T, std::size_t N>
CustomArray<T, N>& CustomArray<T, N>::operator=(const array& other) {
  if (this != &other) {
    for (std::size_t i = 0; i < N; ++i) this->array_[i] = other.array_[i];
  }
  return *this;
}
template <typename T, std::size_t N>
CustomArray<T, N>& CustomArray<T, N>::operator=(array&& other) noexcept {
  if (this != &other) {
    for (std::size_t i = 0; i < N; ++i) this->array_[i] = other.array_[i];
  }
  return *this;
}
template <typename T, std::size_t N>
T& CustomArray<T, N>::at(size_type pos) {
  if (pos >= N) throw std::out_of_range("Index out of range.");
  return this->array_[pos];
}
template <typename T, std::size_t N>
T& CustomArray<T, N>::operator[](size_type pos) {
  if (pos >= N) throw std::out_of_range("Index out of range.");
  return this->array_[pos];
}
template <typename T, std::size_t N>
const T& CustomArray<T, N>::front() {
  return this->array_[0];
}
template <typename T, std::size_t N>
const T& CustomArray<T, N>::back() {
  return this->array_[N - 1];
}
template <typename T, std::size_t N>
T* CustomArray<T, N>::data() {
  return this->array_;
}
template <typename T, std::size_t N>
T* CustomArray<T, N>::begin() {
  return this->array_;
}
template <typename T, std::size_t N>
T* CustomArray<T, N>::end() {
  return this->array_ + N;
}
template <typename T, std::size_t N>
bool CustomArray<T, N>::empty() {
  return N == 0;
}
template <typename T, std::size_t N>
std::size_t CustomArray<T, N>::size() {
  return N;
}
template <typename T, std::size_t N>
std::size_t CustomArray<T, N>::max_size() const {
  return N;
}
template <typename T, std::size_t N>
void CustomArray<T, N>::swap(array& other) {
  for (size_type i = 0; i < N; ++i) std::swap(this->array_[i], other.array_[i]);
}
template <typename T, std::size_t N>
void CustomArray<T, N>::fill(const_reference value) {
  for (std::size_t i = 0; i < N; ++i) this->array_[i] = value;
}

#endif /* CUSTOM_ARRAY_H_ */

#include "array.h"

namespace s21 {

template <typename value_type, size_t N> Array<value_type, N>::Array() {
  if (N == 0) {
    throw std::invalid_argument("Array size must be greater than 0");
  }
}

template <typename value_type, size_t N>
Array<value_type, N>::Array(std::initializer_list<value_type> const &items) {
  if (items.size() > max_size())
    throw std::bad_alloc();
  auto count = items.begin();
  for (size_t i = 0; i < N; ++i) {
    this->arr_[i] = *count;
    count++;
  }
}

template <typename value_type, size_t N>
Array<value_type, N>::Array(const Array &other) : Array<value_type, N>() {
  if (N < other.size()) {
    throw std::out_of_range("Index out of range");
  } else {
    for (size_type i = 0; i < N; ++i) {
      this->arr_[i] = other.arr_[i];
    }
  }
}

template <typename value_type, size_t N>
Array<value_type, N>::Array(Array &&other) {
  this->arr_ = other.arr_;
  other.arr_ = nullptr;
}

template <typename value_type, size_t N>
inline Array<value_type, N>::~Array() = default;

template <typename value_type, size_t N>
inline value_type &Array<value_type, N>::at(size_type index) {
  if (index < N) {
    return arr_[index];
  } else {
    throw std::out_of_range("Index out of range");
  }
}

template <typename value_type, size_t N>
Array<value_type, N> &
Array<value_type, N>::operator=(Array<value_type, N> &&other) {
  if (this != &other) {
    std::move(other.arr_, other.arr_ + other.size(), arr_);
  }
  return *this;
}

template <typename value_type, size_t N>
Array<value_type, N> &
Array<value_type, N>::operator=(const Array<value_type, N> &other) {
  if (this != &other) {
    for (size_t i = 0; i < N; ++i) {
      this->arr_[i] = other.arr_[i];
    }
  }
  return *this;
}

template <typename value_type, size_t N>
inline value_type &Array<value_type, N>::operator[](size_type index) {
  { return *(arr_ + index); }
}

template <typename value_type, size_t N>
inline const value_type &Array<value_type, N>::front() {
  return const_reference(arr_);
}

template <typename value_type, size_t N>
inline const value_type &Array<value_type, N>::back() {
  return const_reference(*(arr_ + N - 1));
}

template <typename value_type, size_t N>
inline value_type *Array<value_type, N>::data() {
  return this->arr_;
}

template <typename value_type, size_t N>
value_type *Array<value_type, N>::begin() noexcept {
  if (N == 0)
    return nullptr;
  else
    return this->arr_;
}

template <typename value_type, size_t N>
value_type *Array<value_type, N>::end() noexcept {
  if (N == 0)
    return nullptr;
  else
    return iterator(this->arr_ + N);
}

template <typename T, size_t N> inline bool Array<T, N>::empty() {
  return N == 0 ? true : false;
}

template <typename value_type, size_t N>
inline size_t Array<value_type, N>::size() const {
  return N;
}

template <typename value_type, size_t N>
inline size_t Array<value_type, N>::max_size() noexcept {
  return N;
}

template <typename value_type, size_t N>
inline void Array<value_type, N>::swap(Array &other) {
  Array<value_type, N> tmp(other);
  std::copy(this->arr_, this->arr_ + N, other.arr_);
  std::copy(tmp.arr_, tmp.arr_ + N, this->arr_);
}

template <typename T, size_t N>
inline void Array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    this->arr_[i] = value;
  }
}
} // namespace s21
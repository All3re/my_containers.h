#ifndef ARRAY_H_
#define ARRAY_H_

#include "libs.h"

namespace s21 {
template <typename T, size_t N> class Array {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array();
  Array(std::initializer_list<value_type> const &items);

  Array(const Array &other);
  Array(Array &&a);
  ~Array();

  Array &operator=(Array<value_type, N> &&other);
  Array &operator=(const Array<value_type, N> &other);

  reference at(size_type index);
  reference operator[](size_type index);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin() noexcept;
  iterator end() noexcept;

  bool empty();
  size_type size() const;
  size_type max_size() noexcept;
  void swap(Array &other);
  void fill(const_reference value);

private:
  T arr_[N];
};
} // namespace s21
#endif
#include "vector.h"

namespace s21 {

template <typename value_type>
Vector<value_type>::Vector() {
  array = nullptr;
  size = 0;
  capacity = 0;
}

template <typename value_type>
Vector<value_type>::Vector(size_type value) {
  if (value > max_size()) throw std::bad_alloc();
  size = value;
  capacity = value;
  array = reinterpret_cast<value_type*>(new int8_t[value * sizeof(value_type)]);
  ;
  for (sizet i = 0; i < value; i++) {
    array[i] = value_type();
  }
}

template <typename value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const& items) {
  if (items.size() > max_size()) throw std::bad_alloc();
  size = items.size();
  capacity = items.size();
  array =
      reinterpret_cast<value_type*>(new int8_t[capacity * sizeof(value_type)]);
  std::uninitialized_copy(items.begin(), items.end(), array);
}

template <typename value_type>
Vector<value_type>::Vector(const Vector& v) {
  this->size = v.size;
  this->capacity = v.capacity;
  array =
      reinterpret_cast<value_type*>(new int8_t[capacity * sizeof(value_type)]);
  try {
    std::uninitialized_copy(v.array, v.array + v.size, array);
  } catch (...) {
    delete[] reinterpret_cast<int8_t*>(array);
    throw std::bad_alloc();
  }
}

template <typename value_type>
Vector<value_type>::Vector(Vector&& v) noexcept {
  this->size = v.size;
  this->capacity = v.capacity;
  this->array = v.array;
  v.size = 0;
  v.capacity = 0;
  v.array = nullptr;
}

template <typename value_type>
Vector<value_type>::~Vector() {
  clear();
  size = 0;
  capacity = 0;
  delete[] reinterpret_cast<int8_t*>(array);
  array = nullptr;
}

template <typename value_type>
Vector<value_type>& Vector<value_type>::operator=(Vector&& v) noexcept {
  if (this != &v) {
    this->clear();
    this->array = v.array;
    this->size = v.size;
    this->capacity = v.capacity;
    v.array = nullptr;
    v.size = 0;
    v.capacity = 0;
  }
  return *this;
}

template <typename value_type>
value_type& Vector<value_type>::at(size_type pos) {
  if (pos < size) {
    return array[pos];
  } else {
    throw std::out_of_range("Index out of range");
  }
}

template <typename value_type>
value_type& Vector<value_type>::operator[](size_type pos) {
  return array[pos];
}

template <typename value_type>
const value_type& Vector<value_type>::front() {
  if (this->empty()) throw std::out_of_range("Index out of range");
  return array[0];
}

template <typename value_type>
const value_type& Vector<value_type>::back() {
  if (this->empty()) throw std::out_of_range("Index out of range");
  return array[size - 1];
}

template <typename value_type>
value_type* Vector<value_type>::data() {
  return array;
}

template <typename value_type>
inline value_type* Vector<value_type>::begin() {
  return iterator(array);
}

template <typename value_type>
inline value_type* Vector<value_type>::end() {
  return iterator(array + size);
}

template <typename value_type>
size_t Vector<value_type>::size() {
  return this->size;
}

template <typename value_type>
size_t Vector<value_type>::max_size() {
  return sizeMAX / sizeof(value_type);
}

template <typename value_type>
size_t Vector<value_type>::capacity() {
  return this->capacity;
}

template <typename value_type>
void Vector<value_type>::shrink_to_fit() {
  if (capacity == size) return;
  value_type* new_arr =
      reinterpret_cast<value_type*>(new int8_t[size * sizeof(value_type)]);
  try {
    std::uninitialized_copy(array, array + size, new_arr);
  } catch (...) {
    delete[] reinterpret_cast<int8_t*>(new_arr);
    throw;
  }
  for (sizet i = 0; i < size; ++i) {
    (array + i)->~value_type();
  }
  delete[] reinterpret_cast<int8_t*>(array);
  array = new_arr;
  capacity = size;
}

template <typename value_type>
void Vector<value_type>::reserve(size_type new_capacity) {
  if (new_capacity <= capacity) return;
  if (new_capacity > max_size()) throw std::bad_alloc();
  value_type* new_arr = reinterpret_cast<value_type*>(
      new int8_t[new_capacity * sizeof(value_type)]);
  try {
    std::uninitialized_copy(array, array + size, new_arr);
  } catch (...) {
    delete[] reinterpret_cast<int8_t*>(new_arr);
    throw std::bad_alloc();
  }

  if (array != nullptr) {
    for (sizet i = 0; i < size; ++i) {
      if ((array + i) != nullptr) {
        (array + i)->~value_type();
      }
    }
    delete[] reinterpret_cast<int8_t*>(array);
  }
  array = new_arr;
  capacity = new_capacity;
}

template <typename value_type>
void Vector<value_type>::resize(size_type new_size) {
  if (new_size > capacity) reserve(new_size);
  for (sizet i = size; i < new_size; ++i) {
    new (array + i) value_type();
  }
  size = new_size;
}

template <typename value_type>
bool Vector<value_type>::empty() {
  return (size == 0 ? true : false);
}

template <typename value_type>
void Vector<value_type>::clear() {
  for (sizet i = 0; i < size; ++i) {
    (array + i)->~value_type();
  }
  size = 0;
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::insert(
    iterator pos, const_reference value) {
  if (size == 0) {
    push_back(value);
    return begin();
  }

  if (pos < this->begin() || pos > this->end()) {
    throw std::out_of_range("position is out of range");
  }

  sizet index = pos - this->begin();
  if (size == capacity) {
    reserve(capacity == 0 ? 1 : capacity * 2);
  }

  resize(size + 1);
  std::move_backward(this->begin() + index, this->end() - 1, this->end());
  iterator result = this->begin() + index;
  array[index] = value;
  return result;
}

template <typename value_type>
void Vector<value_type>::erase(iterator pos) {
  for (iterator i = pos; i != end() - 1; ++i) {
    *(i) = *(i + 1);
  }
  --size;
}

template <typename value_type>
void Vector<value_type>::push_back(const_reference value) {
  if (capacity == size) {
    reserve(capacity == 0 ? 1 : capacity * 2);
  }
  try {
    new (array + size) value_type(value);
  } catch (...) {
    (array + size)->~value_type();
    throw;
  }
  size++;
}

template <typename value_type>
void Vector<value_type>::pop_back() {
  --size;
  (array + size)->~value_type();
}

template <typename value_type>
void Vector<value_type>::swap(Vector<value_type>& other) {
  s21::Vector<value_type> tmp;
  tmp.array = this->array;
  tmp.size = this->size;
  tmp.capacity = this->capacity;
  this->array = other.array;
  this->size = other.size;
  this->capacity = other.capacity;
  other.array = tmp.array;
  other.size = tmp.size;
  other.capacity = tmp.capacity;
  tmp.array = nullptr;
  tmp.size = 0;
  tmp.capacity = 0;
}

template <typename value_type>
template <typename... Args>
typename Vector<value_type>::iterator Vector<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  iterator it = const_cast<iterator>(pos);
  for (auto value : {std::forward<Args>(args)...}) {
    it = insert(it, value);
    it++;
  }
  return --it;
}

template <typename value_type>
template <typename... Args>
void Vector<value_type>::insert_many_back(Args&&... args) {
  for (auto value : {std::forward<Args>(args)...}) {
    push_back(value);
  }
}
}
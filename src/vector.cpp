#include "vector.h"

namespace s21 {

template <typename value_type> Vector<value_type>::Vector() {
  array_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename value_type> Vector<value_type>::Vector(size_type value) {
  if (value > max_size())
    throw std::bad_alloc();
  size_ = value;
  capacity_ = value;
  array_ =
      reinterpret_cast<value_type *>(new int8_t[value * sizeof(value_type)]);
  ;
  for (size_t i = 0; i < value; i++) {
    array_[i] = value_type();
  }
}

template <typename value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const &items) {
  if (items.size() > max_size())
    throw std::bad_alloc();
  size_ = items.size();
  capacity_ = items.size();
  array_ = reinterpret_cast<value_type *>(
      new int8_t[capacity_ * sizeof(value_type)]);
  std::uninitialized_copy(items.begin(), items.end(), array_);
}

template <typename value_type> Vector<value_type>::Vector(const Vector &v) {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  array_ = reinterpret_cast<value_type *>(
      new int8_t[capacity_ * sizeof(value_type)]);
  try {
    std::uninitialized_copy(v.array_, v.array_ + v.size_, array_);
  } catch (...) {
    delete[] reinterpret_cast<int8_t *>(array_);
    throw std::bad_alloc();
  }
}

template <typename value_type> Vector<value_type>::Vector(Vector &&v) noexcept {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  this->array_ = v.array_;
  v.size_ = 0;
  v.capacity_ = 0;
  v.array_ = nullptr;
}

template <typename value_type> Vector<value_type>::~Vector() {
  clear();
  size_ = 0;
  capacity_ = 0;
  delete[] reinterpret_cast<int8_t *>(array_);
  array_ = nullptr;
}

template <typename value_type>
Vector<value_type> &Vector<value_type>::operator=(Vector &&v) noexcept {
  if (this != &v) {
    this->clear();
    this->array_ = v.array_;
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    v.array_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <typename value_type>
value_type &Vector<value_type>::at(size_type pos) {
  if (pos < size_) {
    return array_[pos];
  } else {
    throw std::out_of_range("Index out of range");
  }
}

template <typename value_type>
value_type &Vector<value_type>::operator[](size_type pos) {
  return array_[pos];
}

template <typename value_type> const value_type &Vector<value_type>::front() {
  if (this->empty())
    throw std::out_of_range("Index out of range");
  return array_[0];
}

template <typename value_type> const value_type &Vector<value_type>::back() {
  if (this->empty())
    throw std::out_of_range("Index out of range");
  return array_[size_ - 1];
}

template <typename value_type> value_type *Vector<value_type>::data() {
  return array_;
}

template <typename value_type> inline value_type *Vector<value_type>::begin() {
  return iterator(array_);
}

template <typename value_type> inline value_type *Vector<value_type>::end() {
  return iterator(array_ + size_);
}

template <typename value_type> size_t Vector<value_type>::size() {
  return this->size_;
}

template <typename value_type> size_t Vector<value_type>::max_size() {
  return SIZE_MAX / sizeof(value_type);
}

template <typename value_type> size_t Vector<value_type>::capacity() {
  return this->capacity_;
}

template <typename value_type> void Vector<value_type>::shrink_to_fit() {
  if (capacity_ == size_)
    return;
  value_type *new_arr =
      reinterpret_cast<value_type *>(new int8_t[size_ * sizeof(value_type)]);
  try {
    std::uninitialized_copy(array_, array_ + size_, new_arr);
  } catch (...) {
    delete[] reinterpret_cast<int8_t *>(new_arr);
    throw;
  }
  for (size_t i = 0; i < size_; ++i) {
    (array_ + i)->~value_type();
  }
  delete[] reinterpret_cast<int8_t *>(array_);
  array_ = new_arr;
  capacity_ = size_;
}

template <typename value_type>
void Vector<value_type>::reserve(size_type new_capacity_) {
  if (new_capacity_ <= capacity_)
    return;
  if (new_capacity_ > max_size())
    throw std::bad_alloc();
  value_type *new_arr = reinterpret_cast<value_type *>(
      new int8_t[new_capacity_ * sizeof(value_type)]);
  try {
    std::uninitialized_copy(array_, array_ + size_, new_arr);
  } catch (...) {
    delete[] reinterpret_cast<int8_t *>(new_arr);
    throw std::bad_alloc();
  }

  if (array_ != nullptr) {
    for (size_t i = 0; i < size_; ++i) {
      if ((array_ + i) != nullptr) {
        (array_ + i)->~value_type();
      }
    }
    delete[] reinterpret_cast<int8_t *>(array_);
  }
  array_ = new_arr;
  capacity_ = new_capacity_;
}

template <typename value_type>
void Vector<value_type>::resize(size_type new_size_) {
  if (new_size_ > capacity_)
    reserve(new_size_);
  for (size_t i = size_; i < new_size_; ++i) {
    new (array_ + i) value_type();
  }
  size_ = new_size_;
}

template <typename value_type> bool Vector<value_type>::empty() {
  return (size_ == 0 ? true : false);
}

template <typename value_type> void Vector<value_type>::clear() {
  for (size_t i = 0; i < size_; ++i) {
    (array_ + i)->~value_type();
  }
  size_ = 0;
}

template <typename value_type>
typename Vector<value_type>::iterator
Vector<value_type>::insert(iterator pos, const_reference value) {
  if (size_ == 0) {
    push_back(value);
    return begin();
  }

  if (pos < this->begin() || pos > this->end()) {
    throw std::out_of_range("position is out of range");
  }

  size_t index = pos - this->begin();
  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }

  resize(size_ + 1);
  std::move_backward(this->begin() + index, this->end() - 1, this->end());
  iterator result = this->begin() + index;
  array_[index] = value;
  return result;
}

template <typename value_type> void Vector<value_type>::erase(iterator pos) {
  for (iterator i = pos; i != end() - 1; ++i) {
    *(i) = *(i + 1);
  }
  --size_;
}

template <typename value_type>
void Vector<value_type>::push_back(const_reference value) {
  if (capacity_ == size_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  try {
    new (array_ + size_) value_type(value);
  } catch (...) {
    (array_ + size_)->~value_type();
    throw;
  }
  size_++;
}

template <typename value_type> void Vector<value_type>::pop_back() {
  --size_;
  (array_ + size_)->~value_type();
}

template <typename value_type>
void Vector<value_type>::swap(Vector<value_type> &other) {
  s21::Vector<value_type> tmp;
  tmp.array_ = this->array_;
  tmp.size_ = this->size_;
  tmp.capacity_ = this->capacity_;
  this->array_ = other.array_;
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;
  other.array_ = tmp.array_;
  other.size_ = tmp.size_;
  other.capacity_ = tmp.capacity_;
  tmp.array_ = nullptr;
  tmp.size_ = 0;
  tmp.capacity_ = 0;
}

template <typename value_type>
template <typename... Args>
typename Vector<value_type>::iterator
Vector<value_type>::insert_many(const_iterator pos, Args &&... args) {
  iterator it = const_cast<iterator>(pos);
  for (auto value : {std::forward<Args>(args)...}) {
    it = insert(it, value);
    it++;
  }
  return --it;
}

template <typename value_type>
template <typename... Args>
void Vector<value_type>::insert_many_back(Args &&... args) {
  for (auto value : {std::forward<Args>(args)...}) {
    push_back(value);
  }
}
}; // namespace s21
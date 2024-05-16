#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <iomanip>
#include <iostream>

namespace s21 {
template <typename T>
class Vector
{
private:
    size_t capacity;
    size_t size;
    T* array;
public:
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
    using reference =  T&;
    using const_reference =  const T&;
    using size_type = size_t;

  Vector();
  Vector(
      size_type n);
  Vector(std::initializer_list<value_type> const&
             items);       
                               
  Vector(const Vector& v);     
  Vector(Vector&& v) noexcept; 
  Vector& operator=(
      Vector&& v) noexcept; 
  ~Vector();               

  reference at(size_type pos);  
  reference operator[](size_type pos); 
  const_reference front();             
  const_reference back();              
  iterator data();                     

  iterator begin();  
  iterator end();    

  void resize(size_type new_size);  
  bool empty();                     
  size_type size();                 
  size_type max_size();  
  void reserve(size_type new_capacity);  
                                         
                                        
  size_type capacity();  
                         
  void shrink_to_fit();  

  void clear();  
  iterator insert(
      iterator pos,
      const_reference value);  
                               
  void erase(iterator pos);    
  void push_back(const_reference value); 
  void pop_back();                        
  void swap(Vector& other);             

  template <typename... Args>
  iterator insert_many(const_iterator pos,
                       Args&&... args);  
                                        
  template <typename... Args>
  void insert_many_back(
      Args&&... args);  
};
}

#endif
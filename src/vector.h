#ifndef VECTOR_CPP_
#define VECTOR_CPP_

#include <iomanip>
#include <iostream>

template <class T>
class vector
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
    vector();
    vector(size_type n);
    vector(std::initializer_list<value_type> const &items);
    vector(const vector &v);
    vector(vector &&v);
    operator=(vector &&v);
    ~vector();
    reference at(size_type pos);
    reference operator[](size_type pos);
    const_reference front();
    const_reference back();
    T* data();
};

template <class T>
class vectoriterator
{
private:
    T* iterator;
    /* data */
public:
    vectoriterator(/* args */);
    ~vectoriterator();
};

#endif
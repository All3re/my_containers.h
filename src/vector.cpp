#include "vector.h"

template <typename T>
vector<T>::vector() {
    size = 0U;
    capacity = 0U;
    array = nullptr;
};

template <typename T>
vector<T>::vector(size_type n) {
    size = n;
    capacity = n;
    if(n) {
        array = new T[n];
    }
    else{
        array = nullptr;
    }
};

template <typename T>
vector<T>::vector(const vector &v) {
    size = v.size;
    capacity = v.capacity;
    array = v.array;
};

template <typename T>
vector<T>::vector(vector &&v) {
    size = v.size;
    capacity = v.capacity;
    array = v.array;
    v.size = 0;
    v.capacity = 0;
    v.array = nullptr;
};

template<typename T>
vector<T>::vector(std::initializer_list<value_type> const &items){
    array = new value_type[items.size()];
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++)
    {
        arr[i] = *it;
        i++;
    }
    size = items.size();
    capacity = items.size();
};
#ifndef S21_LIST_H_
#define S21_LIST_H_

#include <iomanip>
#include <iostream>

namespace s21 {
template <class T>
class List {
  using A = class std::allocator<T>;

 public:
  template <class value_type>
  class Node {
   public:
    Node *pNext, *pPrev;
    value_type data;

   public:
    Node(value_type data = value_type(), Node* pPrev = nullptr,
         Node* pNext = nullptr) {
      this->data = data;
      this->pNext = pNext;
      this->pPrev = pPrev;
    }
  };
  using node_allocator =
      typename std::allocator_traits<A>::template rebind_alloc<List>;
  node_allocator allocator;

 public:
  template <class>
  class ListIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;
    using value_type = T;
    using pointer_type = value_type*;
    using reference = value_type&;
    using iterator = ListIterator<value_type>;
    ListIterator() { IterPointer_ = nullptr; }
    ListIterator(int) : ListIterator() {}
    ListIterator(Node<value_type>* IterNode) : ListIterator() {
      IterPointer_ = IterNode;
    }
    ListIterator(const ListIterator& other)
        : IterPointer_(other.IterPointer_){};
    ~ListIterator(){};
    reference operator*() const {
      if (IterPointer_ == nullptr) throw std::invalid_argument("null");
      return this->IterPointer_->data;
    }
    pointer_type operator->() const { return IterPointer_; }
    Node<value_type>* getIterPointer() { return IterPointer_; }
    ListIterator& operator++() {
      IterPointer_ = IterPointer_->pNext;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator it(*this);
      IterPointer_ = IterPointer_->pNext;
      return it;
    }
    ListIterator& operator+(int pos) {
      ListIterator::iterator current = getIterPointer();
      int temp = 0;
      while (temp != pos) {
        temp++;
        current = current.getIterPointer()->pNext;
      }
      return current;
    }
    ListIterator& operator--() {
      IterPointer_ = IterPointer_->pPrev;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator it = *this;
      --(*this);
      return it;
    }
    ListIterator operator[](const value_type index) {
      return *(IterPointer_ + index);
    }
    bool operator==(const ListIterator& other) const {
      return this->IterPointer_ == other.IterPointer_;
    };
    bool operator!=(const ListIterator& other) const {
      return this->IterPointer_ != other.IterPointer_;
    };
    bool operator<=(const ListIterator& other) {
      return (this->IterPointer_ < other.IterPointer_) ||
             (this->IterPointer_ == other.IterPointer_);
    };

   private:
    Node<value_type>* IterPointer_;
    friend class List<value_type>;
  };

 public:
  template <class>
  class ListConstIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;
    using value_type = T;
    using pointer_type = value_type*;
    using reference = value_type&;
    using const_iterator = ListConstIterator<value_type>;
    ListConstIterator() { IterPointer_ = nullptr; }
    ListConstIterator(int) : ListConstIterator() {}
    ListConstIterator(Node<value_type>* IterNode) : ListConstIterator() {
      IterPointer_ = IterNode;
    }
    ListConstIterator(const ListConstIterator& other)
        : IterPointer_(other.IterPointer_){};
    ~ListConstIterator(){};
    reference operator*() const {
      if (IterPointer_ == nullptr) throw std::invalid_argument("null");
      return this->IterPointer_->data;
    }
    pointer_type operator->() const { return IterPointer_; }
    Node<value_type>* getIterPointer() { return IterPointer_; }
    ListConstIterator& operator++() {
      IterPointer_ = IterPointer_->pNext;
      return *this;
    }
    ListConstIterator operator++(int) {
      ListConstIterator it(*this);
      IterPointer_ = IterPointer_->pNext;
      return it;
    }
    ListConstIterator& operator+(int pos) {
      const_iterator current = getIterPointer();
      int temp = 0;
      while (temp != pos) {
        temp++;
        current = current.getIterPointer()->pNext;
      }
      return current;
    }
    ListConstIterator& operator--() {
      IterPointer_ = IterPointer_->pPrev;
      return *this;
    }
    ListConstIterator operator--(int) {
      ListConstIterator it = *this;
      --(*this);
      return it;
    }
    ListConstIterator operator[](const value_type index) {
      return *(IterPointer_ + index);
    }
    bool operator==(const_iterator& other) const {
      return this->IterPointer_ == other.IterPointer_;
    };
    bool operator!=(const_iterator& other) const {
      return this->IterPointer_ != other.IterPointer_;
    };

   private:
    const Node<value_type>* IterPointer_;
    friend class List<value_type>;
  };

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  List();
  List(const List& l);
  List(List&& l) noexcept;
  List(std::initializer_list<value_type> const& items);
  List(size_type n);
  ~List();
  List& operator=(const List& l);
  List& operator=(List&& l) noexcept;
  List& operator+(const List& l);
  using iterator = ListIterator<List>;
  using const_iterator = ListConstIterator<List>;
  const_reference front();
  const_reference back();
  iterator begin() const;
  iterator end() const;
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  void push_back(const_reference data);
  void push_front(const_reference data);
  void pop_back();
  void pop_front();
  void Swap(List& l);
  void reverse();
  void Merge(List& other);
  void Splice(iterator pos, List<value_type>& other);
  void unique();
  void Sort();
  void insert(iterator pos, const_reference data);
  void erase(iterator pos);
  template <typename... Args>
  iterator insert_many(iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);
  void initializeFields();
  void print();
  int Size;
  Node<value_type>* head;
  Node<value_type>* tail;
};

}

#endif
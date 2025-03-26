/**
 * @file liste.hpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief 
 * @version 1.0
 * @date 2025-03-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #ifndef LISTE_HH
 #define LISTE_HH
 
 #include "cyclicNode.h"
 #include <cassert>
 #include <iostream>
 #include <type_traits>
 
 template <typename T>
 /**
  * @brief Classe générique Liste<T> utilisant des Chainon en noeud cyclique (voir cyclicNode.h)
  * 
  */
 class Liste
 {
 protected:
     // ─── Alias ───────────────────────────────────────────────────────────
     using Chainon = DataStructure::cyclicNode<T>;
     using value_type = T;
     using size_type = std::size_t;
     using reference = T&;
     using const_reference = const T&;
     using pointer = T*;
     using const_pointer = const T*;
 
     // ─── Protected Parameters ────────────────────────────────────────────
     Chainon* m_sentinel;
     size_type m_size;
 
     // ─── Protected Methods ───────────────────────────────────────────────
     void init();
     void clear();
 
 public:
     // ─── Constructors/Destructor ─────────────────────────────────────────
     explicit Liste();
     Liste(const Liste<T>& other);
     ~Liste();
 
     // ─── Operators ───────────────────────────────────────────────────────
     Liste<T>& operator=(const Liste<T>& other);
     
     template<typename U, typename V>
     requires std::is_convertible_v<V, U>
     friend Liste<U> operator+(const Liste<U>& l1, const Liste<V>& l2);
 
     template<typename U>
     friend std::ostream& operator<<(std::ostream& os, const Liste<U>& liste);
 
     // ─── List Operations ─────────────────────────────────────────────────
     bool empty() const;
     size_type size() const;
     const_reference front() const;
     reference front();
     const_reference back() const;
     reference back();
     void push_front(const_reference value);
     void push_back(const_reference value);
     void pop_front();
     void pop_back();
 
     // ─── Iterator Classes ────────────────────────────────────────────────
     class const_iterator {
     protected:
         Chainon* m_current;
         Chainon* m_sentinel;
         const_iterator(Chainon* node, Chainon* sentinel);
         friend class Liste<T>;
     public:
         const_iterator();
         const_iterator(const const_iterator& other);
         const_iterator& operator++();
         const_iterator& operator--();
         const_iterator operator++(int);
         const_iterator operator--(int);
         const_reference operator*() const;
         const_pointer operator->() const;
         bool operator==(const const_iterator& other) const;
         bool operator!=(const const_iterator& other) const;
     };
 
     class iterator : public const_iterator {
     protected:
         iterator(Chainon* node, Chainon* sentinel);
         friend class Liste<T>;
     public:
         iterator();
         using const_iterator::operator++;
         using const_iterator::operator--;
         reference operator*();
         pointer operator->();
         iterator& operator++();
         iterator& operator--();
         iterator operator++(int);
         iterator operator--(int);
     };
 
     // ─── Iterator Access ──────────────────────────────────────────────────
     const_iterator begin() const;
     const_iterator end() const;
     iterator begin();
     iterator end();
 
     // ─── Modifiers ────────────────────────────────────────────────────────
     iterator insert(iterator pos, const_reference value);
     iterator erase(iterator pos);
 };
 
 template<class InputIterator, typename U>
 InputIterator find(InputIterator first, InputIterator last, const U& val);
 
 #include "liste.tpp"
 #endif
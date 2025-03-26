/**
 * @file liste.tpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief 
 * @version 0.1
 * @date 2025-03-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #include <cassert>

 template<typename T>
 void Liste<T>::init() {
     m_sentinel = new Chainon();
     m_size = 0;
 }
 
 template<typename T>
 void Liste<T>::clear() {
     while (!empty()) pop_front();
 }
 
 template<typename T>
 Liste<T>::Liste() {
     init();
 }
 
 template<typename T>
 Liste<T>::Liste(const Liste<T>& other) {
     init();
     for (auto it = other.begin(); it != other.end(); ++it)
         push_back(*it);
 }
 
 template<typename T>
 Liste<T>::~Liste() {
     clear();
     delete m_sentinel;
 }
 
 template<typename T>
 Liste<T>& Liste<T>::operator=(const Liste<T>& other) {
     if (this != &other) {
         clear();
         for (auto it = other.begin(); it != other.end(); ++it)
             push_back(*it);
     }
     return *this;
 }
 
 template<typename T>
 bool Liste<T>::empty() const {
     return m_size == 0;
 }
 
 template<typename T>
 typename Liste<T>::size_type Liste<T>::size() const {
     return m_size;
 }
 
 template<typename T>
 const T& Liste<T>::front() const {
     assert(!empty());
     return m_sentinel->next()->data();
 }
 
 template<typename T>
 T& Liste<T>::front() {
     assert(!empty());
     return m_sentinel->next()->data();
 }
 
 template<typename T>
 const T& Liste<T>::back() const {
     assert(!empty());
     return m_sentinel->previous()->data();
 }
 
 template<typename T>
 T& Liste<T>::back() {
     assert(!empty());
     return m_sentinel->previous()->data();
 }
 
 template<typename T>
 void Liste<T>::push_front(const T& value) {
     Chainon* newNode = new Chainon(value);
     m_sentinel->insertAfter(newNode);
     m_size++;
 }
 
 template<typename T>
 void Liste<T>::push_back(const T& value) {
     Chainon* newNode = new Chainon(value);
     m_sentinel->insertBefore(newNode);
     m_size++;
 }
 
 template<typename T>
 void Liste<T>::pop_front() {
     assert(!empty());
     Chainon* node = m_sentinel->next();
     node->detach();
     delete node;
     m_size--;
 }
 
 template<typename T>
 void Liste<T>::pop_back() {
     assert(!empty());
     Chainon* node = m_sentinel->previous();
     node->detach();
     delete node;
     m_size--;
 }
 
 template<typename T>
 Liste<T>::const_iterator::const_iterator(Chainon* node, Chainon* sentinel)
     : m_current(node), m_sentinel(sentinel) {}
 
 template<typename T>
 Liste<T>::const_iterator::const_iterator()
     : m_current(nullptr), m_sentinel(nullptr) {}
 
 template<typename T>
 Liste<T>::const_iterator::const_iterator(const const_iterator& other)
     : m_current(other.m_current), m_sentinel(other.m_sentinel) {}
 
 template<typename T>
 typename Liste<T>::const_iterator& Liste<T>::const_iterator::operator++() {
    assert(m_current != m_sentinel && "Cannot increment past end()");
     m_current = m_current->next();
     return *this;
 }
 
 template<typename T>
 typename Liste<T>::const_iterator& Liste<T>::const_iterator::operator--() {
    assert(m_current != m_sentinel->next() && "Cannot decrement before begin()");
    m_current = m_current->previous();
     return *this;
 }
 
 template<typename T>
 typename Liste<T>::const_iterator Liste<T>::const_iterator::operator++(int) {
    assert(m_current != m_sentinel && "Cannot increment past end()");
     const_iterator tmp = *this;
     ++(*this);
     return tmp;
 }
 
 template<typename T>
 typename Liste<T>::const_iterator Liste<T>::const_iterator::operator--(int) {
    assert(m_current != m_sentinel->next() && "Cannot decrement before begin()");
    const_iterator tmp = *this;
     --(*this);
     return tmp;
 }
 
 template<typename T>
 const T& Liste<T>::const_iterator::operator*() const {
     assert(m_current != m_sentinel);
     return m_current->data();
 }
 
 template<typename T>
 const T* Liste<T>::const_iterator::operator->() const {
     assert(m_current != m_sentinel);
     return &(m_current->data());
 }
 
 template<typename T>
 bool Liste<T>::const_iterator::operator==(const const_iterator& other) const {
     return m_current == other.m_current;
 }
 
 template<typename T>
 bool Liste<T>::const_iterator::operator!=(const const_iterator& other) const {
     return m_current != other.m_current;
 }
 
 template<typename T>
 Liste<T>::iterator::iterator(Chainon* node, Chainon* sentinel)
     : const_iterator(node, sentinel) {}
 
 template<typename T>
 Liste<T>::iterator::iterator()
     : const_iterator(nullptr, nullptr) {}
 
 template<typename T>
 T& Liste<T>::iterator::operator*() {
     assert(this->m_current != this->m_sentinel);
     return this->m_current->data();
 }
 
 template<typename T>
 T* Liste<T>::iterator::operator->() {
     assert(this->m_current != this->m_sentinel);
     return &(this->m_current->data());
 }
 
 template<typename T>
 typename Liste<T>::iterator& Liste<T>::iterator::operator++() {
    assert(this->m_current != this->m_sentinel && "Cannot increment past end()");
     this->m_current = this->m_current->next();
     return *this;
 }
 
 template<typename T>
 typename Liste<T>::iterator Liste<T>::iterator::operator++(int) {
    assert(this->m_current != this->m_sentinel && "Cannot increment past end()");
     iterator tmp = *this;
     ++(*this);
     return tmp;
 }
 
 template<typename T>
 typename Liste<T>::iterator& Liste<T>::iterator::operator--() {
 assert(this->m_current != this->m_sentinel->next() && "Cannot decrement before begin()");
    this->m_current = this->m_current->previous();
    return *this;
 }
 
 template<typename T>
 typename Liste<T>::iterator Liste<T>::iterator::operator--(int) {
    assert(this->m_current != this->m_sentinel->next() && "Cannot decrement before begin()");
    iterator tmp = *this;
     --(*this);
     return tmp;
 }
 
 template<typename T>
 typename Liste<T>::const_iterator Liste<T>::begin() const {
     return const_iterator(m_sentinel->next(), m_sentinel);
 }
 
 template<typename T>
 typename Liste<T>::const_iterator Liste<T>::end() const {
     return const_iterator(m_sentinel, m_sentinel);
 }
 
 template<typename T>
 typename Liste<T>::iterator Liste<T>::begin() {
     return iterator(m_sentinel->next(), m_sentinel);
 }
 
 template<typename T>
 typename Liste<T>::iterator Liste<T>::end() {
     return iterator(m_sentinel, m_sentinel);
 }
 
 template <typename U, typename V>
 requires std::is_convertible_v<V, U>
 Liste<U> operator+(const Liste<U>& l1, const Liste<V>& l2) {
     Liste<U> res(l1);
     for (auto it = l2.begin(); it != l2.end(); ++it)
         res.push_back(*it);
     return res;
 }
 
 template<typename T>
 std::ostream& operator<<(std::ostream& os, const Liste<T>& liste) {
     os << "<";
     for (auto it = liste.begin(); it != liste.end(); ++it)
         os << *it << " ";
     os << ">";
     return os;
 }
 
 template<class InputIterator, typename T>
 InputIterator find(InputIterator first, InputIterator last, const T& val) {
     while(first != last) {
         if(*first == val) return first;
         ++first;
     }
     return last;
 }
 
 template<typename T>
 typename Liste<T>::iterator Liste<T>::insert(iterator pos, const T& value) {
     Chainon* posNode = pos.m_current;
     Chainon* newNode = new Chainon(value);
     posNode->insertBefore(newNode);
     m_size++;
     return iterator(newNode, m_sentinel);
 }
 
 template<typename T>
 typename Liste<T>::iterator Liste<T>::erase(iterator pos) {
     assert(pos != end());
     Chainon* node = pos.m_current;
     iterator ret(node->next(), m_sentinel);
     node->detach();
     delete node;
     m_size--;
     return ret;
 }
#ifndef VECTEUR_H
#define VECTEUR_H
#include <iostream>
#include <utility>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <concepts>  
#ifdef __GNUC__
    #define RESTRICT __restrict__
#else
    #define RESTRICT __restrict
#endif

template<typename T>
class Vecteur {
public :
    // ============== Alias ======================

    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;
    using iterator        = T*;
    using const_iterator  = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
private:
    size_type N;
    pointer v;
public:
    // ============== Constructeurs ==============

    explicit Vecteur(size_type N = 3, value_type init_val = value_type{}) : N(N) {
        assert(N > 0);
        v = new value_type[N];
        std::fill(v, v + N, init_val);
    }

    template<typename U>
    requires std::is_convertible_v<U, T>
    Vecteur(const Vecteur<U>& other) : N(other.dimensions()), v(new T[other.dimensions()]) {
        std::copy(other.begin(), other.end(), v);
    }

    Vecteur(const Vecteur& other) : N(other.N) {
        v = new value_type[N];
        std::copy(other.v, other.v + N, v);
    }

    Vecteur(Vecteur&& other) noexcept : N(other.N), v(other.v) {
        other.N = 0;
        other.v = nullptr;
    }

    ~Vecteur() noexcept {
        delete[] v;
    }

    Vecteur& operator=(const Vecteur& other) {
        if (this == &other) return *this;
        if (N != other.N) {
            delete[] v;
            N = other.N;
            v = new value_type[N];
        }
        std::copy(other.v, other.v + N, v);
        return *this;
    }

    Vecteur& operator=(Vecteur&& other) noexcept {
        if (this != &other) {
            delete[] v;
            N = other.N;
            v = std::exchange(other.v, nullptr);
            other.N = 0;
        }
        return *this;
    }

    reference operator[](size_type index) noexcept {
        check_index(index);
        return v[index];
    }

    const_reference operator[](size_type index) const noexcept {
        check_index(index);
        return v[index];
    }

    template<typename T2>
    requires (requires(value_type a, T2 b) { a + b; } && std::convertible_to<decltype(std::declval<value_type>() + std::declval<T2>()), value_type>)
    Vecteur operator+(const Vecteur<T2>& vecteur2) const {
        assert(N == vecteur2.dimensions());
        Vecteur res(N, value_type{});
        for (size_type i = 0; i < N; i++) res[i] = v[i] + vecteur2[i];
        return res;
    }

    value_type get(size_type index) const noexcept {
        check_index(index);
        return v[index];
    }

    void set(size_type index, const_reference value) noexcept {
        check_index(index);
        v[index] = value;
    }

    size_type dimensions() const noexcept {
        return N;
    }

    void afficherVecteur(std::ostream& out = std::cout) {
        out << "[";
        for (size_type i = 0; i < N; i++) {
            out << v[i];
            if (i < N - 1) out << ", ";
        }
        out << "]\n";
    }

    // ============ STL ==============
    reference at(size_type index) {
        if (index >= N) throw std::out_of_range("Index out of range in Vecteur::at()");
        return v[index];
    }

    const_reference at(size_type index) const {
        if (index >= N) throw std::out_of_range("Index out of range in Vecteur::at()");
        return v[index];
    }

    constexpr size_type size() const noexcept { return dimensions();}
    constexpr bool empty() const noexcept {return dimensions() == 0;}

    const_reference front() const noexcept {return *v;}
    reference front() noexcept {return *v;}

    const_reference back() const noexcept {return *(v+N-1);}
    reference back() noexcept {return *(v+N-1);}

    void swap(Vecteur<T>& other) noexcept {
        std::swap(N, other.N);
        v = std::exchange(other.v, v);
    }
    // ============= ITERATEUR =========
    iterator begin() noexcept {return v;}
    const_iterator begin() const noexcept {return v;}
    const_iterator cbegin() const noexcept {return v;}

    iterator end() noexcept {return v+N;}
    const_iterator end() const noexcept {return v+N;}
    const_iterator cend() const noexcept {return v+N;}

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }
private:
    inline void check_index(size_type index) const noexcept {
        assert(index < N);
    }
};

template<typename T>
void swap(Vecteur<T>& v1, Vecteur<T>& v2) noexcept {
    v1.swap(v2);
}
template<typename T1, typename T2>
requires requires(T1 a, T2 b) { { a + b }; { a * b + a + b }; }
decltype(std::declval<T1>()*std::declval<T2>() + std::declval<T1>() + std::declval<T2>()) operator*(const Vecteur<T1> &v1, const Vecteur<T2> &v2) noexcept{
    assert(v1.dimensions() == v2.dimensions());
    size_t size = v1.dimensions();
    decltype(std::declval<T1>()*std::declval<T2>() + std::declval<T1>() + std::declval<T2>()) res = v1[0] * v2[0];
    for(size_t i = 1; i < size; i++)res += v1[i]*v2[i];
    return res;
}

template<typename V>
std::ostream & operator<<(std::ostream & out, const Vecteur<V> & v){
    out << "[";
    size_t dim = v.dimensions();
    for (size_t i = 0; i < dim; i++) {
        out << v[i];
        if (i < dim - 1) out << ", ";
    }
    out << "]\n";
    return out;
}

template<typename V>
std::istream & operator>>(std::istream & in, Vecteur<V> & v) {
    for (size_t i = 0; i < v.dimensions(); i++) {
        in >> v[i];
    }
    return in;
}

template<typename V>
Vecteur<V> lireVecteur(std::istream & in = std::cin) {
    size_t n;
    in >> n; 
    Vecteur<V> v(n);
    for (size_t i = 0; i < n; i++)in >> v[i];
    return v;
}

template<typename V>
Vecteur<V> add(const Vecteur<V> * RESTRICT vecteur1, const Vecteur<V> * RESTRICT vecteur2) {
    assert(vecteur1->dimensions() == vecteur2->dimensions());
    return *vecteur1 + *vecteur2;
}
#endif 
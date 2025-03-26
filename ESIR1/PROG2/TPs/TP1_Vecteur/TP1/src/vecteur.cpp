/** \brief Ce fichier doit contenir l'ensemble des implémentations
relatives à la classe vecteur et aux fonctionnalités la concernant */
#include <cassert>
#include <iostream>
#include <algorithm>
#include <immintrin.h>
#include <new>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include "vecteur.h"
#define endl "\n" // Pour pas flush le buffer à chaque fois, ça améliore les performances
/**
 * Macro RESTRICT pour indiquer l'absence d'aliasing
 * L'aliasing est l'effet de deux ou plusieurs pointeurs qui pointent vers la même zone mémoire
 * Cela peut poser des problèmes de performance en cas de modification de la valeur pointée
 * __restrict__ : pour GCC
 * __restrict : pour les autres compilateurs
 */
#ifdef __GNUC__
    #define RESTRICT __restrict__
#else
    #define RESTRICT __restrict
#endif

// Implémentation des méthodes de la classe vecteur

  /*==============================================================*/
 /*                  METHODES PUBLIQUES                          */
/*==============================================================*/

// ================== Constructeurs ==================

// Constructeur par défaut 
// Complexité : O(N)
explicit Vecteur::Vecteur(int N, float init_val) : N(N){
    //if(N<=0) throw std::invalid_argument("Invalid size");
    assert(N > 0);
    // Allocation alignée sur 32 octets pour les instructions SIMD sur CPU Intel AVX
    // Allocation alignée sert à garantir que l'adresse de départ de l'allocation est un multiple de 32 octets
    // pour éviter les erreurs de segmentation lors de l'utilisation des instructions SIMD
    v = new (std::align_val_t(32))float[N];
    #ifdef __AVX__
        __m256 fill = _mm256_set1_ps(init_val);
        int i = 0;
        for (; i <= N - 8; i += 8)mm256_store_ps(v + i, fill);
        for (; i < N; i++)v[i] = init_val;
    #else
        std::fill(v, v + N, init_val); // Remplissage du vecteur avec la valeur init_val, fonction de la STL
    #endif
    #ifdef DEBUG
        std::cout << "Construction par défaut du Vecteur(" << N << ", " << init_val << ")" << endl;
    #endif
}

// Constructeur par copie
// Complexité : O(N)
Vecteur::Vecteur(const Vecteur &other) : N(other.N){
    v = new (std::align_val_t(32))float[N];
    #ifdef __AVX__
        int i = 0;
        for (; i <= N - 8; i += 8) { // Copie par blocs de 8 éléments pour les instructions SIMD
            __m256 a = _mm256_load_ps(other.v + i); // Chargement de 8 éléments du vecteur other
            _mm256_store_ps(v + i, a); // Stockage des éléments dans le vecteur courant
        }
        for (; i < N; i++)v[i] = other.v[i]; // Compléter la copie
    #else
        std::copy(other.v, other.v + N, v);
    #endif
    #ifdef DEBUG
        std::cout << "Construction par copie du Vecteur(" << N << ")" << endl;
    #endif
}

// Constructeur de déplacement
// Complexité : O(1)
Vecteur::Vecteur(Vecteur&& other) noexcept : N(other.N), v(other.v) {
    other.N = 0;
    other.v = nullptr;
    #ifdef DEBUG
        std::cout << "Construction par déplacement du Vecteur(" << N << ")" << endl;
    #endif
}

// ============== Destructeur ==============
// Complexité : O(1)
Vecteur::~Vecteur() noexcept{
    ::operator delete[](v, std::align_val_t(32)); // Désallocation alignée sur 32 octets
    #ifdef DEBUG
        std::cout << "Destruction du vecteur de taille : " << this->N << endl;
    #endif
}

// ============== Opérateurs ==============
// Surchage Opérateur d'affectation par copie
// Complexité : O(N)
Vecteur &Vecteur::operator=(const Vecteur &vecteur){
    if(this == &vecteur)return *this;
    if(N != vecteur.N){
        ::operator delete[] (v, std::align_val_t(32));
        N = vecteur.N;
        v = new(std::align_val_t(32))float[N];
    }
    std::copy(vecteur.v, vecteur.v + N, v);
    return *this;
}

// Surchage Opérateur [] pour accès en écriture
// Complexité : O(1)
float &Vecteur::operator[](int index) noexcept{
    check_index(index);
    return v[index];
}

// Surchage Opérateur [] pour accès en lecture
// Complexité : O(1)
const float &Vecteur::operator[](int index) const noexcept{
    check_index(index);
    return v[index];
}

// Surchage Opérateur + pour l'addition de deux vecteurs
// Complexité : O(N)
Vecteur Vecteur::operator+(const Vecteur &vecteur2) const {
    return add(this, &vecteur2);
}

// Opérateur d'affectation par déplacement
// Complexité : O(1)
Vecteur& Vecteur::operator=(Vecteur&& other) noexcept { // noexcept pour indiquer que la fonction ne lance pas d'exception
    if (this != &other) {
        ::operator delete[](v, std::align_val_t(32));
        N = other.N;
        v = other.v;
        other.N = 0;
        other.v = nullptr;
    }
    return *this;
}

// ================== Méthodes ==================

// Retourne la valeur de l'élément à l'index donné
// Complexité : O(1)
float Vecteur::get(int index) const noexcept{
    check_index(index);
    return v[index];
}

// Modifie la valeur de l'élément à l'index donné
// Complexité : O(1)
void Vecteur::set(int index, float value) noexcept{
    check_index(index);
    v[index] = value;
}

// Retourne la taille du vecteur
// Complexité : O(1)
int Vecteur::dimensions() const noexcept{
    return N;
}

// Affiche le vecteur dans le flux de sortie out
// Complexité : O(N)
void Vecteur::afficherVecteur(const Vecteur *vec, std::ostream &out) {
    out << "[";
    int dim = vec->dimensions();
    for (int i = 0; i < dim; i++){
        out << vec->get(i);
        if(i < dim - 1)out << ", ";
    }
    out << "]\n";
}

  /*==============================================================*/
 /*                  METHODES PRIVEES                            */
/*==============================================================*/

// Complexité : O(1)
inline void Vecteur::check_index(int index) const noexcept{ // inline pour éviter l'appel de la fonction, le code est inséré directement à l'endroit de l'appel
    //if(index < 0 || index >= N)throw std::out_of_range("Index out of range");
    assert(index >= 0 && index < N);
}

  /*==============================================================*/
 /*                          FONCTIONS                           */
/*==============================================================*/

// ================== Opérateur ==================
// Surchage Opérateur * pour le produit scalaire de deux vecteurs
// Complexité : O(N)
float operator*(const Vecteur& v1, const Vecteur& v2) noexcept {
    //if(v1.dimensions() != v2.dimensions()) throw std::invalid_argument("Vectors must have the same size");
    assert(v1.dimensions() == v2.dimensions());
    int size = v1.dimensions();
    float sum = 0.0f;
    #ifdef __AVX__
        __m256 acc = _mm256_setzero_ps(); // Initialisation du vecteur à zéro
        int i = 0; 
        for (; i <= size - 8; i += 8) { // Calcul par blocs de 8 éléments pour les instructions SIMD
            __m256 a = _mm256_load_ps(&v1[i]); // Chargement de 8 éléments du vecteur v1
            __m256 b = _mm256_load_ps(&v2[i]); // Chargement de 8 éléments du vecteur v2
            #ifdef __FMA__ // Utilisation de l'instruction FMA (Fused Multiply-Add)
                acc = _mm256_fmadd_ps(a, b, acc); // Fused Multiply-Add
            #else
                __m256 prod = _mm256_mul_ps(a, b); // Produit élément par élément
                acc = _mm256_add_ps(acc, prod); // Accumulation des produits
            #endif
        }
        float buffer[8] __attribute__((aligned(32))); // Buffer pour stocker les éléments du vecteur
        _mm256_store_ps(buffer, acc); // Stockage des éléments du vecteur dans le buffer
        for (int j = 0; j < 8; j++)sum += buffer[j]; // Calcul de la somme
        for (; i < size; i++)sum += v1[i] * v2[i]; // Compléter le calcul
    #else
        for (int i = 0; i < size; i++)sum += v1[i] * v2[i];
    #endif
    return sum;
}

// Surcharge Opérateur << pour afficher le vecteur dans le flux de sortie out
// Complexité : O(N)
std::ostream & operator<<(std::ostream &out, const Vecteur &v) {
    out << "[";
    int dim = v.dimensions();
    for (int i = 0; i < dim; i++) {
        out << v[i];
        if (i < dim - 1) out << ", ";
    }
    out << "]\n";
    return out;
}

// Surcharge Opérateur >> pour lire le vecteur depuis le flux d'entrée in
// Complexité : O(N)
std::istream & operator>>(std::istream &in, Vecteur &v) {
    int dim = v.dimensions();
    for (int i = 0; i < dim; i++) {
        std::cout << "Entrez la valeur pour l'indice " << i << " : ";
        in >> v[i];
    }
    return in;
}

// ================== Fonctions ==================

// Fonction pour lire un vecteur depuis le flux d'entrée in
// Complexité : O(N)
Vecteur * lireVecteur(std::istream &in) {
    std::cout << "Entrez la taille du vecteur : ";
    int size;
    in >> size;
    assert(size > 0);
    //if (size <= 0)throw std::invalid_argument("Taille invalide");
    Vecteur *vec = new Vecteur(size);
    for(int i = 0; i < size; i++){
        std::cout << "Entrez la valeur pour l'indice " << i << " : ";
        in >> (*vec)[i];
    }
    return vec;
}

// Fonction pour ajouter deux vecteurs
// RESTRICT pour indiquer l'absence d'aliasing
// Complexité : O(N)
Vecteur add(const Vecteur *RESTRICT v1, const Vecteur *RESTRICT v2) {
    assert(v1->dimensions() == v2->dimensions());
    //if(v1->dimensions() != v2->dimensions()) [[unlikely]]
    //     throw std::invalid_argument("Vectors must have the same size");
    
    int size = v1->dimensions();
    Vecteur result(size, 0.0f);

    #ifdef __AVX__
        int i = 0;
        for (; i <= size - 8; i += 8) { // Calcul par blocs de 8 éléments pour les instructions SIMD
            __m256 a = _mm256_load_ps(&(*v1)[i]); // Chargement de 8 éléments du vecteur v1
            __m256 b = _mm256_load_ps(&(*v2)[i]); // Chargement de 8 éléments du vecteur v2
            __m256 sum = _mm256_add_ps(a, b); // Addition élément par élément
            _mm256_store_ps(&result[i], sum); // Stockage des éléments du vecteur résultat
        }
        for (; i < size; i++)result[i] = (*v1)[i] + (*v2)[i]; // Compléter le calcul
    #else
        for (int i = 0; i < size; i++) result[i] = (*v1)[i] + (*v2)[i];
    #endif
    return result;
}

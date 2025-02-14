/** \brief Ce fichier doit contenir la déclaration de la classe vecteur
    Attention, elle ne doit contenir aucune implémentation de méthode / fonction
*/
#include <vector>
#include <iostream>
#ifndef _VECTEUR_H
#define _VECTEUR_H
#ifdef __GNUC__
    #define RESTRICT __restrict__
#else
    #define RESTRICT __restrict
#endif

// Déclaration de la classe vecteur
class Vecteur {
private :
    // attributs
    int N;
    float *v;
public :
    // prototypes des constructeurs et autres méthodes publiques

    // ============== Constructeurs ==============

    /**
     * \brief Constructeur par défaut de la classe vecteur
     * \param N La taille du vecteur (3 par défaut)
     * \param inital_val La valeur par défaut des éléments du vecteur (0.0 par défaut)
     * \return Un vecteur de taille N avec des éléments initialisés à init_val
     * utilisation de explicit pour éviter les conversions implicites
     */
   explicit Vecteur(int N = 3, float init_val = 0.0);

   /**
    * \brief Constructeur par copie de la classe vecteur (copie en profondeur)
    * \param vecteur Le vecteur à copier (vecteur par référence)
    * \return Un vecteur identique à vecteur
    */
    Vecteur(const Vecteur &vecteur);

    /**
     * \brief Constructeur de déplacement de la classe vecteur, afin d'éviter la copie inutile de données lors des retours de fonctions ou des affectations
     * \param vecteur Le vecteur à déplacer (vecteur par référence)
     * \return Un vecteur identique à vecteur
     */
    Vecteur(Vecteur &&other) noexcept;

    // ============== Destructeur ==============
    /**
     * \brief Destructeur de la classe vecteur
     * \return void
     */
    ~Vecteur() noexcept;

    // ============== Opérateurs ==============
    /**
     * \brief Opérateur d'affectation par copie
     * \param vecteur Le vecteur à copier (vecteur par référence)
     * \return Le vecteur courant après copie
     */
    Vecteur &operator=(const Vecteur &vecteur);

    /**
     * \brief Surcharge de l'opérateur [] pour accès en écriture
     * \param index L'index de l'élément
     * \return La valeur de l'élément à l'index donné
     */
    float &operator[](int index) noexcept;

    /**
     * \brief Surcharge de l'opérateur [] pour accès en lecture
     * \param index L'index de l'élément
     * \return La valeur de l'élément à l'index donné (constante)
     */
    const float& operator[](int index) const noexcept;

    /**
     * \brief Surcharge de l'opérateur + pour l'addition de deux vecteurs
     * \param vecteur2 Le vecteur à ajouter
     * \return La somme des deux vecteurs
     */
    Vecteur operator+(const Vecteur &vecteur2) const;

    /**
     * \brief Surchage de l'opérateur d'affecation par déplacement
     * \param other Le vecteur à déplacer
     * \return Le vecteur courant après déplacement
     */
    Vecteur& operator=(Vecteur &&other) noexcept;

    // ============== Méthodes ==============

    /**
     * \brief Retourne la valeur de l'élément à l'index donné
     * \param index L'index de l'élément
     * \return La valeur de l'élément à l'index donné
     */
    float get(int index) const noexcept;

    /**
     * \brief Modifie la valeur de l'élément à l'index donné
     * \param index L'index de l'élément
     * \param value La nouvelle valeur de l'élément
     * \return void
     */
    void set(int index, float value) noexcept;

    /**
     * \brief Retourne la taille du vecteur
     * \return La taille du vecteur
     */
    int dimensions() const noexcept;

    /**
     * \brief Affiche le vecteur dans le flux de sortie out
     * \param v Le vecteur à afficher
     * \param out Le flux de sortie
     * \return void
     */
    void afficherVecteur(const Vecteur * v, std::ostream & out = std::cout);

private :
    // méthodes privées d'implémentation (si besoin)

    /**
     * \brief Vérifie que l'index est valide en lançant une exception si ce n'est pas le cas (assert pour correspondre à l'énoncé, même si c'est moins propre qu'une exception)
     * \param index L'index à vérifier
     * \return void 
     */
    inline void check_index(int index) const noexcept;
};
// Prototypes des fonctions
/**
 * Les fonctions suivantes ne sont pas implémentées comme des méthodes afin de pouvoir les utiliser sans instancier un objet de la classe Vecteur
 */

// ================== Opérateur ==================
/**
 * \brief Surcharge de l'opérateur * pour le produit scalaire de deux vecteurs
 * \param v1 Le premier vecteur
 * \param v2 Le deuxième vecteur
 * \return Le produit scalaire des deux vecteurs
 */
float operator*(const Vecteur &v1, const Vecteur &v2) noexcept;

/**
 * \brief Surcharge de l'opérateur << pour afficher un vecteur dans un flux de sortie
 * \param out Le flux de sortie
 * \param v Le vecteur à afficher
 * \return Le flux de sortie
 */
std::ostream & operator<<(std::ostream & out, const Vecteur & v);

/**
 * \brief Surcharge de l'opérateur >> pour lire un vecteur depuis un flux d'entrée
 * \param in Le flux d'entrée
 * \param v Le vecteur à lire
 * \return Le flux d'entrée
 */
std::istream & operator>>(std::istream & in, Vecteur & v);

// ================== Fonctions ==================
/**
 * \brief Initialise un vecteur depuis un flux d'entrée
 * \param in Le flux d'entrée
 * \return Un pointeur vers le vecteur initialisé
 */
Vecteur * lireVecteur(std::istream &in = std::cin);

/**
 * \brief Additionne deux vecteurs et retourne le résultat
 * \param vecteur1 Le premier vecteur
 * \param vecteur2 Le deuxième vecteur
 * \return La somme des deux vecteurs
 */
Vecteur add(const Vecteur *RESTRICT vecteur1, const Vecteur *RESTRICT vecteur2);
#endif
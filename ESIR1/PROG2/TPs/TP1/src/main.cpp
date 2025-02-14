#include <iostream>
#include "vecteur.h"
using std::cin;
using std::cout;
using std::cerr;
#define endl "\n"
int main() {
    Vecteur *vect = nullptr;
    Vecteur *vect2 = nullptr;
    try {
        vect = lireVecteur(cin);
        cout << "Vecteur saisi : ";
        cout << *vect;

        int index;
        float nouvelleValeur;
        cout << "Entrez l'indice de la coordonnée à modifier : ";
        cin >> index;
        cout << "Entrez la nouvelle valeur : ";
        cin >> nouvelleValeur;
        (*vect)[index] = nouvelleValeur;
        cout << "Vecteur modifié : ";
        cout << *vect;

        cout << "Entrer la taille du deuxième vecteur : ";
        int size;
        cin >> size;
        vect2 = new Vecteur(size);
        cin >> *vect2;
        cout << "Deuxième vecteur saisi : ";
        cout << *vect2;

        Vecteur vect3 = *vect + *vect2;
        Vecteur somme = vect3 + *vect2 + *vect;
        cout << "Vecteur3: " << vect3;
        cout << "Somme: " << somme;
        cout << "Produit scalaire: " << (vect3 * somme) << endl;
    }
    catch (const std::exception &e) {
        cerr << "Erreur : " << e.what() << endl;
    }
    delete vect;
    delete vect2;
    return 0;
}
#ifndef COPIER_H
#define COPIER_H
#include <functional>
#include <concepts>
#include <type_traits>
#include "liste.hpp"
/**
   3.2.1 chercher une valeur dans une liste triée, nom de la fonction fonction : chercherTri
   @param premier : itérateur positionné sur le premier élément
   @param dernier : itérateur positionné après le dernier élément
   @param x : valeur à chercher
   @return position du premier élément de valeur >= x
   ou end() si un tel élément n'existe pas
 */
template <class IT, class T, class Compare = std::less<T>>
requires std::predicate<Compare, decltype(*std::declval<IT>()), T>
IT chercherTri(IT premier, IT dernier, const T& x, Compare comp = Compare{}){
   while(premier != dernier){
      if(!comp(*premier,x))return premier;
      premier++;
   }
   return dernier;
}


/**
   3.2.2 créer une copie triée par valeurs croissantes d'une liste, nom de la fonction fonction : copierTri
   @param l : liste à copier
   @return liste triée
*/

template<typename T>
Liste<T> copierTri(const Liste<T>& l){
   Liste<T> res;
   for(auto it = l.begin(); it != l.end(); ++it)res.insert(chercherTri(res.begin(), res.end(), *it), *it);
   return res;
}

#endif
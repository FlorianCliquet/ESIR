#ifndef __COMMON_P1_H__			// -*- c++ -*-
#define __COMMON_P1_H__

#include <deque>
#include <gtest/gtest.h>
//#include <cstdlib>
#include "Liste.h"

enum Position { front, alea, back };

//------------------------------------------------------------------------
// fonctions utilitaires
//------------------------------------------------------------------------

// ajouter des élts dans un tableau et une liste
// avec push_front ou push_back
void
ajouter_elts(
	     Liste<double> & liste,
	     std::deque<double> & array,
	     Position ici = alea
	     );

// ajouter des éléments dans un tableau
void
ajouter_elts(
	     std::deque<double> & array
	     );

// comparer les élts d'une liste et ceux d'un deque
// vide la liste de son contenu
// requiert size, front, pop_front, back, pop_back
template <class T>
void
list_equals_deque(
		  Liste<T> & list,
		  const std::deque<T> & array,
		  Position ici
		  )
{
  unsigned int nb = array.size();
  EXPECT_EQ(
	    (unsigned int) nb,
	    (unsigned int) list.size())
    << "Erreur taille liste";
  unsigned int ideb = 0, ifin = array.size() - 1;
  while (! list.empty())
  {
    EXPECT_EQ(
	      (unsigned int) nb,
	      (unsigned int) list.size())
      << "Erreur taille liste";

    // ôter soit en tête, soit en queue
    bool retraitTete = (ici == front) || (ici == alea && rand() % 2 == 0);
    if (retraitTete) {
      EXPECT_EQ(
		array[ideb],
		list.front())
	<< "Erreur élément de rang " << ideb;
      list.pop_front();
      ++ideb;
    }
    else {
      EXPECT_EQ(
		array[ifin],
		list.back())
	<< "Erreur élément de rang " << ifin;
      list.pop_back();
      --ifin;
    }
    nb -= 1;
  }
}

#endif // __COMMON_P1_H__

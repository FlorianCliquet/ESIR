#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>
#include "Liste.h"
#include "common_p1.h"

//------------------------------------------------------------------------
// fonctions utilitaires
//------------------------------------------------------------------------

// ajouter des élts dans un tableau et une liste
// avec push_front ou push_back
void
ajouter_elts(
	     Liste<double> & liste,
	     std::deque<double> & array,
	     Position ici
	     )
{
  const int array_size = 100 + rand() % 100;
  for (int i = 0; i < array_size; ++i) {
    double x = 5 + drand48();
    bool ajoutTete = (ici == front) || (ici == alea && rand() % 2 == 0);
    if (ajoutTete) {
      // ajout en tête
      array.push_front(i * x * x);
      liste.push_front(i * x * x);
    }
    else {
      // ajout en fin
      array.push_back(i * x + 1);
      liste.push_back(i * x + 1);
    }
  }
}

// ajouter des éléments dans un tableau
void
ajouter_elts(
	     std::deque<double> & array
	     )
{
  const int array_size = 100 + rand() % 100;
  for (int i = 0; i < array_size; ++i) {
    array.push_back(5 + drand48());
  }
}

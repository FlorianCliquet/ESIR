#include "mixage/filtre/additionneur.hpp"

#include <cassert>

additionneur::additionneur(const unsigned int nb_entrees)
    : filtre_base(1, nb_entrees) {}

void additionneur::calculer() {
  if(!yaDesEchantillons())
    return;
  double res = 0;
  for (size_t i = 0; i < filtre_base::nbEntrees(); i++)
    res += filtre_base::getEntree(i)->extraire();
  filtre_base::getSortie(0)->inserer(res);
}
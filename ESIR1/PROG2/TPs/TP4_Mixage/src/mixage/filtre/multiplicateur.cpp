#include "mixage/filtre/multiplicateur.hpp"

#include <cassert>

#include "mixage/filtre/filtre_base.hpp"

multiplicateur::multiplicateur() : filtre_base(1, 2) {}

void multiplicateur::calculer() {
  if(!yaDesEchantillons())
    return;
  double res = getEntree(0)->extraire() * getEntree(1)->extraire();
  getSortie(0)->inserer(res);
}
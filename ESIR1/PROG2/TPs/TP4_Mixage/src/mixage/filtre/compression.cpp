#include "mixage/filtre/compression.hpp"
#include "mixage/filtre/filtre_base.hpp"
#include <cassert>
#include <cmath>

compression::compression(const double force) : filtre_base(1, 1), force_(force) {
  assert(force_ > 0 && force <= 1 && "La force de compression doit être comprise entre ]0;1]");
}

double compression::signe(const double x) { return (x >= 0) ? 1 : -1; }

void compression::calculer() {
  if(!yaDesEchantillons())
    return;
  
  double curr = filtre_base::getEntree(0)->extraire();
  filtre_base::getSortie(0)->inserer(signe(curr) *
                                     std::pow(std::abs(curr), force_));
}
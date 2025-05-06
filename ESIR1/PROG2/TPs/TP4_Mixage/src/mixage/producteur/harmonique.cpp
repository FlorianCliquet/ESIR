#include "mixage/producteur/harmonique.hpp"

#include <cmath>
#include <iostream>
#include "mixage/utils/constantes.hpp"

harmonique::harmonique(int frequence, double phase)
    : producteur_base(1), frequence_(frequence), phase_(phase), i_(0) {}

double harmonique::genererEchantillon() const {
  double t = static_cast<double>(i_) / MixageSonore::frequency;
  return std::sin(t * 2.0 * MixageSonore::pi * frequence_ + phase_);
}

void harmonique::calculer() {
  ++i_;
  auto sortie = getSortie(0);
  if (!sortie) {
    std::cout << "Error: getSortie(0) is invalid!" << std::endl;
  }
  getSortie(0)->inserer(genererEchantillon());
}
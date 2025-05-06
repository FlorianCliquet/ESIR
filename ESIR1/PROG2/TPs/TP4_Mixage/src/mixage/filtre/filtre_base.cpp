#include "mixage/filtre/filtre_base.hpp"

filtre_base::filtre_base(const unsigned int nb_output, const unsigned int nb_input)
    : producteur_base(nb_output), consommateur_base(nb_input) {}

unsigned int filtre_base::nbEntrees() const {
  return consommateur_base::nbEntrees();
}

const std::shared_ptr<flot>& filtre_base::getEntree(unsigned int numentre) const {
  return consommateur_base::getEntree(numentre);
}

void filtre_base::connecterEntree(const std::shared_ptr<flot>& f, unsigned int numentre) {
  consommateur_base::connecterEntree(f, numentre);
}

bool filtre_base::yaDesEchantillons() const {
  return consommateur_base::yaDesEchantillons();
}

unsigned int filtre_base::nbSorties() const {
  return producteur_base::nbSorties();
}

const std::shared_ptr<flot>& filtre_base::getSortie(unsigned int numsortie) const {
  return producteur_base::getSortie(numsortie);
}

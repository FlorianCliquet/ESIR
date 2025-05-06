#include "mixage/producteur/producteur_base.hpp"

#include <memory>

#include "mixage/flot/imp_flot.hpp"
// Constructeur : initialise toutes les sorties avec un shared_ptr vers un flot vide.
producteur_base::producteur_base(unsigned int nb_sortie)
    : sorties_(nb_sortie, std::make_shared<imp_flot>()) {}

void producteur_base::connecterSortie(const std::shared_ptr<flot> &f,
                                      unsigned int indice_sortie) {
  sorties_.at(indice_sortie) = f;
}

unsigned int producteur_base::nbSorties() const { return sorties_.size(); }

const std::shared_ptr<flot> &
producteur_base::getSortie(unsigned int numsortie) const {
  return sorties_.at(numsortie);
}

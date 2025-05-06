#include "mixage/consommateur/consommateur_base.hpp"

#include <algorithm>

#include "mixage/flot/imp_flot.hpp"
consommateur_base::consommateur_base(unsigned int nb_entrees)
    : entrees_(nb_entrees, std::make_shared<imp_flot>()) {}

unsigned int consommateur_base::nbEntrees() const {
  return entrees_.size();
}

const std::shared_ptr<flot>& consommateur_base::getEntree(unsigned int numentree) const {
  return entrees_.at(numentree);
}

void consommateur_base::connecterEntree(const std::shared_ptr<flot>& f, unsigned int numentree) {
  entrees_.at(numentree) = f;
}

bool consommateur_base::yaDesEchantillons() const {
  // Vérifie si toutes les entrées de type flot ont des échantillons.
  // La méthode std::all_of parcourt toutes les entrées et applique une lambda
  // qui retourne `true` si l'entrée n'est pas vide (i.e., qu'elle contient des échantillons).
  return std::all_of(entrees_.begin(), entrees_.end(),
                     [](const std::shared_ptr<flot>& f) { return !f->vide(); });
}

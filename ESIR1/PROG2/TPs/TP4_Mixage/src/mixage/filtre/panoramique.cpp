#include "mixage/filtre/panoramique.hpp"

panoramique::panoramique() : filtre_base(2, 1) {};

void panoramique::calculer() {
  if(!yaDesEchantillons())
    return;
  double curr = filtre_base::getEntree(0)->extraire();
  double sortie_0 = (curr + 1) / 2; ///< Canal gauche
  double sortie_1 = 1 - sortie_0;    ///< Canal droit

  filtre_base::getSortie(0)->inserer(sortie_0);
  filtre_base::getSortie(1)->inserer(sortie_1);
}
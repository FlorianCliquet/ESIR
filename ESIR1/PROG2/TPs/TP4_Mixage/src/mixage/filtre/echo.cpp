#include "mixage/filtre/echo.hpp"

#include "mixage/utils/constantes.hpp"
echo::echo(double decalage_temporel, double attenuation)
    : filtre_base(1, 1),
      buffer_(
          static_cast<size_t>((decalage_temporel * MixageSonore::frequency)) *
          0.001),
      attenuation_(attenuation), decalage_temporel_(decalage_temporel),
      temps_courant_(0) {}

void echo::calculer() {
    if(!yaDesEchantillons())
      return;
    
    double entree = filtre_base::getEntree(0)->extraire();
    double entree_decale = (temps_courant_ >= decalage_temporel_) ? buffer_.read() : 0.0;
    filtre_base::getSortie(0)->inserer(entree + entree_decale * attenuation_);
    buffer_.write(entree);
    temps_courant_ += 1000.0 / MixageSonore::frequency;
}

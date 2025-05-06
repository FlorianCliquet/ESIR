#include "mixage/filtre/fade.hpp"

#include "mixage/utils/constantes.hpp"

fade::fade(double temps_debut, double duree_fondu, double volume_depart, double volume_cible)
    : filtre_base(1, 1), volume_depart_(volume_depart), volume_cible_(volume_cible),
      valeur_actuelle_(volume_depart), temps_ecoule_(0), duree_fondu_(duree_fondu),
      temps_debut_(temps_debut) {}

double fade::CalculerVolumeActuel() const {
  if (temps_ecoule_ < temps_debut_)
    return volume_depart_;  // Pas encore atteint le temps de début, volume de départ.
  if (temps_ecoule_ > temps_debut_ + duree_fondu_)
    return volume_cible_;  // Dépasse la durée du fondu, volume cible atteint.
  
  // Calcule la progression du fondu.
  double progression = (temps_ecoule_ - temps_debut_) / duree_fondu_;
  return volume_depart_ + (volume_cible_ - volume_depart_) * progression;  // Calcul du volume actuel.
}

void fade::calculer() {
  if(!yaDesEchantillons())
    return;
  // Récupère l'échantillon actuel depuis l'entrée.
  double echantillon_actuel = filtre_base::getEntree(0)->extraire();

  // Met à jour la valeur du volume en fonction du temps écoulé.
  valeur_actuelle_ = CalculerVolumeActuel();

  // Applique l'effet de fondu au volume de l'échantillon.
  echantillon_actuel *= valeur_actuelle_;

  // Incrémente le temps écoulé en fonction de la fréquence.
  temps_ecoule_ += 1.0 / MixageSonore::frequency;

  // Insère l'échantillon traité dans la sortie.
  filtre_base::getSortie(0)->inserer(echantillon_actuel);
}

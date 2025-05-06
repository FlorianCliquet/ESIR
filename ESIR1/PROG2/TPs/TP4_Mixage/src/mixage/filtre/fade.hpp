#ifndef __MIXAGE__FILTRE__FADE_H
#define __MIXAGE__FILTRE__FADE_H

#include "mixage/filtre/filtre_base.hpp"

#include <cassert>

/// \class fade
/// \brief Classe représentant un effet de fondu pour le volume.
///
/// L'effet de fondu modifie progressivement le volume d'un échantillon,
/// passant d'un volume de départ à un volume cible sur une durée spécifiée,
/// à partir d'un moment donné. L'effet de fondu est appliqué aux échantillons
/// en entrée.
///
/// \author  Florian Cliquet
/// \date    10/04/2025
class fade : public filtre_base {
 private:
  double volume_depart_;  ///< Volume de départ pour le fondu.
  double volume_cible_;    ///< Volume cible pour le fondu.
  double valeur_actuelle_;  ///< Valeur actuelle du volume pendant le fondu.
  double temps_ecoule_;   ///< Temps écoulé (en ms) depuis le début du fondu.
  double duree_fondu_;  ///< Durée du fondu en millisecondes.
  double temps_debut_;     ///< Temps de début du fondu en millisecondes.

  /// \brief Calcule la valeur actuelle du volume en fonction du temps écoulé.
  /// \return La valeur actuelle du volume en fonction du temps écoulé.
  double CalculerVolumeActuel() const;

 public:
  /// \brief Constructeur pour initialiser les paramètres du fondu.
  /// \param temps_debut Le temps de début du fondu (en ms).
  /// \param duree_fondu La durée du fondu (en ms).
  /// \param volume_depart Le volume de départ pour le fondu.
  /// \param volume_cible Le volume cible pour le fondu.
  explicit fade(double temps_debut, double duree_fondu, double volume_depart, double volume_cible);

  /// \brief Calcule l'effet de fondu et l'applique à l'échantillon en entrée.
  void calculer() override;
};

#endif // __MIXAGE__FILTRE__FADE_H

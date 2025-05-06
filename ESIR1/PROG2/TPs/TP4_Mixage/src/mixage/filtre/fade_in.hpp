#ifndef __MIXAGE__FILTRE__FADIN_IN__H
#define __MIXAGE__FILTRE__FADIN_IN__H

#include "mixage/filtre/filtre_compose.hpp"

#include "mixage/filtre/fade.hpp"

/// \class fade_in
/// \brief Classe représentant un effet de fondu à l'ouverture utilisant la
/// classe fade.
///
/// Cette classe applique un effet de fondu du volume allant de 0 à 1 pendant
/// une durée spécifiée, à partir d'un moment donné. Elle utilise la classe
/// fade pour le calcul du volume.
///
/// \author  Florian Cliquet
/// \date    10/04/2025
class fade_in : public filtre_compose {
 public:
  /// \brief Constructeur de la classe fade_in.
  /// \param duree_fondu La durée du fondu en millisecondes.
  /// \param temps_debut Le temps de début du fondu en millisecondes.
  explicit fade_in(int duree_fondu, int temps_debut)
      : filtre_compose(1, 1) {
    // Crée un effet de fondu allant de 0 à 1 avec la durée et le début spécifiés.
    auto filtre_fondu = std::make_shared<fade>(temps_debut, duree_fondu, 0, 1);
    ajoutComposant(filtre_fondu);
    ajoutLienInput(0, filtre_fondu, 0);
    ajoutLienOutput(0, filtre_fondu, 0);
  }
};

#endif  // __MIXAGE__FILTRE__FADIN_IN__H
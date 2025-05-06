#ifndef __MIXAGE__FILTRE__VOLUME_COMPOSE__H
#define __MIXAGE__FILTRE__VOLUME_COMPOSE__H

#include "mixage/filtre/filtre_compose.hpp"
#include "mixage/filtre/multiplicateur.hpp"
#include "mixage/filtre/volume.hpp"

/// \class volume_compose
///
/// \brief Représente un filtre composé qui applique un volume à un signal d'entrée
///        en combinant un composant `volume` et un `multiplicateur`.
///
/// \author Florian Cliquet
/// \date 10/04/2025
class volume_compose : public filtre_compose {
public:
  /// \brief Constructeur du filtre composé avec une valeur de volume.
  /// \param valeur_volume Valeur initiale du volume à appliquer.
  explicit volume_compose(double valeur_volume)
      : filtre_compose(1, 1) {
    // Création des composants internes
    std::shared_ptr<multiplicateur> filtre_multi =
        std::make_shared<multiplicateur>();
    std::shared_ptr<volume> filtre_volume =
        std::make_shared<volume>(valeur_volume);

    // Ajout à la liste des composants
    ajoutComposant(filtre_multi);
    ajoutComposant(filtre_volume);

    // Connexion interne entre volume -> entrée 0 du multiplicateur
    filtre_multi->connecterEntree(filtre_volume->getEntree(0), 0);

    // Connexion entrée externe -> entrée 1 du multiplicateur
    ajoutLienInput(0, filtre_multi, 1);

    // Connexion sortie du multiplicateur -> sortie externe
    ajoutLienOutput(0, filtre_multi, 0);
  }
};

#endif  // __MIXAGE__FILTRE__VOLUME_COMPOSE__H
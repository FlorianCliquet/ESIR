#ifndef __MIXAGE__FILTRE__PANNING__H
#define __MIXAGE__FILTRE__PANNING__H

#include "mixage/filtre/filtre_compose.hpp"

#include <memory>

#include "mixage/filtre/multiplicateur.hpp"
#include "mixage/filtre/panoramique.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class    panning
///
/// \brief    Filtre de panoramique. Ce filtre applique un panning stéréo en ajustant l'intensité
///           des canaux gauche et droit à partir d'un signal panoramique.
///
/// \author   Florian Cliquet
/// \date     11/04/25
class panning : public filtre_compose {
 public:
  /// \brief Constructeur explicite.
  explicit panning() : filtre_compose(2, 3) {
    auto filtre_panoramique = std::make_shared<panoramique>();
    auto filtre_multi_gauche = std::make_shared<multiplicateur>();
    auto filtre_multi_droit = std::make_shared<multiplicateur>();

    // Ajout des filtres au composite
    ajoutComposant(filtre_panoramique);
    ajoutComposant(filtre_multi_gauche);
    ajoutComposant(filtre_multi_droit);
    

    // Création des liens d'entrées
    ajoutLienInput(0, filtre_multi_gauche, 0);
    ajoutLienInput(1, filtre_multi_droit, 0);
    ajoutLienInput(2, filtre_panoramique, 0);

    // Connexion des sorties entre les filtres
    filtre_multi_gauche->connecterEntree(filtre_panoramique->getSortie(0), 1);
    filtre_multi_droit->connecterEntree(filtre_panoramique->getSortie(1), 1);

    // Ajout des sorties
    ajoutLienOutput(0, filtre_multi_gauche, 0);
    ajoutLienOutput(1, filtre_multi_droit, 0);
  }
};

#endif // __MIXAGE__FILTRE__PANNING__H

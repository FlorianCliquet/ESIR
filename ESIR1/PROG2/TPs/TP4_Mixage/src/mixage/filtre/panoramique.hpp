#ifndef __MIXAGE__FILTRE__PANORAMIQUE__H
#define __MIXAGE__FILTRE__PANORAMIQUE__H

#include "mixage/filtre/filtre_base.hpp"

#include <cassert>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class    Panoramique
///
/// \brief    Filtre de panoramique. Ce filtre répartit le signal entre les canaux gauche et droit
///           selon un facteur de panoramique, qui est calculé en fonction du signal d’entrée.
///
/// \author   Florian Cliquet
/// \date     11/04/25
class panoramique : public filtre_base {
 public:
  /// \brief Constructeur explicite.
  panoramique();

  /// \brief Calcule le panoramique et applique la distribution du signal aux deux sorties.
  void calculer() override;
};

#endif // __MIXAGE__FILTRE__PANORAMIQUE__H

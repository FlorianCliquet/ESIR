#ifndef __MIXAGE__FILTRE__COMPRESSION__H
#define __MIXAGE__FILTRE__COMPRESSION__H

#include "mixage/filtre/filtre_base.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class    Compression
///
/// \brief    Filtre de compression audio. Réduit la dynamique des échantillons audio en atténuant
///           les amplitudes trop fortes selon une force de compression spécifiée.
///
/// \author   Florian Cliquet
/// \date     11/04/2025
class compression : public filtre_base {
private:
  const double force_;
  /// \brief Retourne le signe de la valeur donnée.
  /// \param x La valeur en entrée.
  /// \return -1.0 si x < 0, 1.0 si x > 0, 0.0 si x == 0.
  static double signe(const double x);

  public:
  /// \brief Constructeur explicite.
  /// \param force Le niveau de compression à appliquer (doit être strictement positif).
  explicit compression(const double force);

  /// \brief Applique le filtre de compression aux échantillons fournis.
  void calculer() override;
};

#endif  // __MIXAGE__FILTRE__COMPRESSION__H

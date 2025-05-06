#ifndef __MIXAGE__FILTRE__ECHO__H
#define __MIXAGE__FILTRE__ECHO__H

#include "mixage/filtre/filtre_base.hpp"

#include "mixage/utils/circular_buffer.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class    echo
///
/// \brief    Filtre de type écho audio. Ce filtre applique un retard sur les échantillons audio 
///           en utilisant un buffer circulaire et applique une atténuation au signal retardé.
///
/// \author   Florian Cliquet
/// \date     11/04/25
class echo : public filtre_base {
 private:
  circular_buffer<double> buffer_;            ///< Buffer circulaire pour stocker les échantillons audio.
  const double attenuation_;                  ///< Facteur d'atténuation du signal retardé.
  const double decalage_temporel_;            ///< Délai temporel de l'écho en millisecondes.
  double temps_courant_;                     ///< Temps actuel dans le flux audio (en ms).

 public:
  /// \brief Constructeur explicite.
  /// \param decalage_temporel Temps du décalage temporel (en ms).
  /// \param attenuation Facteur d'atténuation du signal retardé.
  explicit echo(double decalage_temporel, double attenuation);

  /// \brief Applique le filtre d'écho sur l'entrée audio et ajoute le signal retardé avec atténuation.
  void calculer() override;
};

#endif  // __MIXAGE__FILTRE__ECHO__H
#ifndef __MIXAGE__PRODUCTEUR__HARMONIQUE_H
#define __MIXAGE__PRODUCTEUR__HARMONIQUE_H

#include "mixage/producteur/producteur_base.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class  harmonique
///
/// \brief  Génère une sinusoïde à partir d’une fréquence et d’une phase donnée. Implémente un
///         producteur avec une seule sortie contenant les échantillons successifs d’un signal
///         harmonique.
///
/// \author Florian Cliquet
/// \date   09/04/2025
class harmonique : public producteur_base {
 private:
  const int frequence_;
  const double phase_;
  unsigned int i_;

 protected:
  /// \brief Génère un échantillon sinusoïdal en fonction de l'indice courant.
  /// \return L'échantillon calculé.
  double genererEchantillon() const;

 public:
  /// \brief Constructeur à partir d'une fréquence et d'une phase.
  /// \param frequence La fréquence du signal (Hz).
  /// \param phase     La phase initiale du signal (en radians).
  explicit harmonique(int frequence, double phase);

  /// \brief Remplit la sortie avec un nouvel échantillon harmonique.
  void calculer() override;
};

#endif
#ifndef __MIXAGE__CONSOMMATEUR__CONSOMMATEUR_BASE__H
#define __MIXAGE__CONSOMMATEUR__CONSOMMATEUR_BASE__H

#include "mixage/consommateur.hpp"

#include <memory>
#include <vector>
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class   consommateur_base
///
/// \brief   Classe de base pour les consommateurs. Gère la connexion aux flux d'entrée.
/// 
/// \author  Florian Cliquet
/// \date    09/04/2025
class consommateur_base : public consommateur {
private:
  std::vector<std::shared_ptr<flot>> entrees_;

public:
  explicit consommateur_base(unsigned int nb_entrees);
  ~consommateur_base() override = default;

  /// \brief Retourne le nombre d’entrées disponibles.
  unsigned int nbEntrees() const override;

  /// \brief Retourne une référence vers l'entrée spécifiée.
  /// \param numentree L'indice de l'entrée.
  const std::shared_ptr<flot>& getEntree(unsigned int numentree) const override;

  /// \brief Connecte une entrée à un flot donné.
  /// \param f Le flot à connecter.
  /// \param numentree L’indice d’entrée.
  void connecterEntree(const std::shared_ptr<flot>& f, unsigned int numentree) override;

  /// \brief Vérifie si toutes les entrées ont des échantillons disponibles.
  bool yaDesEchantillons() const override;
};

#endif //__MIXAGE__CONSOMMATEUR__CONSOMMATEUR_BASE__H
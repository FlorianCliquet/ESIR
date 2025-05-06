#ifndef __MIXAGE__PRODUCTEUR__PRODUCTEUR_BASE__H
#define __MIXAGE__PRODUCTEUR__PRODUCTEUR_BASE__H

#include <memory>
#include <vector>

#include "mixage/producteur.hpp"

/// \class producteur_base
///
/// \brief Classe de base pour les producteurs ayant plusieurs sorties.
///        Gère une collection de flots (sorties) et permet de les connecter.
///
/// \author Florian Cliquet
/// \date 09/04/2025
class producteur_base : public producteur {
 private:
  // Contient les flots associés aux sorties du producteur.
  std::vector<std::shared_ptr<flot>> sorties_;

 protected:
  /// \brief Connecte un flot à l'une des sorties du producteur.
  /// \param f Le flot à connecter.
  /// \param indice_sortie L'indice de la sortie à laquelle connecter le flot.
  void connecterSortie(const std::shared_ptr<flot>& f,
                       unsigned int indice_sortie);

 public:
  /// \brief Constructeur explicite.
  /// \param nb_sortie Le nombre de sorties à initialiser.
  explicit producteur_base(unsigned int nb_sortie);

  /// \brief Destructeur virtuel par défaut.
  ~producteur_base() override = default;

  /// \brief Retourne le nombre de sorties du producteur.
  /// \return Nombre de sorties.
  unsigned int nbSorties() const override;

  /// \brief Retourne une référence vers la sortie spécifiée.
  /// \param numsortie Indice de la sortie demandée.
  /// \return Référence vers le flot de sortie.
  const std::shared_ptr<flot>& getSortie(unsigned int numsortie) const override;
};

#endif // __MIXAGE__PRODUCEUR__PRODUCTEUR_BASE__H
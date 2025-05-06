#ifndef __MIXAGE__FILTRE__ADDITIONNEUR__H
#define __MIXAGE__FILTRE__ADDITIONNEUR__H

#include "mixage/filtre/filtre_base.hpp"
class additionneur : public filtre_base {
public:
  explicit additionneur(const unsigned int nb_entrees);
  void calculer() override;
};

#endif // __MIXAGE__FILTRE__ADDITIONNEUR__H
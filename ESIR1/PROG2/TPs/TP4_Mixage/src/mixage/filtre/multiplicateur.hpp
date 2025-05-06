#ifndef __MIXAGE__FILTRE__MULTIPLICATEUR__H
#define __MIXAGE__FILTRE__MULTIPLICATEUR__H

#include "mixage/filtre/filtre_base.hpp"
class multiplicateur : public filtre_base {
public:
  explicit multiplicateur();
  void calculer() override;
};

#endif //__MIXAGE__FILTRE__MULTIPLICATEUR__H
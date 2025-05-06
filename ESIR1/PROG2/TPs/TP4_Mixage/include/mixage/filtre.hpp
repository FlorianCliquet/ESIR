// -*- c++ -*-

#ifndef __MIXAGE__FILTRE__H__
#define __MIXAGE__FILTRE__H__

#include "producteur.hpp"
#include "consommateur.hpp"

// spécification d'un filtre

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	filtre
///
/// \brief	Interface associée à un filtre sonore. Ce filtre est considéré comme un producteur /
///		consommateur d'échantillons sonores. Il possède donc des entrées et des sorties.
///
/// \author	Jean Christophe Engel, Fabrice Lamarche, University Of Rennes 1
/// \date	23/04/2010
////////////////////////////////////////////////////////////////////////////////////////////////////
class filtre : public virtual producteur, public virtual consommateur {
public:

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \fn	virtual ~filtre()
  ///
  /// \brief	Destructeur virtuel. 
  ///
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  virtual ~filtre() {}
};

#endif // __MIXAGE__FILTRE__H__

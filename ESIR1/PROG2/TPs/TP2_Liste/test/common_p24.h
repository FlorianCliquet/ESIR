#ifndef __COMMON_P24_H__			// -*- c++ -*-
#define __COMMON_P24_H__

#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>
#include "Liste.h"

//------------------------------------------------------------------------
// fonctions utilitaires pour la partie 2.4
//------------------------------------------------------------------------

// comparer les élts d'une liste et ceux d'un deque
// parcours de la liste avec iterator
// requiert begin, end, ++, *, !=
template <class T>
void
list_equals_deque_forward(
			  Liste<T>	      & list,
			  const std::deque<T> & array
			  )
{
#ifdef DEBUG
  std::cout << "test égalité avec iterator forward\n";
#endif
  EXPECT_EQ(
	    (unsigned int) array.size(),
	    (unsigned int) list.size())
    << "Erreur taille liste";

  unsigned int i_tab = 0;
  typename Liste<T>::iterator it_liste  = list.begin();
  typename Liste<T>::iterator it_fin    = list.end();
  while (it_liste != it_fin)
  {
    EXPECT_EQ(
	      array[i_tab],
	      *it_liste)
      << "Erreur élément de rang " << i_tab;
    ++i_tab;
    ++it_liste;
  }
}

// comparer les élts d'une liste et ceux d'un deque
// parcours de la liste avec iterator
// requiert begin, end, --, *
template <class T>
void
list_equals_deque_backward(
			   Liste<T>	       & list,
			   const std::deque<T> & array
			   )
{
#ifdef DEBUG
  std::cout << "test égalité avec iterator backward\n";
#endif
  EXPECT_EQ(
	    (unsigned int) array.size(),
	    (unsigned int) list.size())
    << "Erreur taille liste";

  unsigned int i_tab = array.size();
  typename Liste<T>::iterator it_liste  = list.end();
  typename Liste<T>::iterator it_fin    = list.begin();
  while (it_liste != it_fin)
  {
    --i_tab;
    --it_liste;
    EXPECT_EQ(
	      array[i_tab],
	      *it_liste)
      << "Erreur élément de rang " << i_tab;
  }
}

#endif // __COMMON_P24_H__

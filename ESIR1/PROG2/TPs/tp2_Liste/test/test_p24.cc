#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>

// fichier qui contient l'implémentation de la classe Liste
#include "Liste.h"

// fonctions utilitaires
#include "common_p1.h"
#include "common_p2.h"
#include "common_p24.h"

//------------------------------------------------------------------------
// tests iterator (2.4) ; idem const_iterator plus
// - modif avec op *
// - modif avec op ->
// à décommenter pour tester 2.4
//------------------------------------------------------------------------

// iterator : tester begin et op * en consultation
TEST(TestList, q24Begin)
{
  Liste<double>		liste;
  liste.push_back(5.5);
  Liste<double>::iterator it_liste  = liste.begin();
  ASSERT_EQ(
	    5.5,
	    *it_liste)
    << "Erreur valeur élément de tête";
}

#ifndef VALGRIND
// iterator : tester assertion op *
TEST(TestList, q24AssertOpEtoile)
{
  Liste<double>		liste;
  liste.push_back(5.5);
  Liste<double>::iterator it_liste  = liste.end();
  ASSERT_DEATH(*it_liste , "Assertion.*failed");
}
#endif

#ifndef VALGRIND
// iterator : tester assertion op ++
TEST(TestList, q24AssertOpInc)
{
  Liste<double>		liste;
  Liste<double>::iterator it  = liste.begin();
  ASSERT_DEATH(++it, "Assertion.*failed");
}
#endif

#ifndef VALGRIND
// iterator : tester assertion op --
TEST(TestList, q24AssertOpDec)
{
  Liste<double>		liste;
  Liste<double>::iterator it  = liste.begin();
  ASSERT_DEATH(--it, "Assertion.*failed");
}
#endif

// iterator : tester == et !=
TEST(TestList, q24EgaliteIterateurs)
{
  Liste<double>		  liste;
  Liste<double>::iterator it_gauche = liste.begin();
  Liste<double>::iterator it_droite   = liste.end();

  // itérateurs begin() et end() dans une liste vide
  EXPECT_TRUE (it_gauche == it_droite) << "ERREUR : les deux itérateurs devraient être égaux";
  EXPECT_FALSE(it_gauche != it_droite) << "ERREUR : les deux itérateurs ne devraient pas être différents";

  // itérateurs begin() et end() dans une liste non vide
  liste.push_back(5.5);
  it_gauche = liste.begin();
  it_droite  = liste.end();
  EXPECT_FALSE(it_gauche == it_droite) << "ERREUR : les deux itérateurs ne devraient pas être égaux";
  EXPECT_TRUE (it_gauche != it_droite) << "ERREUR : les deux itérateurs devraient être différents";

  // itérateurs sur deux éléments de même valeur
  // requiert ++
  liste.push_back(5.5);
  it_gauche = liste.begin();
  it_droite = liste.begin();
  ++it_droite;
  EXPECT_FALSE(it_gauche == it_droite) << "ERREUR : les deux itérateurs ne devraient pas être égaux";
  EXPECT_TRUE (it_gauche != it_droite) << "ERREUR : les deux itérateurs devraient être différents";
}

#ifndef VALGRIND
// iterator : assertion op ->
TEST(TestList, q24AssertionOpFleche)
{
  Liste<std::string> liste;
  Liste<std::string>::iterator it(liste.begin());
  ASSERT_DEATH(it->insert(0, "?"), "Assertion.*failed");
}
#endif

// iterator : tester op -> (consultation)
TEST(TestList, q24OpFleche)
{
  Liste<std::string> liste;
  std::deque<unsigned int>    longueurs;
  // mettre des chaînes de longueurs différentes dans la liste
  for (unsigned int i = 0; i <= 5; ++i) {
    liste.push_front(std::string(i+1, i + 'A'));
    liste.push_back (std::string(i+1, i + '1'));
    longueurs.push_front(i+1);
    longueurs.push_back (i+1);
  }
  // vérifier les longueurs des éléments : op ->
  Liste<std::string>::iterator it_liste = liste.begin();
  Liste<std::string>::iterator it_fin   = liste.end();
  unsigned int i = 0;
  while (it_liste != it_fin) {
    EXPECT_EQ(
	      longueurs[i],
	      it_liste->size()
	      )
      << "Erreur longueur élément " << i;
    ++it_liste;
    ++i;
  }
}

// iterator : parcours de liste en marche avant
TEST(TestList, q24Forward)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  list_equals_deque_forward(liste, array);
}

// idem marche arrière
TEST(TestList, q24Backward)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  list_equals_deque_backward(liste, array);
}

// iterator : test op * modification
TEST(TestList, q24opEtoileModif)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array, alea);
  // modifier les éléments de la liste et du deque
  Liste<double>::iterator it_liste = liste.begin();
  Liste<double>::iterator it_fin   = liste.end();
  unsigned int i = 0;
  while (it_liste != it_fin) {
    *it_liste  *= *it_liste;
    array[i] *= array[i];
    ++it_liste; ++i;
  }
  // vérifier l'égalité de la liste et du array
  list_equals_deque_forward(liste, array);
}

// iterator : test op -> modification
TEST(TestList, q24opFlecheModif)
{
  Liste<std::string>	  liste;
  std::deque<std::string> array;
  // mettre des chaînes de longueurs différentes dans la liste
  for (unsigned int i = 0; i <= 5; ++i) {
    liste.push_front(std::string(i+1, i + 'A'));
    liste.push_back (std::string(i+1, i + '1'));
    array.push_front(std::string(i+1, i + 'A'));
    array.push_back (std::string(i+1, i + '1'));
  }
  // modifier les chaînes
  Liste<std::string>::iterator it_liste = liste.begin();
  Liste<std::string>::iterator it_fin   = liste.end();
  unsigned int i = 0;
  while (it_liste != it_fin) {
    it_liste->insert(0, "(");
    it_liste->append(")");
    array[i].insert(0, "(");
    array[i].append(")");
    ++it_liste; ++i;
  }
  // vérifier l'égalité de la liste et du array
  list_equals_deque_forward(liste, array);
}

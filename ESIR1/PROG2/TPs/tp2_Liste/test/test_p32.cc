#include <algorithm>
#include <deque>
#include <gtest/gtest.h>
#include <cstdlib>

// fichier qui contient l'implémentation de la classe Liste
#include "Liste.h"

// fichier qui contient les deux fonctions chercherTri et copierTri de la partie 3
#include "copier.h"

// fonctions utilitaires
#include "common_p1.h"
#include "common_p2.h"
#include "common_p24.h"

//------------------------------------------------------------------------
// tests des autres fonctions de la partie 3
// - recherche dans une liste triée
// - copie triée d'une liste
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// test recherche liste vide
//------------------------------------------------------------------------
TEST(TestList, q321RechercheListeVide)
{
  Liste<double> liste;
  Liste<double>::iterator found = chercherTri(liste.begin(),
					      liste.end(),
					      3.14159);
  ASSERT_TRUE(
	    liste.end() == found)
    << "Erreur itérateur résultat";
}

//------------------------------------------------------------------------
// test recherche dans liste de taille 1
// - élément inférieur au premier
// - élément égal au premier
// - élément supérieur au premier
//------------------------------------------------------------------------
TEST(TestList, q321RechercheListeTaille1)
{
  Liste<double> liste;
  liste.push_back(3.14159);
  // chercher un élément inférieur au premier
  Liste<double>::iterator found = chercherTri(liste.begin(),
					      liste.end(),
					      -999.);
  ASSERT_TRUE(
	    liste.begin() == found)
    << "Erreur itérateur résultat";
  // chercher un élément égal au premier
  found = chercherTri(liste.begin(),
		      liste.end(),
		      3.14159);
  ASSERT_TRUE(
	    liste.begin() == found)
    << "Erreur itérateur résultat";
  // chercher un élément supérieur au premier
  found = chercherTri(liste.begin(),
		      liste.end(),
		      999.);
  ASSERT_TRUE(
	    liste.end() == found)
    << "Erreur itérateur résultat";
}

// copier un tableau dans une liste
void
copier_array_list(
		  const std::deque<double> & array,
		  Liste<double> & liste
		  )
{
  std::deque<double>::const_iterator it     = array.begin();
  std::deque<double>::const_iterator it_fin = array.end();
  while (it != it_fin) {
    liste.push_back(*it);
    ++it;
  }
}

#include <deque>
#include <sstream>
#include <cstdlib>
#include <gtest/gtest.h>

// fichier qui contient l'implémentation de la classe Liste
#include "Liste.h"

// fonctions utilitaires
#include "common_p1.h"
#include "common_p2.h"
#include "common_p24.h"

//------------------------------------------------------------------------
// tests partie 4
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// tests constructeur de copie q4.1
//------------------------------------------------------------------------
// cdc : vérifier copie
TEST(TestList, q41cdc)
{
  // initialiser une liste et un tableau
  Liste<double>		original;
  std::deque<double>	array;
  ajouter_elts(original, array);
  // vérification préalable
  std::cout << "q41cdc : vérification préalable\n";
  list_equals_deque_forward(original, array);
  // faire une copie de la liste
  Liste<double>		copie(original);
  // vérifier sa taille et son contenu
  std::cout << "q41cdc : vérification après cdc\n";
  list_equals_deque_forward(copie, array);
}

// cdc : vérifier copie après modifications de l'original
TEST(TestList, q41cdcModifOriginal)
{
  // initialiser une liste et un tableau
  Liste<double>		original;
  std::deque<double>	array;
  ajouter_elts(original, array);
  // vérification préalable
  list_equals_deque_forward(original, array);

  // faire une copie de la liste
  Liste<double>		copie(original);
  // vérifier sa taille et son contenu
  list_equals_deque_forward(copie, array);

  // supprimer des éléments dans l'original
  original.pop_front(); original.pop_back();
  // vérifier que la copie n'a pas changé
  list_equals_deque_forward(copie, array);

  // ajouter des éléments dans l'original
  original.push_front(100); original.push_back(999);
  // vérifier que la copie n'a pas changé
  list_equals_deque_forward(copie, array);

  // modifier des éléments dans l'original
  original.front() *= 10; original.back() *= 9.9;
  // vérifier que la copie n'a pas changé
  list_equals_deque_forward(copie, array);
}

// cdc : vérifier copie après modifications de la copie
TEST(TestList, q41cdcModifCopie)
{
  // initialiser une liste et un tableau
  Liste<double>		original;
  std::deque<double>	array;
  ajouter_elts(original, array);
  // vérification préalable
  list_equals_deque_forward(original, array);

  // faire une copie de la liste
  Liste<double>		copie(original);
  // vérifier sa taille et son contenu
  list_equals_deque_forward(copie, array);

  // supprimer des éléments dans la copie
  copie.pop_front(); copie.pop_back();
  // vérifier la taille de la copie
  EXPECT_EQ(
	    original.size() - 2,
	    copie.size())
    << "Erreur taille copie après suppression";
  // vérifier que l'original n'a pas changé
  list_equals_deque_forward(original, array);

  // ajouter des éléments dans la copie
  copie.push_front(100); copie.push_back(999);
  // vérifier la taille de la copie
  EXPECT_EQ(
	    original.size(),
	    copie.size())
    << "Erreur taille copie après ajouts";
  // vérifier que l'original n'a pas changé
  list_equals_deque_forward(original, array);

  // modifier des éléments dans la copie
  copie.front() *= 10; copie.back() *= 9.9;
  // vérifier que l'original n'a pas changé
  list_equals_deque_forward(original, array);
}

//------------------------------------------------------------------------
// tests opérateur = q4.2
//------------------------------------------------------------------------

// tester liste = liste
TEST(TestList, q42OpEgalSelf)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array);
  // vérification préalable
  list_equals_deque_forward(liste, array);
  liste = liste;
  list_equals_deque_forward(liste, array);
}

// tester vide = droite
TEST(TestList, q42OpEgalGaucheVide)
{
  Liste<double> gauche, droite;
  std::deque<double>	array;
  ajouter_elts(droite, array);
  // vérification préalable
  list_equals_deque_forward(droite, array);
  gauche = droite;
  // vérifier les deux listes
  list_equals_deque_forward(gauche, array);
  list_equals_deque_forward(droite, array);
}

// tester gauche = vide
TEST(TestList, q42OpEgalDroiteVide)
{
  Liste<double> gauche, droite;
  std::deque<double>	array;
  ajouter_elts(gauche, array);
  // vérification préalable
  list_equals_deque_forward(gauche, array);
  gauche = droite;
  // vérifier les deux listes
  ASSERT_TRUE(gauche.empty()) << "Erreur taille liste de gauche";
  ASSERT_TRUE(droite.empty()) << "Erreur taille liste de droite";
}

// tester gauche = droite
TEST(TestList, q42OpEgal)
{
  // initialiser la première liste
  Liste<double>		gauche;
  std::deque<double>	left_array;
  ajouter_elts(gauche, left_array);
  std::cout << "q42OpEgal : vérification préalable liste gauche\n";
  list_equals_deque_forward(gauche, left_array);

  // initialiser la deuxième liste
  Liste<double>		droite;
  std::deque<double>	right_array;
  ajouter_elts(droite, right_array);
  std::cout << "q42OpEgal : vérification préalable liste droite\n";
  list_equals_deque_forward(droite, right_array);

  gauche = droite;

  // vérifier les deux listes
  std::cout << "q42OpEgal : vérification liste gauche après gauche = droite\n";
  list_equals_deque_forward(gauche, right_array);
  std::cout << "q42OpEgal : vérification liste droite après gauche = droite\n";
  list_equals_deque_forward(droite, right_array);
}

//------------------------------------------------------------------------
// test opérateur + q4.3
//------------------------------------------------------------------------
TEST(TestList, q43Concat)
{
    // initialiser la première liste
  Liste<double>		first_list;
  std::deque<double>	first_array;
  ajouter_elts(first_list, first_array);
  list_equals_deque_forward(first_list, first_array);

  // initialiser la deuxième liste
  Liste<double>		second_list;
  std::deque<double>	second_array;
  ajouter_elts(second_list, second_array);
  list_equals_deque_forward(second_list, second_array);

  // puis la troisième
  Liste<double>		third_list;
  std::deque<double>	third_array;
  ajouter_elts(third_list, third_array);
  list_equals_deque_forward(third_list, third_array);

  // concaténer les trois listes
  Liste<double>		big_list(first_list + second_list + third_list);
  // faire de même avec les tableaux
  std::deque<double>	big_array(first_array.size() + second_array.size() +
				  third_array.size());
  std::deque<double>::iterator next =
    std::copy(first_array.begin(), first_array.end(), big_array.begin());
  next = std::copy(second_array.begin(), second_array.end(), next);
  next = std::copy(third_array.begin(), third_array.end(), next);
  // puis comparer les résultats
  list_equals_deque_forward(big_list, big_array);
}

TEST(TestList, q43Concat4)
{
  std::deque<std::deque<double> >	arrays(4);
  std::deque<Liste<double> >		lists(arrays.size());
  unsigned int big_array_size = 0;
  for (unsigned int i = 0; i < arrays.size(); ++i) {
    // initialiser liste et tableau
    ajouter_elts(lists[i], arrays[i]);
    big_array_size += arrays[i].size();
    // vérification initiale, a priori inutile
    list_equals_deque_forward(lists[i], arrays[i]);
  }

  // concaténer les listes
  Liste<double>		big_list (
				  (lists[0] + lists[1]) +
				  (lists[2] + lists[3])
				  );
  // puis les tableaux
  std::deque<double>	big_array(big_array_size);
  std::deque<double>::iterator next = big_array.begin();
  for (unsigned int i = 0; i < arrays.size(); ++i) {
    next = std::copy(arrays[i].begin(), arrays[i].end(), next);
  }

  // comparer les résultats
  list_equals_deque_forward(big_list, big_array);
}

//------------------------------------------------------------------------
// test opérateur << q4.4
// À ADAPTER au format de sortie de operator <<
//------------------------------------------------------------------------

TEST(TestList, q44opInsertion)
{
  Liste<double>		liste;
  std::deque<double>	array;
  ajouter_elts(liste, array);
  // vérification préalable
  list_equals_deque_forward(liste, array);

  // "afficher" la liste
  std::ostringstream list_string;
  list_string << liste;

  // idem avec deque
  // À ADAPTER au format de sortie de operator <<
  // le deuxième paramètre de ostream_iterator est une chaîne qui sépare les éléments
  // dans le flux de sortie
  std::ostringstream array_string;
  array_string << "<";					// début de liste : à adapter
  std::copy(array.begin(), array.end(),
	    std::ostream_iterator<double>(array_string, " "));
  array_string << ">";					// fin de liste : à adapter

  // et vérifier le résultat
  ASSERT_EQ(array_string.str(), list_string.str());
}

// -*- c++ -*-
#ifndef _DataStructure_CyclicNode_H
#define _DataStructure_CyclicNode_H

namespace DataStructure
{
  /** Noeud cyclique.
	
  Ce noeud cyclique est rebouclé sur lui-même par défaut ou peut être 
  utilisé pour représenter des listes cycliques.
  @param T Le type de donnée contenu dans ce noeud
  @warning Le type T doit posséder un constructeur par défaut et un constructeur de copie
  */
  template <class T>
  class cyclicNode
  {
  protected:
    /** Le noeud précédent */
    cyclicNode<T> * m_previous ;
    /** Le noeud suivant */
    cyclicNode<T> * m_next ;
    /** La donnée contenue dans ce noeud */
    T		    m_bloc ;

  protected:
    void lightDetach()
    {
      m_previous->m_next = m_next ;
      m_next->m_previous = m_previous ;
    }

  public:
    /** Constructeur par défaut */
    cyclicNode()
      : m_previous(this), m_next(this) { }

    /** Constructeur avec initialisation de la donnée */
    cyclicNode(T const & data)
      : m_previous(this), m_next(this), m_bloc(data) { }

    /** Récupération du noeud prédécesseur */
    cyclicNode<T> * previous() const
    { return m_previous ; }

    /** Récupération du noeud suivant */
    cyclicNode<T> * next() const
    { return m_next ; }

    /** Récupération de la donnée contenue dans ce noeud */
    const T & data() const
    { return m_bloc ; }

    /** Récupération de la donnée contenue dans ce noeud */
    T & data() 
    { return m_bloc ; }

    /** Décroche ce noeud de la structure cyclique à laquelle il appartient */
    void detach()
    {
      lightDetach();
      m_previous = this ;
      m_next = this ;
    }
    //
    /** Insère un noeud avant ce noeud 
	@param node Le noeud à insérer
	@warning Le noeud est décroché de sa structure courante
    */
    void insertBefore(cyclicNode<T> * node)
    {
      node->lightDetach() ;
      m_previous->m_next=node ;
      node->m_previous = m_previous ;
      node->m_next = this ;
      m_previous = node ;
    }

    /** Insère un noeud après ce noeud 
	@param node Le noeud à insérer
	@warning Le noeud est décroché de sa structure courante
    */
    void insertAfter(cyclicNode<T> * node)
    {
      node->lightDetach() ;
      m_next->m_previous=node ;
      node->m_previous=this ;
      node->m_next=m_next ;
      m_next = node ;
    }

    /** Destructeur
	Ce destructeur détache le noeud de sa structure courante.
    */
    ~cyclicNode()
    {
      detach() ;
    }
  };
}

#endif 

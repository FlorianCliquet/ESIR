#include <stdlib.h>
#include <map>
#include <iostream>
#include <sstream>
/** \brief Gestionnaire de mémoire
 * 
 * Le rôle de cette classe est d'allouer désallouer de la mémoire sur demande.
 * Elle gère une table d'allocation afin de vérifier la validité des désallocations
 * et d'afficher l'ensemble des fuites mémoires du programme.
 *
 * Dans cette implémentation, la mémoire n'est pas libérée de manière effective
 * (la commande est commentée) mais par contre, une demande de libération
 * réinitialise la zone mémoire associée :)
 */
class Array
{
public:
  /** \brief Le type pointeur utilisé */
  typedef void * Pointer ;
  /** \brief Paire composée d'un pointeur et de la taille de mémoire allouée */
  typedef std::pair<Pointer, size_t> Pair ;

private:
  /** \brief Table contenant les allocations référencées */
  Pair *	m_array ;
  /** \brief Taille du tableau alloué */
  int		m_allocatedSize ;
  /** \brief Taille actuellement utilisée dans le tableau */
  int		m_size ;
  /** \brief Un petit message devant précéder toutes les traces textuelles */
  const char * m_message ;

  /** \brief Permet de savoir si les allocation mémoire doivent ou non etre enregistrées */
  bool m_record ;

  /** \brief Recherche l'entrée d'allocation mémoire correspondant au pointeur
   *  \param pointer Le pointeur à rechercher
   *  \return L'indice du pointeur dans le tableau, -1 si ce dernier n'est pas présent
   */
  int find(Pointer pointer) const
  {
    for(int cpt=0 ; cpt<m_size ; cpt++)
    {
      if(m_array[cpt].first==pointer)
      {
	return cpt ;
      }
    }
    return -1 ;
  }

  /** \brief Supprime une entrée d'allocation mémoire dans la table
   *
   *  \return -1 si le pointeur n'a pas été alloué ou n'est plus alloué, renvoie le nombre d'octets libérés sinon
   */
  int remove(Pointer pointer)
  {
    int index(find(pointer)) ;
    int size(-1) ;
    if(index!=-1)
    {
      size = (int)m_array[index].second ;
      std::swap(m_array[m_size-1], m_array[index]) ;
      m_size-- ;
    }
    return size ;
  }

  /** \brief Ajoute une entrée d'allocation mémoire dans la table 
   *  \param pointer Le pointeur vers la zone mémoire allouée
   *  \param size    La taille en octets de la zone mémoire allouée
   */
  void add(Pointer pointer, size_t size)
  {
    if(!m_record) { return ; }
    if(m_size==m_allocatedSize)
    {
      m_allocatedSize = m_allocatedSize * 2 ;
      m_array = (Pair*)realloc(m_array, sizeof(Pair)*m_allocatedSize) ;
    }
    m_array[m_size] = Pair(pointer, size) ;
    m_size++ ;
  }

public:
  /** \brief Constructeur d'allocateur mémoire
   *  \param message Message précédant tout affichage relatif à l'allocateur
   */
  Array(const char * message)
    : m_array((Pair*)malloc(sizeof(Pair)*16)), m_allocatedSize(16), m_size(0), m_message(message), m_record(false)
  {
    m_record = true ;

    std::cout<<"Initialisation de l'allocateur "<<message<<std::endl ;
  }

  /** \brief Demande d'allocation mémoire
   *  \param size La taille (en octets) de la mémoire à allouer.
   */
  void * allocate(size_t size)
  {
    void * pointer = malloc(size) ;

    if(m_record)
    {
      std::cout<<m_message<<"Allocation @ "<<pointer<<" / "<<(int)size<<" octets"<<std::endl ;
    }
    add(pointer, size) ;

    return pointer ;
  }

  /** \brief Demande de libération de la mémoire
   *
   * Cette méthode vérifie le pointeur et s'assure qu'il correspond bien à un pointeur alloué.
   *
   * \param pointer Un pointeur vers la zone mémoire à libérer
   */
  void free(void * pointer)
  {
    int size = remove(pointer) ;
    if(size!=-1)
    {
      // Réinitialisation de la mémoire
      char * charPointer = (char*)pointer ;
      for(int cpt=0 ; cpt<size ; cpt++)
      {
	charPointer[cpt]=char(255) ;
      }
      // Pour le moment, on ne libère pas la mémoire (pour des raisons pédagogique bien évidemment).
      //free(pointer) ;
      std::cout<<m_message<<"Liberation @ "<<pointer<<" / "<<size<<" octets"<<std::endl ;
    }
    else
    {
      std::cout<<std::endl<<m_message<<" ERREUR ! @ "<<pointer<<" non allouée !"<<std::endl ;
    }
  }

  /** \brief Desctructeur de l'allocateur mémoire
   *
   *  Ce destructeur affiche l'état de la mémoire perdue (i.e. non desallouée)
   */
  ~Array()
  {
    if(m_size!=0)
    {
      std::cout<<std::endl ;
      std::cout<<m_message<<" ERREUR ! Fuites mémoire détectées !"<<std::endl ;

      for(int cpt=0 ; cpt<m_size ; cpt++)
      {
	std::cout<<m_message<<"\t@ "<<m_array[cpt].first<<" / "<<(int)m_array[cpt].second<<" octets"<<std::endl ;
      }

      char c ;
      std::cout<<"Entrez un caractère"<<std::endl ;
      std::cin>>c ;
    }
  }

} ;

/** \brief Message associé à l'allocateur d'instances d'objets */
static const char * s_msgObjectAllocator("\t--- MEMORY MANAGER: objects  --- ") ;

/** \brief Message associé à l'allocateur de tableaux */
static const char * s_msgArrayAllocator ("\t--- MEMORY MANAGER: tableaux --- ") ;

/** \brief Allocateur de mémoire utilisé pour les instances d'objets */
static Array s_allocated(s_msgObjectAllocator) ;

/** \brief Allocateur de mémoire utilisé pour les tableaux d'objets */
static Array s_arrayAllocated(s_msgArrayAllocator) ;

/** \brief Redéfinition de l'allocateur d'objets */
void * operator new (size_t size)
{
	return s_allocated.allocate(size) ;
}

/** \brief Redéfinition de l'allocateur de tableaux */
void* operator new[] (size_t size) 
{
	return s_arrayAllocated.allocate(size) ;
}

/** \brief Redéfinition de la libération de la mémoire associée à un objet */
void operator delete (void * ptr)
{
	s_allocated.free(ptr) ;
}

/** \brief Redéfinition de la libération de la mémoire associée à un tableau */
void operator delete[] (void * ptr) 
{
	s_arrayAllocated.free(ptr) ;
}

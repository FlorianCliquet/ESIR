#ifndef __MIXAGE_CIRCULAR_BUFFER_HPP
#define __MIXAGE_CIRCULAR_BUFFER_HPP

#include <vector>
#include <cassert>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class    circular_buffer
///
/// \brief    Implémentation d’un buffer circulaire de taille fixe. Ce buffer écrase automatiquement 
///           les anciennes valeurs lorsqu’il atteint sa capacité. Il permet une lecture en FIFO 
///           ainsi qu’une lecture à un décalage arbitraire.
///
/// \author   Florian Cliquet
/// \date     11/04/25
///
/// \tparam   T Type des éléments contenus dans le buffer.
template <typename T>
class circular_buffer {
 private:
  std::vector<T> buffer_;  ///< Contenu du buffer.
  size_t head_;            ///< Index de la prochaine écriture (et de la lecture FIFO).
  size_t size_;            ///< Capacité maximale du buffer.

 public:
  /// \brief Constructeur explicite.
  /// \param capacity Nombre d’éléments que le buffer peut contenir.
  explicit circular_buffer(size_t capacity)
      : buffer_(capacity), head_(0), size_(capacity) {}

  /// \brief Lit l’élément actuel (le plus ancien dans un usage FIFO).
  /// \return L’élément situé à la tête du buffer.
  T read() const {
    assert(size_ > 0);
    return buffer_[head_];
  }

  /// \brief Ajoute un élément dans le buffer à la position actuelle, écrasant l’ancien.
  /// \param value La valeur à insérer.
  void write(const T& value) {
    assert(size_ > 0);
    buffer_[head_] = value;
    head_ = (head_ + 1) % size_;
  }

  /// \brief Lit un élément à un décalage depuis la tête.
  /// \param offset Décalage par rapport à la position actuelle.
  /// \return L’élément à l’offset spécifié.
  T peek(size_t offset) const {
    assert(offset < size_);
    size_t index = (head_ + offset) % size_;
    return buffer_[index];
  }

  /// \brief Réinitialise le buffer (remplit de valeurs par défaut).
  void reset() {
    std::fill(buffer_.begin(), buffer_.end(), T{});
    head_ = 0;
  }

  /// \brief Renvoie la capacité maximale du buffer.
  /// \return Le nombre total d’éléments que peut contenir le buffer.
  size_t capacity() const {
    return size_;
  }

  /// \brief Renvoie l’index de la prochaine écriture.
  /// \return L’index courant du head.
  size_t index() const {
    return head_;
  }
};

#endif  // __MIXAGE_CIRCULAR_BUFFER_HPP
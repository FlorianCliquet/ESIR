#ifndef _Vector2_H
#define _Vector2_H

#include "utils/MathUtils.hpp"
#include <cmath>

/// <summary>
/// A two dimensional vector class.
/// </summary>
template <class Scalar> class Vector2 {
protected:
  Scalar m_coordinates[2];

public:
  /// <summary>
  /// Initializes a new instance of the <see cref="Vector2"/> class.
  /// </summary>
  /// <param name="x">The x coordinate.</param>
  /// <param name="y">The y coordinate.</param>
  Vector2(Scalar x = 0.0, Scalar y = 0.0) {
    m_coordinates[0] = x;
    m_coordinates[1] = y;
  }

  /// <summary>
  /// Gets the value of the coordinate designated by index.
  /// </summary>
  /// <param name="index">The index of the coordinate.</param>
  /// <returns></returns>
  Scalar operator[](unsigned int index) const { return m_coordinates[index]; }

  /// <summary>
  /// Gets / sets the value of the coordinate designated by index.
  /// </summary>
  /// <param name="index">The index of the coordinate.</param>
  /// <returns></returns>
  Scalar &operator[](unsigned int index) { return m_coordinates[index]; }

  /// <summary>
  /// Computes the sum of two vectors.
  /// </summary>
  /// <param name="v">The other vector.</param>
  /// <returns></returns>
  Vector2 operator+(const Vector2 &v) const {
    return Vector2(m_coordinates[0] + v[0], m_coordinates[1] + v[1]);
  }

  /// <summary>
  /// Computes the difference between two vectors.
  /// </summary>
  /// <param name="v">The other vector.</param>
  /// <returns></returns>
  Vector2 operator-(const Vector2 &v) const {
    return Vector2(m_coordinates[0] - v[0], m_coordinates[1] - v[1]);
  }

  /// <summary>
  /// Computes the multiplication of this vector by a scalar.
  /// </summary>
  /// <param name="v">The scalar.</param>
  /// <returns></returns>
  Vector2 operator*(const Scalar &v) const {
    return Vector2(m_coordinates[0] * v, m_coordinates[1] * v);
  }

  /// <summary>
  /// Computes the division of the vector by a scalar.
  /// </summary>
  /// <param name="v">The scalar.</param>
  /// <returns></returns>

  // SUBOPTIMAL IMPLEMENTATION
  // Vector2 operator/(const Scalar &v) const {
  //   return Vector2(m_coordinates[0] / v, m_coordinates[1] / v);
  // }

  Vector2 operator/(const Scalar &v) const {
    Scalar inv = Scalar(1) / v; // Compute reciprocal once
    return (*this) * inv;
  }

  /// <summary>
  /// Computes the negation of this vector.
  /// </summary>
  /// <returns></returns>
  Vector2 operator-() const { return Vector2(-m_coordinates[0], -m_coordinates[1]); }

  /// <summary>
  /// Computes the dot product of two vectors.
  /// </summary>
  /// <param name="v">The v.</param>
  /// <returns></returns>
  Scalar operator*(const Vector2 &v) const {
    return m_coordinates[0] * v.m_coordinates[0] + m_coordinates[1] * v.m_coordinates[1];
  }

  /// <summary>
  /// Computes the norm of this vector.
  /// </summary>
  /// <returns></returns>
  Scalar norm() const {
    return sqrt(m_coordinates[0] * m_coordinates[0] + m_coordinates[1] * m_coordinates[1]);
  }

  /// <summary>
  /// Computes the normalized vector (*this)/this->norm().
  /// </summary>
  /// <returns></returns>
  Vector2 normalized() const { return (*this) / norm(); }

  /// <summary>
  /// Equality test between two vectors.
  /// </summary>
  /// <param name="v">The other vector.</param>
  /// <returns></returns>
  bool operator==(const Vector2 &v) const {
    return m_coordinates[0] == v[0] && m_coordinates[1] == v[1];
  }

  /// <summary>
  /// Difference test between two vectors.
  /// </summary>
  /// <param name="v">The other vector.</param>
  /// <returns></returns>
  bool operator!=(const Vector2 &v) const { return !((*this) == v); }

  /// <summary>
  /// Computes the rotation of this vector by the angle angle (in radians).
  /// </summary>
  /// <param name="angle">The angle.</param>
  /// <returns></returns>
  Vector2 rotate(const Scalar &angle) const {
    return Vector2(cos(angle) * m_coordinates[0] - sin(angle) * m_coordinates[1],
                   sin(angle) * m_coordinates[0] + cos(angle) * m_coordinates[1]);
  }

  /// <summary>
  /// Computes the distance between two points which coordinates are this vector and the provided
  /// one.
  /// </summary>
  /// <param name="v">The distance.</param>
  /// <returns></returns>
  Scalar distance(const Vector2<Scalar> &v) const { return ((*this) - v).norm(); }

  /// <summary>
  /// Assuming that this vector is a point and v is a point, computes the direction (*this) to v.
  /// </summary>
  /// <param name="v">The direction from (*this) to v.</param>
  /// <returns></returns>
  Vector2<Scalar> direction(const Vector2<Scalar> &v) const { return (v - (*this)).normalized(); }

  /// <summary>
  /// Returns a random unit vector.
  /// </summary>
  /// <returns></returns>
  static Vector2 random() {
    return Vector2(Scalar(1), Scalar(0)).rotate(MathUtils::random() * MathUtils::pi * Scalar(2));
  }
};

#endif

#ifndef _Square_H
#define _Square_H

#include "utils/Vector2.hpp"
#include <algorithm>

/// <summary>
/// A rectangle
/// </summary>
class Rectangle {
protected:
  Vector2<float> m_center, m_extent;

public:
  /// <summary>
  /// Initializes a new instance of the <see cref="Rectangle"/> class.
  /// </summary>
  /// <param name="topLeft">Coordinates of the top left corner of the rectangle.</param>
  /// <param name="diagonal">The diagonal of the rectangle.</param>
  Rectangle(const Vector2<float> &topLeft, const Vector2<float> &diagonal)
      : m_center(topLeft + diagonal / 2.0), m_extent(diagonal / 2.0) {}

  /// <summary>
  /// Computes the distance between this rectangle and a point.
  /// </summary>
  /// <param name="point">The point.</param>
  /// <returns></returns>
  float distance(const Vector2<float> &point) const {
    float dx = std::max<float>((float)fabs(point[0] - m_center[0]) - m_extent[0] * 0.5f, 0.0f);
    float dy = std::max<float>((float)fabs(point[1] - m_center[1]) - m_extent[1] * 0.5f, 0.0f);
    return Vector2<float>(dx, dy).norm();
  }
};

#endif
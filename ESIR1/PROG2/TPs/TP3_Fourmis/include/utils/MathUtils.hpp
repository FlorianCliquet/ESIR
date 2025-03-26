#ifndef _MathFunctions_H
#define _MathFunctions_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <numeric>
#include <vector>

/// <summary>
/// Namespace containing useful mathematical functions and constants
/// </summary>
namespace MathUtils {
/// <summary>
/// pi value
/// </summary>
static const float pi = (float)acos(-1.0);

/// <summary>
/// pi/2.0 value
/// </summary>
static const float piDiv2 = (float)(acos(-1.0) / 2.0);

/// <summary>
/// Given the surface of a circle, this function computes its radius.
/// </summary>
/// <param name="surface">The surface of the circle.</param>
/// <returns> The radius of the circle. </returns>
inline float circleRadius(float surface) { return sqrt(surface / MathUtils::pi); }

/// <summary>
/// Computes a random number in the interval [0;1].
/// </summary>
/// <returns></returns>
inline float random() { return (float)rand() / (float)RAND_MAX; }

/// <summary>
/// Returns a random value in the interval [min;max].
/// </summary>
/// <param name="min">The minimum.</param>
/// <param name="max">The maximum.</param>
/// <returns></returns>
inline float random(float min, float max) {
  assert((max >= min) && "Invalid interval in MathUtils::random(float, float)");
  return min + random() * (max - min);
}

/// <summary>
/// Clamps the specified value in the interval [min;max].
/// </summary>
/// <param name="min">The minimum value.</param>
/// <param name="max">The maximum value.</param>
/// <param name="value">The value.</param>
/// <returns></returns>
inline float clamp(float min, float max, float value) {
  assert(max >= min && "MathUtils::clamp: Invalid interval");
  return ::std::max(::std::min(value, max), min);
}

/// <summary>
/// Randomly chooses an index in the provided table with a probability proportional to its
/// associated weight
/// </summary>
/// <param name="weights">The table of weights.</param>
/// <returns> The index of the chosen element. </returns>
inline unsigned int randomChoose(const std::vector<float> &weights) {
  assert(weights.size() > 0 &&
         "MathUtils::randomChoose: Invalid weight vector, size must be greater than one");
  ::std::vector<float> accumulation(weights.size());
  ::std::partial_sum(weights.begin(), weights.end(), accumulation.begin());
  float value = MathUtils::random() * accumulation.back();
  auto it = ::std::lower_bound(accumulation.begin(), accumulation.end(), value);
  unsigned int index = it - accumulation.begin();
  if (index == accumulation.size()) {
    --index;
  }
  return index;
}
}; // namespace MathUtils

#endif

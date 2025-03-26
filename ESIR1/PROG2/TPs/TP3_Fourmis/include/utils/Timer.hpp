#ifndef _Timer_H
#define _Timer_H

/// <summary>
/// A timer class.
/// </summary>
class Timer {
protected:
  static float m_currentTime;
  static float m_deltaTime;

public:
  /// <summary>
  /// Returns the absolute time since the beginning of the simulation.
  /// </summary>
  /// <returns></returns>
  static float time() { return m_currentTime; }

  /// <summary>
  /// Returns the time elapsed since the last time step.
  /// </summary>
  /// <returns></returns>
  static float dt() { return m_deltaTime; }

  /// <summary>
  /// Updates the time with specified time step duration.
  /// </summary>
  /// <param name="dt">The time step duration.</param>
  static void update(float dt) {
    m_currentTime += dt;
    m_deltaTime = dt;
  }
};

#endif
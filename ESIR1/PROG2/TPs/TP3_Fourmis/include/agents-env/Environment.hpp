#ifndef _Environment_H
#define _Environment_H

#include "utils/MathUtils.hpp"
#include "utils/Rectangle.hpp"
#include "utils/Vector2.hpp"
#include <SDL2/SDL.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

/// <summary>
/// An environment in which several entities can evolve.
/// </summary>
class Environment {
public:
  /// <summary>
  /// Anything inheriting from this class can be placed, moved and perceived in the environment.
  /// </summary>
  class LocalizedEntity {
  public:
    static float defaultRadius() { return 0.01f; }

  private:
    /// <summary>
    /// The position of the element
    /// </summary>
    Vector2<float> m_position;

    /// <summary>
    /// The radius of the entity
    /// </summary>
    float m_radius;

    /// <summary>
    /// The environment in which the element is placed
    /// </summary>
    Environment *m_environment;

  public:
    /// <summary>
    /// Initializes a new instance of the <see cref="LocalizedEntity" /> class.
    /// </summary>
    /// <param name="environment">The environment.</param>
    /// <param name="position">The position.</param>
    /// <param name="radius">The radius of the entity.</param>
    LocalizedEntity(Environment *environment, const Vector2<float> &position,
                    float radius = defaultRadius());

    /// <summary>
    /// Finalizes an instance of the <see cref="LocalizedEntity"/> class.
    /// </summary>
    virtual ~LocalizedEntity();

    /// <summary>
    /// Gets the position.
    /// </summary>
    /// <returns></returns>
    const Vector2<float> &getPosition() const { return m_position; }

    /// <summary>
    /// Sets the position.
    /// </summary>
    /// <param name="position">The position.</param>
    void setPosition(const Vector2<float> &position);

    /// <summary>
    /// Translates the element with the provided vector.
    /// </summary>
    /// <param name="v">The v.</param>
    void translate(Vector2<float> const &v);

    /// <summary>
    /// Sets the radius of the entity
    /// </summary>
    /// <param name="radius">The radius.</param>
    void setRadius(float radius);

    /// <summary>
    /// Gets the radius of the entity
    /// </summary>
    /// <returns></returns>
    float getRadius() const { return m_radius; }

    /// <summary>
    /// Gets the environment.
    /// </summary>
    /// <returns></returns>
    Environment *getEnvironment() const { return m_environment; }

    /// <summary>
    /// Perceives the environment from the current position, in specified direction, with the
    /// specified opening angle and within the provided extent.
    /// </summary>
    /// <param name="direction">The perception direction.</param>
    /// <param name="openingAngle">The opening angle of the perception (maximum angle between the
    /// direction and the perceived entity position).</param> <param name="extent">The extent of the
    /// perception (distance under which elements can be perceived).</param> <param
    /// name="minimumDistance">The minimum perception distance.</param> <returns></returns>
    template <class T>
    ::std::vector<T *> perceive(Vector2<float> const &direction, float openingAngle, float extent,
                                float minimumDistance = 0.01) const {
      return m_environment->perceive<T>(m_position, direction, openingAngle, extent,
                                        minimumDistance);
    }

    /// <summary>
    /// Perceives the part of the environment on which the entity stands.
    /// </summary>
    /// <returns></returns>
    template <class T>::std::vector<T *> perceive() const {
      return m_environment->perceive<T>(m_environment->cell(m_position));
    }
  };

private:
  /// <summary>
  /// The width of the environment
  /// </summary>
  unsigned int m_sizeX;

  /// <summary>
  /// The height of the environment
  /// </summary>
  unsigned int m_sizeY;

  /// <summary>
  /// The elements that evolve in the environment. [(int)X,(int)Y] coordinates are the indices in
  /// the table.
  /// </summary>
  ::std::vector<::std::vector<::std::set<LocalizedEntity *>>> m_data;

  /// <summary>
  /// For each cell in which the entity lies, call the provided function with the cell coordinates.
  /// </summary>
  /// <param name="entity">The entity.</param>
  /// <param name="function">The function to call. Its type is void(const Vector2<unsigned int> &
  /// cell)</param>
  template <class Function> void rasterize(LocalizedEntity *entity, const Function &function) {
    float extent = entity->getRadius();
    Vector2<float> position = entity->getPosition();

    // For entities with a radius lesser than a cell size, we only rasterize the current cell
    if (extent <= 1.0) {
      function(cell(position));
      return;
    }

    // General case : the entity radius is greater than a cell size
    unsigned int minX = (unsigned int)::std::floor(::std::max(position[0] - extent, 0.0f));
    unsigned int maxX =
        (unsigned int)::std::ceil(::std::min(position[0] + extent, float(m_sizeX - 1)));
    unsigned int minY = (unsigned int)::std::floor(::std::max(position[1] - extent, 0.0f));
    unsigned int maxY =
        (unsigned int)::std::ceil(std::min(position[1] + extent, float(m_sizeY - 1)));

    for (unsigned int x = minX; x <= maxX; ++x) {
      for (unsigned int y = minY; y < maxY; ++y) {
        Rectangle cellShape(Vector2<float>((float)x, (float)y), Vector2<float>(1.0f, 1.0f));
        if (cellShape.distance(position) > extent) {
          continue;
        }
        function(Vector2<unsigned int>(x, y));
      }
    }
  }
  

  /// <summary>
  /// Removes the entity from all cells it lies in.
  /// </summary>
  /// <param name="entity">The entity.</param>
  void removeEntity(LocalizedEntity *entity);

  /// <summary>
  /// Adds the entity in each cell it covers.
  /// </summary>
  /// <param name="entity">The entity.</param>
  void addEntity(LocalizedEntity *entity);

  /// <summary>
  /// Clamps the x coordinate given the width of the envionment.
  /// </summary>
  /// <param name="x">The x coordinate.</param>
  /// <returns></returns>
  float clampX(float x) const;

  /// <summary>
  /// Clamps the y coordinate given the height of the environment
  /// </summary>
  /// <param name="x">The y coordinate.</param>
  /// <returns></returns>
  float clampY(float y) const;

  /// <summary>
  /// Clamps the provided vector given the width and the height of the environment
  /// </summary>
  /// <param name="p">The p.</param>
  /// <returns></returns>
  Vector2<float> clamp(const Vector2<float> &p) const;

  /// <summary>
  /// Determines whether the specified cell is valid.
  /// </summary>
  /// <param name="cell">The cell.</param>
  /// <returns>
  ///   <c>true</c> if the specified cell is valid; otherwise, <c>false</c>.
  /// </returns>
  bool isValid(const Vector2<unsigned int> &cell) const;



public:
  /// <summary>
  /// Initializes a new instance of the <see cref="Environment"/> class.
  /// </summary>
  /// <param name="width">The width of the environment.</param>
  /// <param name="height">The height of the environment.</param>
  Environment(unsigned int width, unsigned int height);

  /// <summary>
  /// Gets the width of the environment
  /// </summary>
  /// <returns></returns>
  float getWidth() const { return (float)m_sizeX; }

  /// <summary>
  /// Gets the height of the environment.
  /// </summary>
  /// <returns></returns>
  float getHeight() const { return (float)m_sizeY; }

  /// <summary>
  /// Gets a random position in the environment
  /// </summary>
  /// <returns></returns>
  Vector2<float> randomPosition() const {
    return Vector2<float>(MathUtils::random(0.0f, (float)m_sizeX),
                          MathUtils::random(0.0f, (float)m_sizeY));
  }

  /// <summary>
  /// Converts a position into cell coordinates.
  /// </summary>
  /// <param name="position">The cell coordinates.</param>
  /// <returns></returns>
  Vector2<unsigned int> cell(Vector2<float> const &position) const;

  /// <summary>
  /// Perceives entities located in a provided cell.
  /// </summary>
  /// <param name="cell">The cell.</param>
  /// <param name="T">The type of the entities that should be perceived. Warning, this type must
  /// inherit from LocalizedEntity. <returns>The entities of type T located in the cell. </returns>
  template <class T>::std::vector<T *> perceive(const Vector2<unsigned int> &cell) const {
    assert(isValid(cell) && "Environment::perceive: invalid cell provided. Please, use "
                            "Environment::cell to convert your coordinates");
    const ::std::set<LocalizedEntity *> &elements = m_data[cell[0]][cell[1]];
    ::std::vector<T *> result;
    for (auto it = elements.begin(), end = elements.end(); it != end; ++it) {
      T *current = dynamic_cast<T *>(*it);
      if (current !=
          nullptr) // If the type of the entity is the expected one, we add it in the result
      {
        result.push_back(current);
      }
    }
    return result;
  }

  /// <summary>
  /// Perceives the specified position.
  /// </summary>
  /// <param name="position">The position of the observer.</param>
  /// <param name="direction">The direction toward which the observer looks.</param>
  /// <param name="openingAngle">The opening angle of the field of perception.</param>
  /// <param name="extent">The extent of the field of perception.</param>
  /// <param name="minimumDistance">The minimum perception distance i.e. the distance under which
  /// element are not perceived.</param> <returns></returns>
  template <class T>
  ::std::vector<T *> perceive(Vector2<float> const &position, const Vector2<float> &direction,
                              float openingAngle, float extent,
                              float minimumDistance = 0.01f) const {
    float cosAngle = cos(openingAngle);
    Vector2<float> dir = direction / direction.norm();

    ::std::vector<T *> result;

    unsigned int minX = (unsigned int)::std::floor(::std::max(position[0] - extent, 0.0f));
    unsigned int maxX =
        (unsigned int)::std::ceil(::std::min(position[0] + extent, float(m_sizeX - 1)));
    unsigned int minY = (unsigned int)::std::floor(::std::max(position[1] - extent, 0.0f));
    unsigned int maxY =
        (unsigned int)::std::ceil(std::min(position[1] + extent, float(m_sizeY - 1)));

    for (unsigned int x = minX; x <= maxX; ++x) {
      for (unsigned int y = minY; y < maxY; ++y) {
        Rectangle cellShape(Vector2<float>((float)x, (float)y), Vector2<float>(1.0f, 1.0f));
        if (cellShape.distance(position) > extent) {
          continue;
        }

        const ::std::set<LocalizedEntity *> &current = m_data[x][y];
        for (auto it = current.begin(), end = current.end(); it != end; ++it) {
          Vector2<float> targetDirection = (*it)->getPosition() - position;
          targetDirection = targetDirection / targetDirection.norm();
          if (dir * targetDirection >= cosAngle &&
              (position - (*it)->getPosition()).norm() < (*it)->getRadius() + extent &&
              (position - (*it)->getPosition()).norm() > minimumDistance) {
            T *element = dynamic_cast<T *>(*it);
            if (element != nullptr) {
              result.push_back(element);
            }
          }
        }
      }
    }
    return result;
  }

  /// <summary>
  /// Gets all instances of T referenced in this environment.
  /// </summary>
  /// <returns></returns>
  template <class T>::std::vector<T *> getAllInstancesOf() const {
    ::std::set<T *> result;
    for (size_t x = 0; x < getWidth(); ++x) {
      for (size_t y = 0; y < getHeight(); ++y) {
        std::vector<T *> tmp = perceive<T>(Vector2<unsigned int>(x, y));
        std::copy(tmp.begin(), tmp.end(), std::inserter(result, result.begin()));
      }
    }
    std::vector<T *> realResult(result.size());
    std::copy(result.begin(), result.end(), realResult.begin());
    return realResult;
  }

};

#endif

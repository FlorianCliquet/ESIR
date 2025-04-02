#include <agents-env/Environment.hpp>

Environment::LocalizedEntity::LocalizedEntity(Environment *environment,
                                              const Vector2<float> &position, float radius)
    : m_position(position), m_radius(radius), m_environment(environment) {
  m_environment->addEntity(this);
}

/// <summary>
/// Finalizes an instance of the <see cref="LocalizedEntity"/> class.
/// </summary>

Environment::LocalizedEntity::~LocalizedEntity() { m_environment->removeEntity(this); }

void Environment::LocalizedEntity::setPosition(const Vector2<float> &position) {
  Vector2<float> clamped = m_environment->clamp(position);
  m_environment->removeEntity(this);
  m_position = clamped;
  m_environment->addEntity(this);
}

void Environment::LocalizedEntity::translate(Vector2<float> const &v) {
  setPosition(m_position + v);
}

/// <summary>
/// Sets the radius of the entity
/// </summary>
/// <param name="radius">The radius.</param>

void Environment::LocalizedEntity::setRadius(float radius) {
  m_environment->removeEntity(this);
  m_radius = radius;
  m_environment->addEntity(this);
}

void Environment::removeEntity(LocalizedEntity *entity) {
  auto function = [this, entity](const Vector2<unsigned int> &cell) {
    m_data[cell[0]][cell[1]].erase(entity);
  };
  rasterize(entity, function);
}

/// <summary>
/// Adds the entity in each cell it covers.
/// </summary>
/// <param name="entity">The entity.</param>

void Environment::addEntity(LocalizedEntity *entity) {
  auto function = [this, entity](const Vector2<unsigned int> &cell) {
    m_data[cell[0]][cell[1]].insert(entity);
  };
  rasterize(entity, function);
}

float Environment::clampX(float x) const {
  return MathUtils::clamp(0.0f, (float)m_sizeX - 0.001f, x);
}

float Environment::clampY(float y) const {
  return MathUtils::clamp(0.0f, (float)m_sizeY - 0.001f, y);
}

Vector2<float> Environment::clamp(const Vector2<float> &p) const {
  return Vector2<float>(clampX(p[0]), clampY(p[1]));
}

bool Environment::isValid(const Vector2<unsigned int> &cell) const {
  return cell[0] < m_sizeX && cell[1] < m_sizeY;
}

Environment::Environment(unsigned int width, unsigned int height)
    : m_sizeX(width), m_sizeY(height),
      m_data(width, ::std::vector<std::set<LocalizedEntity *>>(height)) {}

Vector2<unsigned int> Environment::cell(Vector2<float> const &position) const {
  Vector2<float> clamped = clamp(position);
  return Vector2<unsigned int>((unsigned int)clamped[0], (unsigned int)clamped[1]);
}

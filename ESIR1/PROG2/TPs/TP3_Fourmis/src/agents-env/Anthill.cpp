/**
 * @file Anthill.cpp
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "agents-env/Anthill.hpp"
#include "renderer/Renderer.hpp"
Anthill::Anthill(Environment *environment, const Vector2<float> &pos)
    : Agent(environment, pos, 10.0f) {}

void Anthill::depositFood(float quantity) { m_quantity += quantity; }

void Anthill::update() {
  Renderer::getInstance()->drawCircle(getPosition(), getRadius(), Renderer::Color(0, 0, 255, 255));
}
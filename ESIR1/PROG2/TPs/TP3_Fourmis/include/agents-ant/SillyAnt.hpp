/**
 * @file SillyAnt.h
 * @author Cliquet Florian (florian.cliquet@etudiant.univ-rennes.fr)
 * @brief
 * @version 0.1
 * @date 2025-03-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef SILLY_ANT_H
#define SILLY_ANT_H

#include "agents-ant/AntBase.hpp"
#include "agents-env/Anthill.hpp"
#include "agents-env/Environment.hpp"
class SillyAnt : public AntBase {
public:
  SillyAnt(Environment *environment, Anthill *anthill);
  void update() override;
};

#endif
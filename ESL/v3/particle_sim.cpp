/**
 * @file   particle_sim.cpp
 * @brief  Particle simulator class is defined in this file.
 * @date   2023-03-21
 * @name   ee98_2019
*/

#include "particle_sim.hpp"

#define MIN_DELAY_TIME   (1u)
#define MAX_DELAY_TIME   (10u)

#define HIT (50u)    ///< Value which will activate the particle

ParticleSimulator::ParticleSimulator(sc_core::sc_module_name name, ParticleSimulator::State initial_state) : sc_module(name)
{
  this->m_state = initial_state;
  SC_THREAD(simulate);
  sensitive << explosion;
  srand(time(NULL));
}

void ParticleSimulator::setState(ParticleSimulator::State new_state)
{
  this->m_state = new_state;
}

ParticleSimulator::State ParticleSimulator::getState(void) const
{
  return this->m_state;
}

void ParticleSimulator::simulate(void)
{
  while(true)
  {
    if (this->m_state == ParticleSimulator::State::Active)
    {
      std::cout << "Exploding..." << std::endl;
      int rand_delay = (rand() % (MAX_DELAY_TIME - MIN_DELAY_TIME + 1)) + MIN_DELAY_TIME;
      wait(rand_delay, sc_core::SC_NS);
      std::cout << "Boom!!!" << std::endl;
      explosion.notify(sc_core::SC_ZERO_TIME);
      this->m_state = ParticleSimulator::State::Exploded;
      break;
    }

    if (this->m_state == ParticleSimulator::State::Inactive)
    {
      std::cout << "Waiting..." << std::endl;
      wait(explosion);
      std::cout << "Activated" << std::endl;
      int random_num = (rand() % (100 - 0 + 1)) + 0;
      if (true)
      {
        this->m_state = ParticleSimulator::State::Active;
      }
    }
  }
}

/**
 * @file   particle_sim.hpp
 * @brief  Particle simulator class is declared in this file.
 * @date   2023-03-21
 * @name   ee98_2019
*/

#ifndef PARTICLE_SIM_HPP_
#define PARTICLE_SIM_HPP_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <systemc>

SC_MODULE(ParticleSimulator)
{
public:
  SC_HAS_PROCESS(ParticleSimulator);
  enum State
  {
    Inactive,
    Active,
    Exploded
  };

protected:
  ParticleSimulator::State m_state;

public:
  static sc_core::sc_event explosion;

  ParticleSimulator(sc_core::sc_module_name name, ParticleSimulator::State initial_state);

  void setState(ParticleSimulator::State new_state);
  ParticleSimulator::State getState(void) const;
  void simulate(void);
};

#endif  /* PARTICLE_SIM_HPP_ */

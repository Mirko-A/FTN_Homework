/**
 * @file   particle_sim.hpp
 * @brief  Particle simulator class is declared in this file.
 * @date   2023-03-21
 * @name   ee98_2019
*/

#ifndef PARTICLE_SIM_HPP_
#define PARTICLE_SIM_HPP_

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <systemc>

SC_MODULE(Particle)
{
public:
  SC_HAS_PROCESS(Particle);
  enum State
  {
    Inactive,
    Active,
    Exploded
  };
 
protected:
  Particle::State m_state;
  
public:
  static sc_core::sc_event explosion;

  Particle(sc_core::sc_module_name name, Particle::State initial_state);

  void setState(Particle::State new_state);
  Particle::State getState(void) const;
  void simulate(void);
};

SC_MODULE(Simulator)
{
public:
  SC_HAS_PROCESS(Simulator);

  Particle* particles[1000];

  Simulator(sc_core::sc_module_name name);
  
  void run(void);
};

#endif  /* PARTICLE_SIM_HPP_ */

/**
 * @file   main.cpp
 * @brief  Entry point for ParticleSimulator project.
 * @date   2023-03-21
 * @name   ee98_2019
*/

#include "particle_sim.hpp"

int sc_main(int argc, char* argv[])
{
    Simulator sim("Simulator");
    
    Particle* p = new Particle("particle0", Particle::State::Active);
    sim.particles[0] = p;

    for (size_t i = 1; i < 1000; i++)
    {
        std::string particle_name = "particle";
        particle_name.append(std::to_string(i));
        Particle* p = new Particle(particle_name.c_str(), Particle::State::Inactive);
        sim.particles[i] = p;
    }
  
    sc_start(2000, sc_core::SC_NS);
  
    return 0;
}

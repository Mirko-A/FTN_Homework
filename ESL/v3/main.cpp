#include <iostream>
#include <systemc>
#include <string>
#include "particle_sim.hpp"

int sc_main(int argc, char* argv[])
{
  ParticleSimulator* particles[1000];

  ParticleSimulator particle("particle0", ParticleSimulator::State::Active);
  particles[0] = &particle;

  for (size_t i = 1; i < 1000; i++)
  {
    std::string particle_name = "particle";
    particle_name.append(std::to_string(i));
    ParticleSimulator particle(particle_name.c_str(), ParticleSimulator::State::Inactive);
    particles[i] = &particle;
  }

  sc_start(2000, sc_core::SC_NS);

  size_t exploded_cnt = 0u;
  for (int i = 0; i < 1000; i++)
  {
    if (particles[i]->getState() == ParticleSimulator::State::Exploded)
    {
      exploded_cnt++;
    }
  }

  std::cout << "NUMBER OF EXPLODED PARTICLES: " << exploded_cnt << std::endl;

  return 0;
}

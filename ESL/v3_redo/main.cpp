/**
 * @file   main.cpp
 * @brief  Entry point for ParticleSimulator project.
 * @date   2023-03-21
 * @name   ee98_2019
*/

#include "particle_sim.hpp"

int sc_main(int argc, char* argv[])
{
    Simulator uut("Simulator");
  
    sc_start(2000, sc_core::SC_NS);
  
    return 0;
}

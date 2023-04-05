/**
 * @file   particle_sim.cpp
 * @brief  Particle simulator class is defined in this file.
 * @date   2023-03-21
 * @name   ee98_2019
*/

#include "particle_sim.hpp"

#define MIN_DELAY_TIME   (1u)
#define MAX_DELAY_TIME   (10u)

// Value which will activate the particle
#define HIT (50u)

// PARTICLE IMPLEMENTATION

sc_core::sc_event Particle::explosion;

Particle::Particle(sc_core::sc_module_name name, Particle::State initial_state) : sc_module(name)
{
    this->m_state = initial_state;
    SC_THREAD(simulate);
    sensitive << explosion;
    srand(time(NULL));
}

void Particle::setState(Particle::State new_state)
{
    this->m_state = new_state;
}

Particle::State Particle::getState(void) const
{
    return this->m_state;
}

void Particle::simulate(void)
{
    while(true)
    {
        if (this->m_state == Particle::State::Active)
        {
            std::cout << "Exploding..." << std::endl;
            int rand_delay = (rand() % (MAX_DELAY_TIME - MIN_DELAY_TIME + 1)) + MIN_DELAY_TIME;
            wait(rand_delay, sc_core::SC_NS);
            std::cout << "Boom!!!" << std::endl;
            explosion.notify(sc_core::SC_ZERO_TIME);
            this->m_state = Particle::State::Exploded;
            break;
        }
	    
        if (this->m_state == Particle::State::Inactive)
        {
            std::cout << "Waiting..." << std::endl;
            wait(explosion);
            std::cout << "Activated" << std::endl;
            int random_num = (rand() % (100 - 0 + 1)) + 0;
            if (random_num == HIT)
            {
                this->m_state = Particle::State::Active;
            }
        }
    }
}

// SIMULATOR IMPLEMENTATION

Simulator::Simulator(sc_core::sc_module_name name) : sc_module(name)
{
	SC_THREAD(run);
	
	Particle particle("particle0", Particle::State::Active);
    particles[0] = &particle;

    for (size_t i = 1; i < 1000; i++)
    {
        std::string particle_name = "particle";
        particle_name.append(std::to_string(i));
        Particle particle(particle_name.c_str(), Particle::State::Inactive);
        particles[i] = &particle;
    }
}

Simulator::run()
{
	bool stop_sim = true;
	wait(15, sc_core::SC_NS);
	
	for (int i = 0; i < 1000; i++)
	{
		if (this->particles[i]->getState() == Particle::State::Activate) 
		{
			stop_sim = false;
		}
	}
	
	if (stop_sim == true) 
    {
	    size_t exploded_cnt = 0u;
        for (int i = 0; i < 1000; i++)
        {
            if (this->particles[i]->getState() == ParticleSimulator::State::Exploded)
            {
                exploded_cnt++;
            }
        }
        std::cout << "NUMBER OF EXPLODED PARTICLES: " << exploded_cnt << std::endl;
		
		sc_core::sc_stop;
	}
}
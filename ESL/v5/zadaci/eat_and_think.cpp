#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <systemc>

#define PHILOSOPHER_NUM 5u

#define MIN_THINK_TIME 3
#define MAX_THINK_TIME 7

sc_core::sc_mutex forks[5];

int holding_one_count = 0;

SC_MODULE(Philosopher)
{
public:
    SC_HAS_PROCESS(Philosopher);
    
private:
    int m_fork1;
    int m_fork2;
	
public:
    Philosopher(sc_core::sc_module_name name, int fork1_pos, int fork2_pos);
    
	void eatAndThink(void);
};

Philosopher::Philosopher(sc_core::sc_module_name name) : sc_module(name)
{
    SC_THREAD(eatAndThink);
    srand(time(NULL));
}

void Philosopher::eatAndThink(void)
{
    while(true)
    {
        int rand_delay = (rand() % (MAX_THINK_TIME - MIN_THINK_TIME + 1)) + MIN_THINK_TIME;
		std::cout << "[" << m_fork1 << "]" << "I will think for " << rand_delay << " seconds..." std::endl;
		wait(rand_delay, sc_core::SC_NS);
		
		forks[m_fork1].lock();
		if (++holding_one_count == PHILOSOPHER_NUM)
        {
			std::cout << "Impass has been reached...stopping the simulation." << std::endl;
			sc_core::sc_stop(); 
		}
		forks[m_fork2].lock();
		holding_one_count--;
		
		std::cout << "[" << m_fork1 << "]" << "Too hungry. Eating..." << std::endl;
		wait(2, sc_core::SC_NS);
		
	    forks[m_fork1].unlock();
		forks[m_fork2].unlock();
    }
}

int sc_main(int argc, char* argv[])
{
    Philosopher* philosophers[PHILOSOPHER_NUM];

    for (size_t it = 0; it < PHILOSOPHER_NUM; it++)
	{
		std::string philosopher_name = "P";
        philosopher_name.append(std::to_string(i));
		Philosopher p(philosopher_name.c_str(), it, ((it + 1) == PHILOSOPHER_NUM ? 0 : (it + 1)));
		
		philosophers[i] = &p;
	}

    sc_start(200, sc_core::SC_NS);

    return 0;
}

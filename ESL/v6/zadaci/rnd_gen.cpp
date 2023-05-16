#include "rnd_gen.h"

#define MIN_RAND (0)
#define MAX_RAND (99)

#define MIN_DELAY_TIME (5)
#define MAX_DELAY_TIME (10)

rnd_gen::rnd_gen(sc_module_name name) : sc_module(name)
{
    cout << name() << " constructed.\n";
    SC_METHOD(process);
    sensitive << gen;
}

void rnd_gen::process()
{
    if (gen->read() == true)
    {
        std::cout << name() << " activated!" << std::endl;
        int rand_delay = (rand() % (MAX_DELAY_TIME - MIN_DELAY_TIME + 1)) + MIN_DELAY_TIME;
        wait(rand_delay, sc_core::SC_NS);

        int rand_num = (rand() % (MAX_RAND - MIN_RAND + 1)) + MIN_RAND;
        std::cout << "Sending " << num << "to coll..." << std::endl;
        num->write(rand_num);
        std::cout << "Activating next generator..." << std::endl;
    }
}

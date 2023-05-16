#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <systemc>

SC_MODULE(rnd_gen)
{
public:
	SC_HAS_PROCESS(rnd_gen);

	rnd_gen(sc_module_name);

	sc_in<bool>  gen;
	sc_out<bool> start;
	sc_out<int> num;
protected:
	void process();
};

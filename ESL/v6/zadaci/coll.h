#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <systemc>

// When initializing FIFO, use its constructor
// to specify the size (100 in this case)

SC_MODULE(coll)
{
public:
	SC_HAS_PROCESS(coll);

	coll(sc_module_name);

	sc_in<int> num0;
	sc_in<int> num1;
	sc_in<int> num2;

	sc_export<sc_fifo_out_if<int>> nums;
protected:
	sc_fifo<int> f0;

	void num0_proc();
	void num1_proc();
	void num2_proc();
};

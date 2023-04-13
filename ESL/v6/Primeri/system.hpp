#ifndef _SYS_HPP_
#define _SYS_HPP_

#include <systemc>
#include "module0.hpp"
#include "module1.hpp"

namespace comm
{
using namespace sc_core;

SC_MODULE(system)
{
public:
	SC_HAS_PROCESS(system);

	system(sc_module_name);

	sc_port<sc_signal_in_if<int> > p0;
	sc_in<int> p1;
	sc_out<int> p2;
	sc_export< sc_signal_out_if<int> > p3;
protected:
	void proc0();
	void proc1();

	sc_fifo<int> f0;
	sc_signal<int> s0;
	sc_event e0;
	module0 m0;
	module1 m1;
	sc_mutex x0;
};


}
#endif

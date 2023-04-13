#ifndef _MODULE0_HPP_
#define _MODULE0_HPP_

#include <systemc>

namespace comm
{
using namespace sc_core;

SC_MODULE(module0)
{
public:
	SC_HAS_PROCESS(module0);

	module0(sc_module_name);

	sc_in<int> pnum;
	sc_port< sc_fifo_out_if<int> > pfifo;
	sc_out<int> pp;
protected:
	void process();
};

}
#endif

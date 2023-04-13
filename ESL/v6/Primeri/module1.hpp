#ifndef _MODULE1_HPP_
#define _MODULE1_HPP_

#include <systemc>

namespace comm
{
	using namespace sc_core;

	SC_MODULE(module1)
	{
	public:
		SC_HAS_PROCESS(module1);

		module1(sc_core::sc_module_name);

		sc_fifo_in<int> pfifo;
		sc_export<sc_signal_out_if<int> > pexp;
		//sc_port< sc_fifo_in_if<int> > pfifo;
	protected:
		void process();
		sc_signal<int> s0;
	};

}
#endif

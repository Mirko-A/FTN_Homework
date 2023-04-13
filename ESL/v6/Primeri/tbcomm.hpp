#ifndef _TBCOMM_HPP_
#define _TBCOMM_HPP_

#include <systemc>
#include "system.hpp"

namespace comm
{

SC_MODULE(tbcomm)
{
public:
	SC_HAS_PROCESS(tbcomm);

	tbcomm(sc_module_name);

protected:
	system uut;
	sc_signal<int> num0;
	sc_signal<int> num1;
	sc_signal<int> res;

	void driver();
	void monitor();
};

}
#endif

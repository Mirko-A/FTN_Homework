#include <systemc>

#include "tbcomm.hpp"

int sc_main(int argc, char* argv[])
{
	comm::tbcomm uut("TB");

	sc_start(50, sc_core::SC_NS);

    return 0;
}

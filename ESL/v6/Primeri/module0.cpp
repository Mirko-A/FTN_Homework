#include "module0.hpp"

namespace comm
{
	using namespace sc_core;
	using namespace std;

	module0::module0(sc_module_name n) : sc_module(n)
	{
		cout << name() << " constructed.\n";
		SC_METHOD(process);
		sensitive << pnum;
	}

	void module0::process()
	{
		int v = pnum->read();
		cout << name() << " read: " << v << endl;
		v++;
		pfifo->write(v);
		pp->write(v);
	}
}

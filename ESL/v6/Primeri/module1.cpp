#include "module1.hpp"

namespace comm
{
	using namespace sc_core;
	using namespace std;

	module1::module1(sc_module_name n) : sc_module(n)
	{
		//pexp(s0);
		pexp.bind(s0);
		cout << name() << " constructed.\n";
		SC_THREAD(process);
	}

	void module1::process()
	{
		while(1)
		{
			if (pfifo->num_available())
			{
				int v = pfifo->read();
				cout << name() << " read: "
					 << v << endl;
				s0.write(v);
			}
			wait(1, SC_NS);
		}
	}

}

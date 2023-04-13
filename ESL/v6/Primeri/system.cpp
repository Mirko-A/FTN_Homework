#include "system.hpp"

namespace comm
{
	using namespace sc_core;
	using namespace std;

	system::system(sc_module_name n) :
		sc_module(n),
		f0("f0"), // Member initializer list
		m0("m0"),
		m1("m1"),
		x0("x0")
	{
		cout << name() << " constructed.\n";
		m0.pnum(p0);
		m0.pfifo.bind(f0);
		m0.pp(s0);
		// Position connecting is possible
		// but not recommended.
		//m0(p0, f0);
		m1.pfifo(f0);
		p3(m1.pexp);

		SC_THREAD(proc0);
		sensitive << p1 << s0;
		SC_THREAD(proc1);
	}

	void system::proc0()
	{
		sc_process_handle h = sc_get_current_process_handle();
		cout << h.name() << " of type " << h.proc_kind() << " activated @ " << sc_time_stamp() << endl;
		x0.lock();
		wait(1, SC_NS);
		x0.unlock();
		cout << "Proc0 deactivated " << sc_time_stamp() << endl;
		e0.notify();
	}

	void system::proc1()
	{
		int v = 200;
		while(1)
		{
			wait(e0);
			cout << "Event e0 happened " << sc_time_stamp() << endl;
			x0.lock();
			wait(2, SC_NS);
			x0.unlock();
			p2.write(v++);
		}
	}
}

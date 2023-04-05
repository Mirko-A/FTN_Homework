#include <systemc>
#include <iostream>

using namespace sc_core;

SC_MODULE(BusGen)
{
public:
	SC_HAS_PROCESS(BusGen);

	BusGen(sc_module_name name, sc_mutex* );

protected:
	sc_mutex* m;

	void proc();
};

BusGen::BusGen(sc_module_name name, sc_mutex* m) : sc_module(name), m(m)
{
	SC_THREAD(proc);
}

void BusGen::proc()
{
	while(1)
	{
		wait(5, SC_NS);
		m->lock();
		std::cout << "@ " << sc_time_stamp() <<
			" bus locked by " << name() << std::endl;
		wait(3, SC_NS);
		m->unlock();
	}
}

int sc_main(int argc, char* argv[])
{
	sc_mutex mtx;
	BusGen g1("g1", &mtx);
	BusGen g2("g2", &mtx);

	sc_start(100, SC_NS);

    return 0;
}

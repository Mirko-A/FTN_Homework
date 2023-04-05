#include <systemc>
#include <iostream>

using namespace sc_core;
using namespace std;

SC_MODULE(TwoFlops)
{
public:
	SC_HAS_PROCESS(TwoFlops);

	TwoFlops(sc_module_name);

	void print();

protected:
	bool v0, v1;

	void change();
};

TwoFlops::TwoFlops(sc_module_name name) : sc_module(name)
{
	SC_THREAD(change);
	v0 = false;
	v1 = true;
}

void TwoFlops::change()
{
	while(1)
	{
		wait(5, SC_NS);
		v0 = v1;
		v1 = v0;
	}
}

void TwoFlops::print()
{
	cout
		<< "v0 = " << v0 << endl
		<< "v1 = " << v1 << endl;
}

int sc_main(int argc, char* argv[])
{
	TwoFlops uut("UUT");

	sc_start(200, SC_NS);

	uut.print();

    return 0;
}

#include "tbcomm.hpp"

namespace comm
{
	using namespace sc_core;
	using namespace std;

	tbcomm::tbcomm(sc_module_name n) : sc_module(n), uut("UUT")
	{
		cout << name() << " constructed.\n";
		uut.p0(num0);
		uut.p1(num1);
		uut.p2(res);
		SC_THREAD(driver);
		SC_METHOD(monitor);
		sensitive << uut.p3;
	}

	void tbcomm::driver()
	{
		int v = 0xA;
		int t = 100;
		while(1)
		{
			num0.write(v++);
			wait(2, SC_NS);
			num1.write(t--);
			wait(1, SC_NS);
		}
	}

	void tbcomm::monitor()
	{
		cout << "From export: " << uut.p3->read() << endl;
	}
}

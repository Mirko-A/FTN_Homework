#include <systemc>
#include <iostream>

using namespace sc_core;
using namespace std;

SC_MODULE(TwoFlops)
{
public:
SC_HAS_PROCESS(TwoFlops);
TwoFlops (sc_module_name);
void print();
protected:
sc_signal<bool> s0, s1;
void change();
};

TwoFlops::TwoFlops(sc_module_name name) : sc_module(name)
{
SC_THREAD(change);
s0 = false;
s1 = true;
}
void TwoFlops::change()
{
while (1)
{
wait(5, SC_NS);
s0 = s1;
// s0.write(s1.read()); // This is alternative
s1 = s0;
// s1.write(s0.read()); // This is alternative
}
}
void TwoFlops::print()
{
cout
<< " s0 _=_" << s0 << endl
<< " s1 _=_" << s1 << endl;
}

int sc_main(int argc, char∗ argv[])
{
	TwoFlops uut("UUT");
    sc_start(200, SC_NS);
    uut.print();
    return 0;
}
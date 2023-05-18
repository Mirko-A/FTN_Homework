#include "coll.h"

coll::coll(sc_module_name name) : sc_module(name)
{
    cout << name() << " constructed.\n";
    SC_METHOD(num0_proc);
    sensitive << num0;

    SC_METHOD(num1_proc);
    sensitive << num1;

    SC_METHOD(num2_proc);
    sensitive << num2;
}

void coll::num0_proc()
{
    f0.write(num0->read());

    if (f0.num_free() == 0)
    {

    }
}

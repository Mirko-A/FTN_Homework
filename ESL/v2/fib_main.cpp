#include <stdio.h>
#include "fib_randomizer.hpp"

#define SIM_DURATION  20

int sc_main(int argc, char* argv[])
{
  FibonacciRandomizer fib_lotto("FibonacciLotto");

  std::cout << " Simulacija zapoceta..." << std::endl;
  sc_start(SIM_DURATION, sc_core::SC_SEC);
  std::cout << " Simulacija zavrsena: " << sc_core::sc_time_stamp() << std::endl;

  return 0;
}

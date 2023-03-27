/**
 * @file   fib_randomizer.hpp
 * @brief  Fibonacci randomizer class and is declared in this file.
 * @date   2023-03-14
 * @name   ee98_2019
*/

#ifndef FIB_RANDOMIZER_HPP_
#define FIB_RANDOMIZER_HPP_

#include <systemc>
#include <deque>

SC_MODULE(FibonacciRandomizer)
{
public:
  SC_HAS_PROCESS(FibonacciRandomizer);

  FibonacciRandomizer(sc_core::sc_module_name name);

  void generateNumber(void);
  void listNumbers(void);

protected:
  std::deque<int> fibonacci_numbers;
};

#endif  /* FIB_RANDOMIZER_HPP_ */

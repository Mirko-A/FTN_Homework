/**
 * @file   fib_randomizer.cpp
 * @brief  Fibonacci randomizer class and is defined in this file.
 * @date   2023-03-14
 * @name   ee98_2019
*/

#include <cstdlib>
#include <ctime>
#include "fib_randomizer.hpp"

#define MIN_DELAY_TIME   (10u)
#define MAX_DELAY_TIME   (100u)
#define FIBONACCI_RANGE  (64u)

FibonacciRandomizer::FibonacciRandomizer(sc_core::sc_module_name name)
{
  SC_THREAD(generateNumber);
  SC_THREAD(listNumbers);
  srand(time(NULL));
}

void FibonacciRandomizer::generateNumber(void)
{
  while(true)
  {
    int current_num_count = fibonacci_numbers.size();
    int rand_delay = (rand() % (MAX_DELAY_TIME - MIN_DELAY_TIME + 1)) + MIN_DELAY_TIME;

    if (current_num_count == 0)
    {
      wait(rand_delay);
      rand_delay = (rand() % (MAX_DELAY_TIME - MIN_DELAY_TIME + 1)) + MIN_DELAY_TIME;
      fibonacci_numbers.push_back(0);
      wait(rand_delay);
      fibonacci_numbers.push_back(1);
    }
    else
    {
      int next_fibonacci = fibonacci_numbers.at(current_num_count - 1) + fibonacci_numbers.at(current_num_count - 2);
      if (current_num_count % FIBONACCI_RANGE == 0)
      {
        wait(rand_delay);
        fibonacci_numbers.push_back(next_fibonacci);
        wait(rand_delay);
        rand_delay = (rand() % (MAX_DELAY_TIME - MIN_DELAY_TIME + 1)) + MIN_DELAY_TIME;
        fibonacci_numbers.push_back(0);
        wait(rand_delay);
        rand_delay = (rand() % (MAX_DELAY_TIME - MIN_DELAY_TIME + 1)) + MIN_DELAY_TIME;
        fibonacci_numbers.push_back(1);
      }
      else
      {
        fibonacci_numbers.push_back(next_fibonacci);
      }
    }

    wait(rand_delay, sc_core::SC_NS);
  }
}

void FibonacciRandomizer::listNumbers(void)
{
  while(true)
  {
    wait(1, sc_core::SC_SEC);

    int current_num_count = fibonacci_numbers.size();
    fibonacci_numbers.clear();
    std::cout << sc_core::sc_time_stamp();
    std::cout << " U prethodnoj sekundi upisano je " << current_num_count << " elemenata." << std::endl;
  }
}


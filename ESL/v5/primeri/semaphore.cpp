#include <systemc>
#include <iostream>
#include <list>
#include <string>

using namespace sc_core;

SC_MODULE(Car)
{
public:
	SC_HAS_PROCESS(Car);

	Car(sc_module_name name, sc_semaphore* );

protected:
	sc_semaphore* s;

	void proc();
};

Car::Car(sc_module_name name, sc_semaphore* s) : sc_module(name), s(s)
{
	SC_THREAD(proc);
}

void Car::proc()
{
	wait(rand()%17 + 3, SC_NS);
	while(1)
	{
		s->wait();
		std::cout
			<< "@ " << sc_time_stamp() << " "
			<< name() << " entered. Places left "
			<< s->get_value() << std::endl;
		wait(rand()%37 + 3, SC_NS);
		s->post();
	}
}

int sc_main(int argc, char* argv[])
{
	const int NUMBER_OF_PLACES = 50;

	sc_semaphore park(NUMBER_OF_PLACES);

	std::list<Car*> cars;
	for (int i = 0; i < 100; ++i)
	{
		std::string instName = "Car" + std::to_string(i);
		Car* c = new Car(instName.c_str(), &park);
		cars.push_back(c);
	}

	sc_start(200, SC_NS);

	std::list<Car*>::iterator it;
	for (it = cars.begin(); it != cars.end(); ++it)
		delete *it;

    return 0;
}

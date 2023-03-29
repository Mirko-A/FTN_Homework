#include <iostream>
#include <cstdlib>
#include <ctime>
#include <systemc>

#define MIN_DELAY_TIME 3
#define MAX_DELAY_TIME 7

int passed_cnt = 0u;
int attempt_num = 0u;

SC_MODULE(DoorSim)
{
public:
    SC_HAS_PROCESS(DoorSim);
    
    enum State
    {
      WaitingA,
      WaitingB,
      WaitingC
    };
    
private:
    DoorSim::State m_state;
    
public:
    sc_core::sc_event door_event;
    
    DoorSim(sc_core::sc_module_name name);
    DoorSim::State getState(void) const;
    
    void simulateHuman(void);
    void simulateDoor(void);
};

DoorSim::DoorSim(sc_core::sc_module_name name) : sc_module(name)
{
    SC_THREAD(simulateHuman);
    sensitive << door_event;
    SC_THREAD(simulateDoor);
    this->m_state = DoorSim::State::WaitingA;
}

void DoorSim::simulateHuman(void)
{
    while(true)
    {
        attempt_num++;
        
        double time1 = sc_core::sc_time_stamp().to_seconds();
        wait(door_event);
        double time2 = sc_core::sc_time_stamp().to_seconds();
        double deltaTime = time2 - time1;
    
        std::cout << "Wait time: " << deltaTime << std::endl;
    
        if (deltaTime < 5.0)
        {
            if (this->m_state == WaitingA) 
            { 
                this->m_state = WaitingB; 
            }
            else if (this->m_state == WaitingB) 
            { 
                this->m_state = WaitingC; 
            }
            else if (this->m_state == WaitingC) 
            { 
                passed_cnt++;

                this->m_state = WaitingA;  
            }
        }
        else
        {
            this->m_state = WaitingA;
        }
    }
}

void DoorSim::simulateDoor(void)
{
    while(true)
    {
        int rand_delay = (rand() % (MAX_DELAY_TIME - MIN_DELAY_TIME + 1)) + MIN_DELAY_TIME;
        wait(rand_delay, sc_core::SC_SEC);
        door_event.notify();
    }
}

int sc_main(int argc, char* argv[])
{
    DoorSim uut("UUT");

    sc_start(1000, sc_core::SC_SEC);

    std::cout << "NUMBER OF FAILED ATTEMPTS: " << attempt_num << std::endl;
    std::cout << "NUMBER OF PASSED PEOPLE: " << passed_cnt << std::endl;
    std::cout << "SUCCESS RATIO: " << (passed_cnt/attempt_num) << std::endl;

    return 0;
}

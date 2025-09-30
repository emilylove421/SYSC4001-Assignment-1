/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include<interrupts.hpp>
#include <stdlib.h>
#include <string>
int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/
    int time = 0;
    int internum = 0;
    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);
        
        /******************ADD YOUR SIMULATION CODE HERE*************************/
        //code to execute if the instruction is from the I/O or another device
        if (activity == "SYSCALL"){
            std::string execution1 = "";
            int newTime = 0;
            int partTime = 0;
            
            //call boilerplate method
            std::tie(execution1, partTime) = intr_boilerplate(time, duration_intr, 10, vectors);
            execution.append(execution1);
            newTime = partTime;

            //get I/O device delay time
            int delay_time = delays[duration_intr];
            //call io method
            std::tie(execution1, partTime) = intr_io(newTime, duration_intr, 10, vectors, delay_time);
            execution.append(execution1);
            time = partTime;
        }
        else if (activity == "END_IO"){
            int r = (rand() % (50 - 1 + 1)) + 1;
            std::string execution1 = (std::to_string(time) +", "+ std::to_string(r) + ", end of i/o " + std::to_string(duration_intr) + " :interrupt\n");
            execution.append(execution1);
        }
        //code to execute from the CPU
        else{
            int newTime = time + duration_intr;
            std::string execution1 = (std::to_string(time) +", "+ std::to_string(duration_intr) + ", CPU burst\n");
            execution.append(execution1);
            time = newTime;
        }

        
        // append the activity and duration to the execution file
        //execution.append(std::to_string(time) +" "+ std::to_string(duration_intr) + "\n");
        //time = time + duration_intr;
        internum = internum + 1;
        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}

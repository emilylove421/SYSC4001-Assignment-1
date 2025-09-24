/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include<interrupts.hpp>
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

    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);
        
        /******************ADD YOUR SIMULATION CODE HERE*************************/
        
        if (activity != "CPU"){
            auto [execution1, newTime] = intr_boilerplate(time, duration_intr, 10, vectors);
            execution.append(execution1);
        }
        else{
            int newTime = time + duration_intr;
            std::string execution1 = (std::to_string(time) +", "+ std::to_string(duration_intr) + ", CPU burst\n");
            execution.append(execution1);
        }

        
        // append the activity and duration to the execution file
        //execution.append(std::to_string(time) +" "+ std::to_string(duration_intr) + "\n");
        time = time + duration_intr;
        internum = internum + 1;
        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}

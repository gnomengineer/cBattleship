#ifndef _PROCESS_H
#define _PROCESS_H

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>

class Process {
    FILE *handle;

    public:
        Process(std::string executable, std::vector<std::string> arguments) {
            std::string cmd = executable;
            std::for_each(arguments.begin(), arguments.end(), [&cmd](std::string element) {
                    cmd += " " + element;
            });
            handle = popen(cmd.c_str(), "W");
        }
        virtual ~Process() {
            pclose(handle);
        }
        Process(const Process & other) = delete;
        Process(Process && other) = delete;

        void write(std::string input) {
            fprintf(handle, "%s", input.c_str());
        }

        std::string read() {
            std::string output = "";
            const int buffer_size = 256;
            char buffer[buffer_size] = {};
            while(!feof(handle)) {
                if(fgets(buffer, buffer_size, handle) != NULL) {
                    output += buffer;
                }
            }
            return output;
        }
};

#endif /* _PROCESS_H */

#include "util.h"

std::string getCommandResult(std::string a_cmd){
    std::array<char, 2014> buffer;
    std::string res;
    std::shared_ptr<std::FILE> pipe(popen(a_cmd.c_str(), "r"), pclose);
    while (!std::feof(pipe.get())) {
        if (std::fgets(buffer.data(), 128, pipe.get()) != NULL)
            res += buffer.data();
    }
    return res.substr(0, res.size()-1);
}
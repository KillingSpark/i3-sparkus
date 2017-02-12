#pragma once

#include <memory>
#include <array>

string getCommandResult(string a_cmd){
    array<char, 2014> buffer;
    string res;
    shared_ptr<FILE> pipe(popen(a_cmd.c_str(), "r"), pclose);
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            res += buffer.data();
    }
    return res.substr(0, res.size()-1);
}
#include <iostream>
#include <limits>
#include <sstream>

#include "Interpreter.h"

using namespace std;

int main(int argc, char** argv) {
    int seed = 0;
    std::string filename = std::string();
    if (argc == 2 || argc == 3) {
        filename = argv[1];
        if (argc == 3) {
            istringstream str_seed (argv[2]);
            str_seed >> seed;
        }
    } else if (argc != 1) {
        cout << "Invalid number of arguments. Format is [filename] [seed]." << endl;
        return 1;
    }

    Interpreter inter(filename, seed);
    inter.init();

    std::string cmd;
    while (cin >> cmd) {
        if (cmd != "q") {
            inter.command(cmd);
        }
        if (cmd == "nst") {
            inter.nextFloor();
        }
        if (cmd == "q") {
            break;
        }
    }
    return 0;
}

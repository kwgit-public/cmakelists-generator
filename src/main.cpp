#include <iostream>
#include "generator.hpp"

#define VERSION "1.0.0"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Usage: ./cmake-generator {project_path}" << endl;
        return -1;
    }

    string dir_path = argv[1];
    cout << "dir_path = " << dir_path << endl;
    
    generator::CMakeListsGenerator gen{dir_path};
    if (!gen.generate()) {
        cout << "Error ocurred!" << endl;
        return -1;
    }

    cout << "CMakeLists.txt files are successfully generated!" << endl;


    return 0;
}
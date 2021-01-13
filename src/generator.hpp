#ifndef __GENERATOR_HEADER
#define __GENERATOR_HEADER

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

namespace generator {

class CMakeListsGenerator {
public:
    CMakeListsGenerator(std::string dir_path);
    bool generate();
private:
    const std::string m_dir_path;
    bool is_invalid_project(void);
    void create_root_cmakelists(const std::string &project_name);
    void create_module_cmakelists(const std::string &module_name);
    void create_source_cmakelists(const std::string &project_name);
    void add_module_to_library(std::ofstream &ofs, std::string module_dir);
};

}


#endif
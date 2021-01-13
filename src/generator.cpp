#include "generator.hpp"
#include "helper.hpp"

#define VERSION "1.0.0"

using namespace std;

namespace generator {

CMakeListsGenerator::CMakeListsGenerator(string dir_path)
    : m_dir_path{dir_path} {}

bool CMakeListsGenerator::is_invalid_project(void) {
    if (helper::get_pathtype(m_dir_path.c_str()) != helper::PATH_DIR) {
        cout << "Please check if the project path is correct." << endl;
        return true;
    }
    if (helper::src_dir_not_exists(m_dir_path)) {
        cout << m_dir_path << "/src directory doesn't exist." << endl;
        return true;
    }
    if (helper::main_cpp_not_exists(m_dir_path)) {
        cout << m_dir_path << "/src/main.cpp doesn't exist." << endl;
        return true;
    }
    return false;
}

bool CMakeListsGenerator::generate(void) {
    if (is_invalid_project()) {
        return false;
    }

    string project_name = helper::get_basename(m_dir_path);

    create_root_cmakelists(project_name);
    create_source_cmakelists(project_name);
    return true;
}

void CMakeListsGenerator::create_root_cmakelists(const string &project_name) {
    ofstream root_out(m_dir_path + "/CMakeLists.txt");
    root_out << "cmake_minimum_required(VERSION 3.0.0)" << endl;
    root_out << "project(" + project_name + " VERSION " + VERSION + ")" << endl;
    root_out << "add_subdirectory(src)" << endl;
    root_out << "include(CTest)" << endl;
    root_out << "enable_testing()" << endl;

    root_out << "set(CPACK_PROJECT_NAME ${PROJECT_NAME})" << endl;
    root_out << "set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})" << endl;
    root_out << "include(CPack)" << endl;
}

void CMakeListsGenerator::create_source_cmakelists(const string &project_name) {
    ofstream src_out(m_dir_path + "/src/CMakeLists.txt");

    string pattern = m_dir_path + "/src/*";
    vector<string> cpp_files;
    vector<string> results = helper::glob_dir(pattern);
    size_t module_cnt = 0;
    for (size_t i = 0; i < results.size(); i++) {
        helper::PathType pathtype = helper::get_pathtype(results[i].c_str());
        if (pathtype == helper::PATH_FILE) {
            string cpp_filename;
            if (!helper::get_cpp_filename(cpp_filename, results[i])) continue;
            cpp_files.push_back(cpp_filename);
        } else if (pathtype == helper::PATH_DIR) {
            module_cnt++;
            add_module_to_library(src_out, results[i]);
            create_module_cmakelists(results[i]);
        }
    }

    src_out << "add_executable(" << project_name; //main.cpp utils.cpp)
    for (size_t i = 0; i < cpp_files.size(); i++) {
        src_out << " " << cpp_files[i];
    }
    src_out << ")" << endl;

    if (module_cnt > 0) {
        src_out << "target_link_libraries(" << project_name << " PUBLIC ${EXTRA_LIBS})" << endl;
        src_out << "target_include_directories(" << project_name << " PUBLIC ${EXTRA_INCLUDES})" << endl;
    }
}

void CMakeListsGenerator::create_module_cmakelists(const string &module_dir) {
    string module_name = helper::get_basename(module_dir);
    string pattern = module_dir + "/*.cpp";
    vector<string> cpp_paths = helper::glob_dir(pattern);
    if (cpp_paths.size() == 0) return;
    ofstream out(m_dir_path + "/src/" + module_name + "/CMakeLists.txt");
    out << "add_library(" << module_name;
    for (size_t i = 0; i < cpp_paths.size(); i++) {
        string cpp_file;
        if (helper::get_cpp_filename(cpp_file, cpp_paths[i])) {
            out << " " + cpp_file;
        }
    }
    out << ")" << endl;
}

void CMakeListsGenerator::add_module_to_library(ofstream &ofs, string module_dir) {
    string module_name = helper::get_basename(module_dir);
    ofs << "add_subdirectory(" << module_name << ")" << endl;
    ofs << "list(APPEND EXTRA_LIBS " << module_name << ")" << endl;
    ofs << "list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/src/" << module_name << ")" << endl;
}

}

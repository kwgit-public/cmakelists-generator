#ifndef __HELPER_HEADER
#define __HELPER_HEADER

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <glob.h>

namespace helper {

typedef enum PathType {
    PATH_FILE,
    PATH_DIR,
    PATH_NA
} PathType;

std::string get_basename(const std::string &path);
bool get_cpp_filename(std::string &dst, std::string path);
PathType get_pathtype(const char * path);
std::vector<std::string> glob_dir(const std::string &pattern);
bool src_dir_not_exists(const std::string &path);
bool main_cpp_not_exists(const std::string &path);

}

#endif
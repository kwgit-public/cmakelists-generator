#include "helper.hpp"

using namespace std;

namespace helper {

string get_basename(const string &path) {
    int len = path.length();
    for (int i = len-1; i >= 0; i--) {
        if (path[i] == '/') {
            return path.substr(i + 1, len - 1 - i);
        }
    }
    return path;
}

bool get_cpp_filename(string &dst, string path) {
    int len = path.length();
    if (len < 5) return false;
    if (path.substr(len-4, 4) != ".cpp") return false;
    dst = get_basename(path);
    return true;
}

PathType get_pathtype(const char *path) {
    struct stat info;
    if(stat(path, &info) != 0) {
        printf( "cannot access %s\n", path );
        return PATH_NA;
    } else if( info.st_mode & S_IFDIR ) {
        // printf( "%s is a directory\n", path );
        return PATH_DIR;
    } else {
        // printf( "%s is no directory\n", path );
        return PATH_FILE;
    }
}

vector<string> glob_dir(const string &pattern) {
    vector<string> result;
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    for(unsigned int i=0; i<glob_result.gl_pathc; ++i){
        // cout << glob_result.gl_pathv[i] << endl;
        result.push_back(glob_result.gl_pathv[i]);
    }
    return result;
}

bool src_dir_not_exists(const string &path) {
    string src_dir = path + "/src";
    if (get_pathtype(src_dir.c_str()) == PATH_DIR) {
        return false;
    } else {
        return true;
    }
}

bool main_cpp_not_exists(const string &path) {
    string main_cpp = path + "/src/main.cpp";
    if (get_pathtype(main_cpp.c_str()) == PATH_FILE) {
        return false;
    } else {
        return true;
    }
}

}
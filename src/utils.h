#ifndef HTTP_SERVER_UTILS_H
#define HTTP_SERVER_UTILS_H

#include <cstdio>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

// Print message and then exit with status 1.
void fatal(const char *msg) {
    perror(msg);
    exit(1);
}

std::vector<std::string> listPath(const std::string& path) {
    auto files = std::vector<std::string>();
    struct dirent *entry;
    DIR *dir = opendir(path.c_str());

    if (dir == nullptr) {
        return files;
    }
    while ((entry = readdir(dir)) != nullptr) {
        files.emplace_back(entry->d_name);
    }
    closedir(dir);
    return files;
}

bool isFolder(const std::string &path) {
    // In fact it can be a third thing.
    struct stat s{};
    if (stat(path.c_str(), &s) == 0) {
        if (s.st_mode & S_IFDIR) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

std::string getExtension(const std::string &path) {
    auto i = path.find_last_of('.');
    if (i != std::string::npos) {
        return path.substr(i + 1);
    }
    return "";
}

#endif //HTTP_SERVER_UTILS_H

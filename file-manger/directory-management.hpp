#ifndef DirectoryManagementClass
#define DirectoryManagementClass
#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <dirent.h>
#include <string>
#include <utility>

class DirectoryManagement {

public:
    explicit DirectoryManagement(std::string);
    int getDirectoryContents(std::string []);
    static int getDirectoryContentsFromPath (const std::string&, std::string []);

private:
    std::string workingDirectory;
};

#endif

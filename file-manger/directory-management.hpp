#include <dirent.h>
#include <string>
#include <utility>
#ifndef DirectoryManagement
#pragma GCC diagnostic ignored "-Wc++11-extensions"

class DirectoryManagement {

public:
    explicit DirectoryManagement(std::string);
    int getDirectoryContents(std::string []);
    static int getDirectoryContentsFromPath (const std::string&, std::string []);

private:
    std::string workingDirectory;
};

#endif

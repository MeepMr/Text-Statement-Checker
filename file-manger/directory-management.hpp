#include <dirent.h>
#include <string>
#include <utility>
#ifndef DirectoryManagement

class DirectoryManagement {

public:
    explicit DirectoryManagement(std::string);
    int getDirectoryContents(std::string []);
    static int getDirectoryContentsFromPath (const std::string&, std::string []);

private:
    std::string workingDirectory;
};

#endif

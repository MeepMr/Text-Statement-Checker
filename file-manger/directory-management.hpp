#include <dirent.h>
#include <string>
#include <utility>

class DirectoryManagement {

public:
    explicit DirectoryManagement(std::string);
    std::string getWorkingDirectory();
    int getDirectoryContents(std::string []);
    static int getDirectoryContentsFromPath (const std::string&, std::string []);

private:
    std::string workingDirectory;
};
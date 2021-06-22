#include "file-management.hpp"

void FileManagement::printContentOfFile(const std::string& pathToFile) {

    std::ifstream fileInputStream(pathToFile);

    if(fileInputStream.is_open())
        std::cout << fileInputStream.rdbuf();
}

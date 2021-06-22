#include <iostream>
#include "file-manger/file-management.hpp"
#include "file-manger/directory-management.hpp"


#define MAXSIZE 300

int main() {

    std::string pathToTestDirectory = "./test-candidates";

    std::string dirContents [MAXSIZE];

    int contentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToTestDirectory, dirContents);


    for(int i = 0; i < contentsCount; i++) {

        std::cout << dirContents[i] << std::endl;

        std::string subDirContents [MAXSIZE];

        std::string pathToSubDirectory = pathToTestDirectory + "/" + dirContents[i];
        int subDirContentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToSubDirectory, subDirContents);

        for(int j = 0; j < subDirContentsCount; j++) {

            std::cout << "   " << subDirContents[j] << std::endl;

            std::string pathToFile = pathToSubDirectory + "/" + subDirContents[j];

            FileManagement::printContentOfFile(pathToFile);
        }
    }

    return 0;
}

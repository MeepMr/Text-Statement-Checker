#include <iostream>
#include "file-manger/file-management.hpp"
#include "file-manger/directory-management.hpp"


#define MAXSIZE 300
#define MAXSUBDIRSIZE 5

int main(int argc, char ** argv) {

    std::string pathToTestDirectory = argv[1];

    auto* dirContents = new std::string [MAXSIZE];

    int contentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToTestDirectory, dirContents);


    for(int i = 0; i < contentsCount; i++) {

        std::cout << dirContents[i] << std::endl;

        auto* subDirContents = new std::string [MAXSUBDIRSIZE];

        std::string pathToSubDirectory = pathToTestDirectory + "/" + dirContents[i];
        int subDirContentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToSubDirectory, subDirContents);

        for(int j = 0; j < subDirContentsCount; j++) {

            std::cout << "   " << subDirContents[j] << std::endl;

            std::string pathToFile = pathToSubDirectory + "/" + subDirContents[j];

            FileManagement::printContentOfFile(pathToFile);
        }

        delete[] subDirContents;
    }

    delete[] dirContents;

    return 0;
}

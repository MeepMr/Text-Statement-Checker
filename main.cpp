#include <iostream>
#include "file-manger/file-management.hpp"
#include "file-manger/directory-management.hpp"
#include "constraint-manager/constraint-manager.hpp"

#define MAXSIZE 300
#define MAXSUBDIRSIZE 5

int main(int argc, char ** argv) {

    if(argc != 2)
        exit(100);

    std::string pathToTestDirectory = argv[1];

    auto* dirContents = new std::string [MAXSIZE];

    auto* constraintManager = new ConstraintManager(argv[1]);
    std::string testConstraints [] = {"monitor"};
    constraintManager->addConstraint("FirstConstraint", testConstraints, 1);

    int contentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToTestDirectory, dirContents);


    for(int i = 0; i < contentsCount; i++) {

        std::cout << dirContents[i] << std::endl;

        auto* subDirContents = new std::string [MAXSUBDIRSIZE];

        std::string pathToSubDirectory = pathToTestDirectory + "/" + dirContents[i];
        int subDirContentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToSubDirectory, subDirContents);

        for(int j = 0; j < subDirContentsCount; j++) {

            std::cout << "   " << subDirContents[j] << std::endl;

            std::string pathToFile = pathToSubDirectory + "/" + subDirContents[j];
            auto* linesOfFile = new std::string[500];

            const int lines = FileManagement::getLinesOfFile(pathToFile, linesOfFile);
            for(int line = 0; line < lines; line++)
                constraintManager->findKeyWordsInString(linesOfFile[line], line);

            delete [] linesOfFile;
        }

        delete[] subDirContents;
    }

    delete[] dirContents;

    constraintManager->printKeyWordMap();
    constraintManager->checkAllConstraints();

    ConstraintManager::constraint *constraints = constraintManager->getRegisteredConstraints();

    for(int i = 0; i < constraintManager->getAmountOfRegisteredConstraints(); i++)
        std::cout << constraints[i].identifier << " Is " << constraints[i].fulfilled << std::endl;

    delete[] constraints;

    return 0;
}

#include <iostream>
#include "file-manger/file-management.hpp"
#include "file-manger/directory-management.hpp"
#include "constraint-manager/constraint-manager.hpp"
#include "constraint-manager/constraint-injector.hpp"
#pragma GCC diagnostic ignored "-Wc++11-extensions"

#define MAXSIZE 300
#define MAXSUBDIRSIZE 5

void testSubdirectory (const std::string& parentDirectory, const std::string& currentDirectory);
void testSingleFile (const std::string& parentDirectory, const std::string& currentFile);

void injectConstraintsForTestFile (ConstraintManager* constraintManager, const std::string& filename);
void registerKeyWords (ConstraintManager* constraintManager, std::string linesOfFile [], int linesCount);
void executeTest(ConstraintManager* constraintManager);

void printTestResults (ConstraintManager* constraintManager);

int main(int argc, char ** argv) {

    if(argc != 2)
        exit(100);

    auto* directoryContents = new std::string [MAXSIZE];
    int contentsCount;
    std::string pathToTestDirectory = argv[1];

    contentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToTestDirectory, directoryContents);

    for(int i = 0; i < contentsCount; i++)
        testSubdirectory(pathToTestDirectory, directoryContents[i]);

    delete[] directoryContents;
    return 0;
}

void testSubdirectory (const std::string& parentDirectory, const std::string& currentDirectory) {

    auto* subDirectoryContents = new std::string [MAXSUBDIRSIZE];
    int subDirContentsCount, i;

    std::cout << currentDirectory << std::endl;

    std::string pathToSubDirectory = parentDirectory + "/" + currentDirectory;
    subDirContentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToSubDirectory, subDirectoryContents);

    for(i = 0; i < subDirContentsCount; i++) {

        testSingleFile(pathToSubDirectory, subDirectoryContents[i]);
    }

    delete[] subDirectoryContents;
}

void testSingleFile (const std::string& parentDirectory, const std::string& currentFile) {

    auto* constraintManager = new ConstraintManager(currentFile);
    auto* linesOfFile = new std::string[500];
    int lines;

    std::cout << "   " << currentFile << std::endl;

    std::string pathToFile = parentDirectory + "/" + currentFile;
    injectConstraintsForTestFile(constraintManager, currentFile);

    lines = FileManagement::getLinesOfFile(pathToFile, linesOfFile);

    registerKeyWords(constraintManager, linesOfFile, lines);
    executeTest(constraintManager);

    delete [] linesOfFile;
}

void injectConstraintsForTestFile (ConstraintManager* constraintManager, const std::string& filename) {

    if(filename == "Option1")
        ConstraintInjector::injectTestConstraints(constraintManager);
    else if (filename == "Option3")
        ConstraintInjector::injectTestConstraints(constraintManager);
    else
        ConstraintInjector::injectTestConstraints(constraintManager);
}

void registerKeyWords (ConstraintManager* constraintManager, std::string linesOfFile [], int linesCount) {

    for(int currentLine = 0; currentLine < linesCount; currentLine++)
        constraintManager->findKeyWordsInString(linesOfFile[currentLine], currentLine);
}

void executeTest(ConstraintManager* constraintManager) {

    constraintManager->checkAllConstraints();
    printTestResults(constraintManager);
}

void printTestResults (ConstraintManager* constraintManager) {

    ConstraintManager::constraint *constraints = constraintManager->getRegisteredConstraints();

    for(int i = 0; i < constraintManager->getAmountOfRegisteredConstraints(); i++)
        std::cout << constraints[i].identifier << " Is " << constraints[i].fulfilled << std::endl;

    delete[] constraints;
}

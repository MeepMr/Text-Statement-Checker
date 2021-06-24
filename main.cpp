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
void writeStatementHead();

FileManagement* resultStatement;

int main(int argc, char ** argv) {

    if(argc != 2)
        exit(100);

    std::string pathToTestDirectory = argv[1];
    auto* directoryContents = new std::string [MAXSIZE];
    resultStatement = new FileManagement(pathToTestDirectory+"/result-statement.md", false);
    int contentsCount;

    contentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToTestDirectory, directoryContents);
    //resultStatement->writeLineToFile("# Summary of Text-Tests");
    writeStatementHead();

    for(int i = 0; i < contentsCount; i++)
        testSubdirectory(pathToTestDirectory, directoryContents[i]);

    delete resultStatement;
    delete[] directoryContents;
    return 0;
}

void testSubdirectory (const std::string& parentDirectory, const std::string& currentDirectory) {

    auto* subDirectoryContents = new std::string [MAXSUBDIRSIZE];
    int subDirContentsCount, i;

    std::string pathToSubDirectory = parentDirectory + "/" + currentDirectory;
    subDirContentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToSubDirectory, subDirectoryContents);

    resultStatement->writeLineToFile("## " + currentDirectory);

    for(i = 0; i < subDirContentsCount; i++) {

        testSingleFile(pathToSubDirectory, subDirectoryContents[i]);
    }

    resultStatement->writeLineToFile("+++");

    delete[] subDirectoryContents;
}

void testSingleFile (const std::string& parentDirectory, const std::string& currentFile) {

    auto* constraintManager = new ConstraintManager(currentFile);
    auto* linesOfFile = new std::string[500];
    int lines;

    resultStatement->writeLineToFile("- " + currentFile);


    std::string pathToFile = parentDirectory + "/" + currentFile;
    auto* testFile = new FileManagement(pathToFile);

    injectConstraintsForTestFile(constraintManager, currentFile);

    lines = testFile->getLinesOfFile(linesOfFile);

    registerKeyWords(constraintManager, linesOfFile, lines);
    executeTest(constraintManager);

    delete [] linesOfFile;
}

void injectConstraintsForTestFile (ConstraintManager* constraintManager, const std::string& filename) {

    if(filename == "writer.c" || filename == "Writer.c")
        ConstraintInjector::injectWriterConstraints(constraintManager);
    else if (filename == "spooler.c" || filename == "Spooler.c")
        ConstraintInjector::injectSpoolerConstraints(constraintManager);
    else if (filename == "monitor.c" || filename == "Monitor.c")
        ConstraintInjector::injectMonitorConstraints(constraintManager);
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

    char statusString [30];
    int fulfilledConstraints = constraintManager->fulfilledConstraints;
    int constraintAmount = constraintManager->constraintCounter;
    sprintf(statusString, "\t- ==Passed %d of %d Tests==" ,  fulfilledConstraints, constraintAmount);

    resultStatement->writeLineToFile(statusString);

    for(int i = 0; i < constraintAmount; i++) {

        std::string resultString;
        if (constraints[i].fulfilled)
            resultString = "\t- [x] " + constraints[i].identifier;
        else
            resultString = "\t- [ ] ==" + constraints[i].identifier + "==";

        resultStatement->writeLineToFile(resultString);
    }

    delete[] constraints;
}

void writeStatementHead () {

    resultStatement->writeLineToFile("# Summary of Text-Tests\n"
                                     "### Automated inspection of Source files.\n"
                                     "\n---\n"
                                     "The following File contains the results of an automated Test-Script.  \n"
                                     "The Script looks for Predefined Keywords and checks the order in which they appear\n"
                                     "+++");
}

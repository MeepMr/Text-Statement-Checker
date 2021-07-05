#include "main.hpp"


void testSubdirectory (const std::string& parentDirectory, const std::string& currentDirectory);
void testSingleFile (const std::string& parentDirectory, const std::string& currentFile);

void injectConstraintsForTestFile (ConstraintManager* constraintManager, const std::string& filename);
void registerKeyWords (ConstraintManager* constraintManager, std::string linesOfFile [], int linesCount);
void executeTest(ConstraintManager* constraintManager);

void printTestResults (ConstraintManager* constraintManager);
void printResultStatement (const std::string& pathToTestDirectory);
void adjustTestStatistics (const std::string& fileName, int constraintAmount, int fulfilledConstraints);
void writeStatementHead();

FileManagement* resultStatement;
int testsRun [4];
int testCompleted [4];

int main(int argc, char ** argv) {

    if(argc != 2)
        exit(100);

    std::string pathToTestDirectory = argv[1];
    auto* directoryContents = new std::string [MAXSIZE];
    resultStatement = new FileManagement(pathToTestDirectory+"/result-statement.md.tmp", false);
    int contentsCount;

    contentsCount = DirectoryManagement::getDirectoryContentsFromPath(pathToTestDirectory, directoryContents);

    for(int i = 0; i < contentsCount; i++)
        testSubdirectory(pathToTestDirectory, directoryContents[i]);

    delete resultStatement;
    delete[] directoryContents;

    printResultStatement(pathToTestDirectory);

    delete resultStatement;

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
    delete testFile;
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

    int fulfilledConstraints = constraintManager->fulfilledConstraints;
    int constraintAmount = constraintManager->constraintCounter;

    char statusString [30];
    sprintf(statusString, "\t- **Passed %d of %d Tests**" ,  fulfilledConstraints, constraintAmount);
    resultStatement->writeLineToFile(statusString);

    adjustTestStatistics(constraintManager->fileName, constraintAmount, fulfilledConstraints);

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

void adjustTestStatisticAtIdentifier (int identifier, int constraintAmount, int fulfilledConstraints) {

    testsRun[identifier] += constraintAmount;
    testCompleted[identifier] += fulfilledConstraints;
}

void adjustTestStatistics (const std::string& fileName, int constraintAmount, int fulfilledConstraints) {

    int identifier = 0;
    adjustTestStatisticAtIdentifier(identifier, constraintAmount, fulfilledConstraints);

    if(fileName == "writer.c" || fileName == "Writer.c")
        identifier = 1;
    else if (fileName == "spooler.c" || fileName == "Spooler.c")
        identifier = 2;
    else if (fileName == "monitor.c" || fileName == "Monitor.c")
        identifier = 3;

    adjustTestStatisticAtIdentifier(identifier, constraintAmount, fulfilledConstraints);
}

void writeStatementHead () {

    char headString [1000];
    sprintf(headString, "**Test Results**\n"
                        "\n"
                        "*Automatic Generated File*\n"
                        "\n"
                        "---\n"
                        "\n"
                        "**Automated inspection of Source files.**  \n"
                        " \n"
                        "The following File contains the results of an automated Test-Script.  \n"
                        "The Script looks for Predefined Keywords and checks the order in which they appear\n"
                        "\n"
                        "---\n"
                        "\n"
                        "**Summary of The Tests**\n"
                        "\n"
                        "| Tested File | Tests Run | Tests Cleared | Clearing Rate |\n"
                        "|:----------|:--------:|:-----------:|:-----------:|\n"
                        "| All Files | %d | %d | %f %% |\n"
                        "\n"
                        "| writer.c | %d | %d | %f %% |\n"
                        "\n"
                        "| spooler.c | %d | %d | %f %% |\n"
                        "\n"
                        "| monitor.c | %d | %d | %f %% |\n"
                        "\n"
                        "+++\n"
                        "**Checked Folders**\n"
                        "\n"
                        "{{TOC}}\n"
                        "\n"
                        "+++" , testsRun[0], testCompleted[0], (testCompleted[0] * 1.0)/testsRun[0]*100,
                                testsRun[1], testCompleted[1], (testCompleted[1] * 1.0)/testsRun[1]*100,
                                testsRun[2], testCompleted[2], (testCompleted[2] * 1.0)/testsRun[2]*100,
                                testsRun[3], testCompleted[3], (testCompleted[3] * 1.0)/testsRun[3]*100);


    resultStatement->writeLineToFile(headString);
}

void printResultStatement(const std::string& pathToTestDirectory) {

    resultStatement = new FileManagement(pathToTestDirectory+"/result-statement.md", false);

    auto* temporaryStatement = new FileManagement(pathToTestDirectory+"/result-statement.md.tmp");

    writeStatementHead();

    std::string currentLine = temporaryStatement->getNextLineOfFile();

    while (!currentLine.empty()) {

        resultStatement->writeLineToFile(currentLine);
        currentLine = temporaryStatement->getNextLineOfFile();
    }

    delete temporaryStatement;
}

#include "file-management.hpp"

FileManagement::FileManagement(std::string pathToFile, bool readOnly): pathToFile(std::move(pathToFile)), readOnly(readOnly) {

    if(readOnly) {
        auto *fileInputStream = new std::ifstream(pathToFile);
        fileInput = fileInputStream;
        fileOutput = nullptr;
    } else {

        auto* fileOutputStream = new std::ofstream (pathToFile);
        fileOutput = fileOutputStream;
        fileInput = nullptr;
    }
}

FileManagement::FileManagement(std::string pathToFile): pathToFile(std::move(pathToFile)), readOnly(true) {

    auto* fileInputStream = new std::ifstream (pathToFile);
    fileInput = fileInputStream;
    fileOutput = nullptr;
}

FileManagement::~FileManagement() {

    if(readOnly)
        (*fileInput).close();
    else
        (*fileOutput).close();
}

void FileManagement::printContentOfFile() {

    if (readOnly) {
        auto *linesOfFile = new std::string[500];
        FileManagement::printContentOfFile(FileManagement::getLinesOfFile(linesOfFile), linesOfFile);

        delete[] linesOfFile;
    }
}

void FileManagement::printContentOfFile(int linesCount, const std::string linesOfFile []) {

    for(int counter = 0; counter < linesCount; counter++ ) {

        std::cout << counter << ": " << linesOfFile[counter] << std::endl;
    }
}

/**
 * Returns the lines read and the Lines in the passed String Array
 * @param linesOfFile
 * @returns Integer
 */
int FileManagement::getLinesOfFile(std::string linesOfFile []) {

    if (readOnly && (*fileInput).is_open()) {
        int counter = 0;

        while (std::getline((*fileInput), linesOfFile[counter]))
            counter++;

        return counter;
    } else {

        return -1;
    }
}

void FileManagement::writeLineToFile(const std::string& lineToWrite) {

    if(!readOnly) {

        (*fileOutput) << lineToWrite << std::endl;
    }
}

std::string FileManagement::getNextLineOfFile() {

    std::string nextLine;

    if(readOnly && (*fileInput).is_open())
        std::getline((*fileInput), nextLine);
    else
        nextLine = "";

    return nextLine;
}

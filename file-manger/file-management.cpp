#include "file-management.hpp"

void FileManagement::printContentOfFile(const std::string& pathToFile) {

    auto* linesOfFile = new std::string [500];
    FileManagement::printContentOfFile(FileManagement::getLinesOfFile(pathToFile, linesOfFile), linesOfFile);

    delete[] linesOfFile;
}

/**
 * Returns the lines read and the Lines in the passed String Array
 * @param pathToFile
 * @param linesOfFile
 * @returns Integer
 */
int FileManagement::getLinesOfFile(const std::string& pathToFile, std::string linesOfFile []) {

    std::ifstream fileInputStream(pathToFile);
    int counter = 0;
    if(fileInputStream.is_open()) {

        while (std::getline(fileInputStream, linesOfFile[counter])) {
            counter++;
        }

        fileInputStream.close();

        return counter;
    } else {

        return -1;
    }
}

void FileManagement::printContentOfFile(int linesCount, const std::string linesOfFile []) {

    for(int counter = 0; counter < linesCount; counter++ ) {

        std::cout << counter << ": " << linesOfFile[counter] << std::endl;
    }
}

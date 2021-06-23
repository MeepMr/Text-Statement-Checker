#include "directory-management.hpp"

DirectoryManagement::DirectoryManagement(std::string pathToDirectory): workingDirectory(std::move(pathToDirectory)) { }

int DirectoryManagement::getDirectoryContents(std::string directoryContentsList []) {

    DIR* directory = opendir(workingDirectory.c_str());
    struct dirent *currentDirectory;
    int directoryCounter = 0;
    if(!directory) {

        printf("Directory not found!");
        directoryContentsList = nullptr;
    } else {

        while ((currentDirectory = readdir(directory)) != nullptr) {

            std::string fileName = currentDirectory->d_name;

            if(fileName == ".DS_Store" || fileName == "." || fileName == "..")
                continue;

            directoryContentsList[directoryCounter] = fileName;
            directoryCounter++;
        }
    }

    return directoryCounter;
}

int DirectoryManagement::getDirectoryContentsFromPath (const std::string& pathToDirectory, std::string contentsReturnString []) {

    auto* directoryFileManager = new DirectoryManagement(pathToDirectory);
    return directoryFileManager->getDirectoryContents(contentsReturnString);
}
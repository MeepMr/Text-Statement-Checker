#include "directory-management.hpp"

DirectoryManagement::DirectoryManagement(std::string pathToDirectory): workingDirectory(std::move(pathToDirectory)) { }

/**
 * Writes all Contents of the workingDirectory from its associated DirectoryManager
 * into the passed String Array.
 * @param directoryContentsList
 * @return The amount of Lines written into the passed String Array
 */
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

/**
 * Enables all the functionality without the need to separately create an instance
 * of the DirectoryManagement class
 * @param pathToDirectory
 * @param contentsReturnString
 * @return
 */
int DirectoryManagement::getDirectoryContentsFromPath (const std::string& pathToDirectory, std::string contentsReturnString []) {

    auto* directoryFileManager = new DirectoryManagement(pathToDirectory);
    return directoryFileManager->getDirectoryContents(contentsReturnString);
}
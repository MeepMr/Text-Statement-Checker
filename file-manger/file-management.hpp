#ifndef FileManagementClass
#define FileManagementClass
#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <string>
#include <fstream>
#include <iostream>
#include <utility>

class FileManagement {
public:
    FileManagement(std::string  pathToFile, bool readOnly);
    explicit FileManagement(std::string pathToFile);
    ~FileManagement();
    void printContentOfFile();
    int getLinesOfFile(std::string []);
    std::string getNextLineOfFile();
    void writeLineToFile(const std::string& lineToWrite);

private:
    std::string pathToFile;
    bool readOnly;
    std::ifstream* fileInput;
    std::ofstream* fileOutput;

    static void printContentOfFile(int, const std::string []);

};

#endif

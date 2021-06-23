#ifndef FileManagementClass
#define FileManagementClass
#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include <string>
#include <fstream>
#include <iostream>

class FileManagement {
public:
    static void printContentOfFile(const std::string&);
    static void printContentOfFile(int, const std::string []);

    static int getLinesOfFile(const std::string&, std::string []);
private:

};

#endif

#include <string>
#include <fstream>
#include <iostream>
#ifndef FileManagement
#pragma GCC diagnostic ignored "-Wc++11-extensions"

class FileManagement {
public:
    static void printContentOfFile(const std::string&);
    static void printContentOfFile(int, const std::string []);

    static int getLinesOfFile(const std::string&, std::string []);
private:

};

#endif

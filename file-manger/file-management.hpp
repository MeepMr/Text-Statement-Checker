#include <string>
#include <fstream>
#include <iostream>
#ifndef FileManagement
class FileManagement {
public:
    static void printContentOfFile(const std::string&);
    static void printContentOfFile(int, const std::string []);

    static int getLinesOfFile(const std::string&, std::string []);
private:

};

#endif

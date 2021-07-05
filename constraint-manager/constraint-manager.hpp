#ifndef ConstraintManagerClass
#define ConstraintManagerClass
#include "../constants.hpp"
#include <string>
#include <utility>
#include <iostream>

class ConstraintManager {

    typedef struct {

        std::string keyWord;
        int timesFound;
        int lineCount [100];
    } keyWordCountMap;

public:
    typedef struct {

        std::string* constraintArray;
        std::string identifier;
        int amountOfConstraintParts;
        int constraintsFulfilled;
        bool fulfilled;
        bool fulfilledMap [20];
    } constraint;

    int fulfilledConstraints;
    int constraintCounter;
    std::string fileName;

    explicit ConstraintManager(std::string registeredFile);
    ~ConstraintManager();
    void addConstraint(const std::string& name, std::string constraintArray [], int amountOfConstraints);
    void printKeyWordMap();
    void findKeyWordsInString(const std::string& lineOfFile, int currentLine);
    constraint * getRegisteredConstraints();
    void checkAllConstraints();

private:
    constraint * registeredConstraints ;
    keyWordCountMap* keyWordMap;
    int keyWordCounter;

    void addToKeyWordMap(const std::string& newKeyWord);
    bool keyWordMapContains(const std::string& newKeyWord);
    bool checkConstraint(ConstraintManager::constraint& currentConstraint);
    static int getMinimumLine(int *lines,int amountLines, int &currentLine);
    bool isKeyWordFoundAfterLine(const std::string &keyWord, int &currentLine);
};

#endif

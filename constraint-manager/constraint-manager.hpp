#include <string>
#include <utility>
#include <iostream>
#ifndef ConstraintManager

class ConstraintManager {

    typedef struct {

        std::string keyWord;
        int timesFound;
        int lineCount [];
    } keyWordCountMap;

public:
    typedef struct {

        std::string* constraintArray;
        std::string identifier;
        int amountOfConstraintParts;
        bool fulfilled;
    } constraint;

    explicit ConstraintManager(std::string registeredFile);
    ~ConstraintManager();
    void addConstraint(const std::string& name, std::string constraintArray [], int amountOfConstraints);
    void printKeyWordMap();
    void findKeyWordsInString(const std::string& lineOfFile, int currentLine);
    constraint * getRegisteredConstraints();
    void checkAllConstraints();
    int getAmountOfRegisteredConstraints() const;

private:
    std::string fileName;
    constraint * registeredConstraints ;
    keyWordCountMap* keyWordMap;
    int constraintCounter;
    int keyWordCounter;

    void addToKeyWordMap(const std::string& newKeyWord);
    bool keyWordMapContains(const std::string& newKeyWord);
    bool checkConstraint(const ConstraintManager::constraint& currentConstraint);
    static int getMinimumLine(int *lines,int amountLines, const int *currentLine);
    bool isKeyWordFoundAfterLine(const std::string &keyWord, int *currentLine);
};

#endif

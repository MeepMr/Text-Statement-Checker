#include "constraint-manager.hpp"

ConstraintManager::ConstraintManager(std::string registeredFile) {

    this->keyWordMap = new keyWordCountMap [300];
    this->registeredConstraints = new constraint [100];
    this->fileName = std::move(registeredFile);
    this->constraintCounter = 0;
    this->keyWordCounter = 0;
}

void ConstraintManager::addConstraint(const std::string& name, std::string constraintArray [], int amountOfConstraints) {

    registeredConstraints[constraintCounter].constraintArray = constraintArray;
    registeredConstraints[constraintCounter].identifier = name;
    registeredConstraints[constraintCounter].amountOfConstraintParts = amountOfConstraints;
    constraintCounter++;

    for(int i = 0; i < amountOfConstraints; i++)
        addToKeyWordMap(constraintArray[i]);

}

ConstraintManager::~ConstraintManager() {

    delete[] keyWordMap;
    delete[] registeredConstraints;
}

void ConstraintManager::addToKeyWordMap(const std::string& newKeyWord) {

    if(!keyWordMapContains(newKeyWord)) {

        keyWordMap[keyWordCounter++].keyWord = newKeyWord;
    }
}

bool ConstraintManager::keyWordMapContains(const std::string& newKeyWord) {

    for(int counter = 0; counter < keyWordCounter; counter++) {

        if(keyWordMap[counter].keyWord == newKeyWord)
            return true;
    }

    return false;
}

void ConstraintManager::printKeyWordMap() {

    for(int counter = 0; counter < keyWordCounter; counter++) {

        std::cout << "Found " << keyWordMap[counter].keyWord << " " << keyWordMap[counter].timesFound << " times" << std::endl;

        std::cout << "Found at: ";
        for(int i = 0; i < keyWordMap[counter].timesFound; i++)
            std::cout << keyWordMap[counter].lineCount[i] << " ";

        std::cout << std::endl << std::endl;
    }
}

void ConstraintManager::findKeyWordsInString(const std::string& lineOfFile, int currentLine) {

    for(int counter = 0; counter < keyWordCounter; counter++) {

        if(lineOfFile.find(keyWordMap[counter].keyWord) != std::string::npos) {

            const int currentlyFoundTimes = keyWordMap[counter].timesFound;
            keyWordMap[counter].lineCount[currentlyFoundTimes] = currentLine;
            keyWordMap[counter].timesFound++;
        }

    }
}

ConstraintManager::constraint *ConstraintManager::getRegisteredConstraints() {
    return registeredConstraints;
}

void ConstraintManager::checkAllConstraints() {

    for(int currentConstraintCounter = 0; currentConstraintCounter < constraintCounter; currentConstraintCounter++) {

        const bool success = checkConstraint(registeredConstraints[currentConstraintCounter]);

        if(success)
            registeredConstraints[currentConstraintCounter].fulfilled = true;
        else
            registeredConstraints[currentConstraintCounter].fulfilled = false;
    }
}

bool ConstraintManager::checkConstraint(const ConstraintManager::constraint& currentConstraint) {

    int currentLine = 0;
    bool found = false;

    for (int csCounter = 0; csCounter < currentConstraint.amountOfConstraintParts; csCounter++) {

        std::cout << "Before Line: " << currentConstraint.constraintArray[csCounter] << " " << currentLine << std::endl;

        found = isKeyWordFoundAfterLine(currentConstraint.constraintArray[csCounter], &currentLine);

        std::cout << "After Line: " << currentConstraint.constraintArray[csCounter] << " " << currentLine << std::endl;

        if(!found)
            return false;
    }

    if(found)
        return true;
    else
        return false;
}

int ConstraintManager::getMinimumLine(int lines[], int amountLines, const int* currentLine) {

    for (int i = 0; i < amountLines; i++) {

        if(lines[i] >= *currentLine)
            return lines[i];
    }

    return -1;
}

bool ConstraintManager::isKeyWordFoundAfterLine (const std::string& keyWord, int* currentLine) {

    for (int kwCounter = 0; kwCounter < keyWordCounter; kwCounter++) {

        keyWordCountMap * currentKwMap = &keyWordMap[kwCounter];
        if ((*currentKwMap).keyWord == keyWord) {

            (*currentLine) = getMinimumLine((*currentKwMap).lineCount, (*currentKwMap).timesFound, currentLine);

            if(*currentLine < 0)
                return false;
            else
                return true;
        }
    }

    return false;
}

int ConstraintManager::getAmountOfRegisteredConstraints() const {
    return constraintCounter;
}

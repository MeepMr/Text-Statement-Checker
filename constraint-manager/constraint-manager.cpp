#include "constraint-manager.hpp"

ConstraintManager::ConstraintManager(std::string registeredFile) {

    this->keyWordMap = new keyWordCountMap [300];
    this->registeredConstraints = new constraint [100];
    this->fileName = std::move(registeredFile);
    this->constraintCounter = 0;
    this->fulfilledConstraints = 0;
    this->keyWordCounter = 0;
}

ConstraintManager::~ConstraintManager() {

    delete[] keyWordMap;
    delete[] registeredConstraints;
}

/**
 *
 * @param name Meaningful Name for the Constraint-Set
 * @param constraintArray Array Providing the KeyWords in the Order, they have to appear in
 * @param amountOfConstraints
 */
void ConstraintManager::addConstraint(const std::string& name, std::string constraintArray [], int amountOfConstraints) {

    registeredConstraints[constraintCounter].constraintArray = constraintArray;
    registeredConstraints[constraintCounter].identifier = name;
    registeredConstraints[constraintCounter].amountOfConstraintParts = amountOfConstraints;
    constraintCounter++;

    for(int i = 0; i < amountOfConstraints; i++) {
        addToKeyWordMap(constraintArray[i]);
    }
}

/**
 * Prints the Keyword Map with all found Keywords and their associated lines
 * into std-out
 */
void ConstraintManager::printKeyWordMap() {

    for(int counter = 0; counter < keyWordCounter; counter++) {

        for(int i = 0; i < keyWordMap[counter].timesFound; i++)
            std::cout << keyWordMap[counter].lineCount[i] << " ";

        std::cout << std::endl << std::endl;
    }
}

/**
 * Searches the given String for all registered Keywords.
 * When a Match is found, the given Line will be saved in the Keyword Struct
 * @param lineOfFile
 * @param currentLine Number of the Line in the file
 */
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

        registeredConstraints[currentConstraintCounter].fulfilled = success;
        if(success)
            fulfilledConstraints++;
    }
}

void ConstraintManager::addToKeyWordMap(const std::string& newKeyWord) {

    if(!keyWordMapContains(newKeyWord))
        keyWordMap[keyWordCounter++].keyWord = newKeyWord;
}

bool ConstraintManager::keyWordMapContains(const std::string& newKeyWord) {

    for(int counter = 0; counter < keyWordCounter; counter++) {

        if(keyWordMap[counter].keyWord == newKeyWord)
            return true;
    }

    return false;
}

/**
 * Checks for each Constraint part, if the corresponding Keyword was found and if the
 * order of the Keywords matches the order defined at the declaration of the Keyword
 * @param currentConstraint
 * @return A Boolean, weather the Constraint succeeded or not
 */
bool ConstraintManager::checkConstraint(ConstraintManager::constraint& currentConstraint) {

    int currentLine = 0;
    bool fulfilled = false;

    for (int csCounter = 0; csCounter < currentConstraint.amountOfConstraintParts; csCounter++) {

        fulfilled = isKeyWordFoundAfterLine(currentConstraint.constraintArray[csCounter], currentLine);

        currentConstraint.fulfilledMap[csCounter] = fulfilled;

        if(fulfilled)
            currentConstraint.constraintsFulfilled++;
    }

    return fulfilled;
}

/**
 * Returns the smallest Number from an Integer Array, which is larger
 * than or equal to the given currentLine
 * @param lines
 * @param amountLines
 * @param currentLine
 * @return
 */
int ConstraintManager::getMinimumLine(int lines[], int amountLines, int& currentLine) {

    for (int i = 0; i < amountLines; i++) {

        if(lines[i] >= currentLine)
            return lines[i];
    }

    return -1;
}

/**
 * Checks if a given Keyword is found in the Keyword Objects.
 * The Keyword has to be found after the currentLine
 * @param keyWord
 * @param currentLine
 * @return
 */
bool ConstraintManager::isKeyWordFoundAfterLine (const std::string& keyWord, int& currentLine) {

    for (int kwCounter = 0; kwCounter < keyWordCounter; kwCounter++) {

        keyWordCountMap  currentKwMap = keyWordMap[kwCounter];
        if (currentKwMap.keyWord == keyWord) {

            currentLine = getMinimumLine(currentKwMap.lineCount, currentKwMap.timesFound, currentLine);

            if(currentLine < 0)
                return false;
            else
                return true;
        }
    }

    return false;
}

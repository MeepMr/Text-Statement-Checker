#include "constraint-injector.hpp"

/**
 * Injects the Test-Constraints into the given constraintManager
 * @param constraintManager
 */
void ConstraintInjector::injectTestConstraints(ConstraintManager *constraintManager) {

    auto* constraintStringArray = new std::string [1];
    constraintStringArray[0] = ";";
    constraintManager->addConstraint("File does not match Pattern", constraintStringArray, 1);
}

void ConstraintInjector::injectWriterConstraints(ConstraintManager *constraintManager) {

    auto* constraintStringArray = new std::string [1];
    constraintStringArray[0] = "for";
    constraintManager->addConstraint("Writer contains for loop", constraintStringArray, 1);


    constraintStringArray = new std::string [4];
    constraintStringArray[0] = "open";
    constraintStringArray[1] = "O_WRONLY";
    constraintStringArray[2] = "write";
    constraintStringArray[3] = "close";
    constraintManager->addConstraint("Writer contains fifo", constraintStringArray, 4);

    constraintStringArray = new std::string [2];
    constraintStringArray[0] = "strcmp";
    constraintStringArray[1] = "txt";
    constraintManager->addConstraint("Writer checks for .txt ending", constraintStringArray, 2);

    constraintStringArray = new std::string [1];
    constraintStringArray[0] = "signal";
    constraintManager->addConstraint("Writer checks for Signals", constraintStringArray, 1);

    constraintStringArray = new std::string [4];
    constraintStringArray[0] = "main";
    constraintStringArray[1] = "argc";
    constraintStringArray[2] = "argv";
    constraintStringArray[3] = "{";
    constraintManager->addConstraint("Writer checks Command-Line Arguments", constraintStringArray, 4);
}

void ConstraintInjector::injectSpoolerConstraints(ConstraintManager *constraintManager) {

    auto* constraintStringArray = new std::string [4];
    constraintStringArray[0] = "typedef";
    constraintStringArray[1] = "struct";
    constraintStringArray[2] = "{";
    constraintStringArray[3] = "}";
    constraintManager->addConstraint("Spooler Uses Struct", constraintStringArray, 4);

    constraintStringArray = new std::string [4];
    constraintStringArray[0] = "sem_open";
    constraintStringArray[1] = "sem_trywait";
    constraintStringArray[2] = "sem_post";
    constraintStringArray[3] = "sem_unlink";
    constraintManager->addConstraint("Spooler Uses Semaphore", constraintStringArray, 3);

    constraintStringArray = new std::string [4];
    constraintStringArray[0] = "pthread_mutex_init";
    constraintStringArray[1] = "pthread_mutex_lock";
    constraintStringArray[2] = "pthread_mutex_unlock";
    constraintStringArray[3] = "pthread_mutex_destroy";
    constraintManager->addConstraint("Spooler uses Mutex", constraintStringArray, 4);

    constraintStringArray = new std::string [3];
    constraintStringArray[0] = "shmget";
    constraintStringArray[1] = "shmat";
    constraintStringArray[2] = "shmdt";
    constraintManager->addConstraint("Spooler Uses Shared Memory", constraintStringArray, 3);

    constraintStringArray = new std::string [3];
    constraintStringArray[0] = "mkfifo";
    constraintStringArray[1] = "open";
    constraintStringArray[2] = "close";
    constraintManager->addConstraint("Spooler Provides the FiFo", constraintStringArray, 3);

    constraintStringArray = new std::string [1];
    constraintStringArray[0] = "sleep";
    constraintManager->addConstraint("Spooler Sleeps", constraintStringArray, 1);
}

void ConstraintInjector::injectMonitorConstraints(ConstraintManager *constraintManager) {

    auto* constraintStringArray = new std::string [3];
    constraintStringArray[0] = "shmget";
    constraintStringArray[1] = "shmat";
    constraintStringArray[2] = "shmdt";
    constraintManager->addConstraint("Monitor attaches Shared-Memory", constraintStringArray, 3);

    constraintStringArray = new std::string [3];
    constraintStringArray[0] = "sem_open";
    constraintStringArray[1] = "sem_trywait";
    constraintStringArray[2] = "sem_post";
    constraintManager->addConstraint("Writer uses Semaphore", constraintStringArray, 3);

    constraintStringArray = new std::string [3];
    constraintStringArray[0] = "pthread_mutex_lock";
    constraintStringArray[1] = "pthread_mutex_lock_unlock";
    constraintManager->addConstraint("Writer uses Mutex", constraintStringArray, 2);

    constraintStringArray = new std::string [1];
    constraintStringArray[0] = "sleep";
    constraintManager->addConstraint("Monitor Sleeps", constraintStringArray, 1);
}


#ifndef ConstraintInjectorClass
#define ConstraintInjectorClass
#include "../constants.hpp"
#include "constraint-manager.hpp"

class ConstraintInjector {

public:
    static void injectTestConstraints (ConstraintManager* constraintManager);
    static void injectWriterConstraints (ConstraintManager* constraintManager);
    static void injectSpoolerConstraints (ConstraintManager* constraintManager);
    static void injectMonitorConstraints (ConstraintManager* constraintManager);

};

#endif
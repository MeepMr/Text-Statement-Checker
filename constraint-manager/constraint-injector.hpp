#ifndef ConstraintInjectorClass
#define ConstraintInjectorClass
#pragma GCC diagnostic ignored "-Wc++11-extensions"
#include "constraint-manager.hpp"

class ConstraintInjector {

public:
    static void injectTestConstraints (ConstraintManager* constraintManager);
    static void injectWriterConstraints (ConstraintManager* constraintManager);
    static void injectSpoolerConstraints (ConstraintManager* constraintManager);
    static void injectMonitorConstraints (ConstraintManager* constraintManager);

};

#endif
#include "constraint-injector.hpp"

/**
 * Injects the Test-Constraints into the given constraintManager
 * @param constraintManager
 */
void ConstraintInjector::injectTestConstraints(ConstraintManager *constraintManager) {

    auto* testConstraint = new std::string [4];
    testConstraint[0] = "int";
    testConstraint[1] = "char";
    testConstraint[2] = "int";
    testConstraint[3] = "int";
    constraintManager->addConstraint("Test-Constraint", testConstraint, 4);
}

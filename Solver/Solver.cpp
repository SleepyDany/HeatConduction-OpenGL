#include "Solver.h"

SolverODEs::SolverODEs() : method_id(Undefined), step(0.0f)
{
}

SolverODEs::~SolverODEs()
{
}

std::string SolverODEs::getStringMethod()
{
    switch (method_id)
    {
    case Undefined:
        return "Undefined";

    default:
        method_id = Undefined;
        return "Undefined";
    }
}

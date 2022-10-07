#pragma once

#include <iostream>
#include <string>

#include <functional>

class SolverODEs
{
public:
    enum Method
    {
        Undefined
    };

public:
    SolverODEs();
    virtual ~SolverODEs();

    void setStep(float p_step) { step = p_step; }

    Method getMethod() const { return method_id; }
    std::string getStringMethod();
    void setMethod(Method method) { method_id = method; }

protected:
    
    float step;
    Method method_id;
};

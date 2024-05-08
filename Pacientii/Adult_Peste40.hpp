#pragma once
#include "./Adult.cpp"
#include "./Adult.hpp"
class Adult_peste40 : public Adult
{

public:
    Adult_peste40(){}
    Adult_peste40(Adult& a, bool fumator, float sedentarism);
    virtual ~Adult_peste40(){}
};
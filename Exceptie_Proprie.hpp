#pragma once
#include "includuri.hpp"


class Exceptie_Proprie : public exception
{
    string msg;
public:
    Exceptie_Proprie(const char* msg): msg(msg){}
    const char* what();
};
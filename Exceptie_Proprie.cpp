#pragma once

#include "Exceptie_Proprie.hpp"

const char* Exceptie_Proprie::what()
{
    return msg.c_str();
}

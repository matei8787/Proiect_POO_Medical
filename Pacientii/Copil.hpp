#pragma once
#include "./Pacient.cpp"
#include "./Pacient.hpp"
#include "./Adult.cpp"
#include "./Adult.hpp"
class Copil : public Pacient
{
    pair<Adult*, Adult*> parinti;
public:
    Copil(){}
    Copil(Pacient& eu, Adult* a1, Adult* a2): Pacient(eu), parinti(a1, a2){}
    int get_cate_naspa();
    pair<Adult*, Adult*>& get_parinti();
};
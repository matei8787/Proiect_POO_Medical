#pragma once
#include "./Substanta.hpp"
#include "./Substanta.cpp"

class Substanta_onsale : virtual public Substanta
{
    float reducere;
public:
    Substanta_onsale(){}
    Substanta_onsale(Substanta& s, float r): Substanta(s), reducere(r){}
    Substanta_onsale(string n, string u, float c, float i, float pr, Data d, float r): Substanta(n, u, c, i, pr, d), reducere(r){}
    float get_pret();
    void set_reducere(float r);
    float get_reducere();
    virtual void citeste(istream& in);
    virtual void afiseaza(ostream& out);
    virtual ~Substanta_onsale(){}
};
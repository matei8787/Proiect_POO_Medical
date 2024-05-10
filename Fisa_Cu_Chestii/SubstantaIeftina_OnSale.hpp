#pragma once
#include "./SubstantaIeftina.cpp"
#include "./SubstantaIeftina.hpp"
#include "./Substanta_OnSale.cpp"
#include "./Substanta_OnSale.hpp"

class SubstantaIeftina_onsale : public SubstantaIeftina, public Substanta_onsale
{
public:
    SubstantaIeftina_onsale(){}
    SubstantaIeftina_onsale(SubstantaIeftina& s1, Substanta_onsale& s2):SubstantaIeftina(s1), Substanta_onsale(s2){}
    SubstantaIeftina_onsale(string n, string u, float c, float i, float pr, Data d, float r, float p):SubstantaIeftina(n, u, c, i, pr, d, p), Substanta_onsale(n, u, c, i, p, d, r){}
    float get_pret();
    void citeste(istream& in);
    void afiseaza(ostream& out);
    virtual ~SubstantaIeftina_onsale(){}
};


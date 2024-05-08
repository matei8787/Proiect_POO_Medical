#pragma once
#include "./Substanta.hpp"
#include "./Substanta.cpp"
class SubstantaIeftina: virtual public Substanta
{
    float proc_impuritati;
public:
    SubstantaIeftina(){}
    SubstantaIeftina(Substanta& s, float p): Substanta(s), proc_impuritati(p){}
    SubstantaIeftina(string n, string u, float c, float i, float pr, Data d, float p): Substanta(n, u, c, i, pr, d), proc_impuritati(p){}
    void set_proc(float p);
    float get_proc();
    float get_pret();
    float calculeaza_intensitatea();
    virtual void citeste(istream& in);
    virtual void afiseaza(ostream& out);
    virtual ~SubstantaIeftina(){}
};
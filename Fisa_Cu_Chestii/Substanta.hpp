#pragma once
#include "../includuri.hpp"
#include "../Building_Blocks/Data.hpp"

class Substanta
{
    string nume, unitate;
    float cantitate, indice_intensitate, pret;
    Data expirare;

public:
    Substanta(){}
    Substanta(string n, string u, float c, float i, float p, Data d): nume(n), unitate(u), cantitate(c), indice_intensitate(i), pret(p), expirare(d){}
    void set_nume(string nume);
    void set_unitate(string unitate);
    void set_cantitate(float c);
    void set_expirare(Data d);
    void set_indice(float i);
    void set_pret(float p);
    float get_pret();
    float get_indice();
    Data get_expirare();
    float get_cantitate();
    string get_nume();
    string get_unitate();
    float calculeaza_intensitatea();
    virtual void afiseaza(ostream& out);
    virtual void citeste(istream& in);
    virtual ~Substanta(){}
};

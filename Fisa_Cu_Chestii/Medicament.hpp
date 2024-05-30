#pragma once
#include "./Substanta.cpp"
#include "./Substanta.hpp"
#include "./SubstantaIeftina.cpp"
#include "./SubstantaIeftina.hpp"
#include "./Substanta_OnSale.cpp"
#include "./Substanta_OnSAle.hpp"
#include "./SubstantaIeftina_OnSale.cpp"
#include "./SubstantaIeftina_OnSale.hpp"

class Medicament
{
    vector< shared_ptr<Substanta> > substante;
    string nume;
public:
    Medicament(){}
    Medicament(string nume, vector< shared_ptr<Substanta> >& v): nume(nume), substante(v){}
    void set_nume(string nume);
    void adauga_substanta(Substanta s);
    void sterge_substanta(string nume);
    void sterge_substanta(int i);
    float get_intensitate_totala();
    float get_pret();
    string get_nume();
    Substanta* get_substanta(int i);
    Substanta* get_substanta(string nume);
    friend ostream& operator<<(ostream& out, const Medicament& m);
    friend istream& operator>>(istream& in, Medicament& m);
    virtual ~Medicament(){}
};
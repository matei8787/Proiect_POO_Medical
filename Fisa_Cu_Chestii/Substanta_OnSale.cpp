#pragma once
#include "./Substanta_OnSale.hpp"

float Substanta_onsale::get_pret()
{
    return this -> Substanta::get_pret()*reducere;
}
void Substanta_onsale::set_reducere(float r)
{
    this -> reducere = r;
}
float Substanta_onsale::get_reducere()
{
    return this -> reducere;
}
void Substanta_onsale::citeste(istream& in)
{
    Substanta::citeste(in);
    in>>reducere;
    cout<<"AM atata reducere"<<reducere<<'\n';
}
void Substanta_onsale::afiseaza(ostream& out)
{
    afiseaza_substanta(out, this);
    out<<"AM atata reducere"<<reducere<<'\n';
}

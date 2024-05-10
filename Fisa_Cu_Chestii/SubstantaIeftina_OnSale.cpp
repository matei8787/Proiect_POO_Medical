#pragma once
#include "./SubstantaIeftina_OnSale.hpp"

float SubstantaIeftina_onsale::get_pret()
{
    return this -> SubstantaIeftina::get_pret() * get_reducere() *0.75;
}
void SubstantaIeftina_onsale::citeste(istream& in)
{
    SubstantaIeftina::citeste(in);
    float aux;
    in>>aux;
    Substanta_onsale::set_reducere(aux);
}
void SubstantaIeftina_onsale::afiseaza(ostream& out)
{
    afiseaza_substanta(out, this);
    out<<"Cu atatea impuritati: "<<get_proc()<<"\nsi reducerea asta"<<get_reducere()<<'\n';
}

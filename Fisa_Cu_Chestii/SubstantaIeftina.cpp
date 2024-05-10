#pragma once
#include "SubstantaIeftina.hpp"

void SubstantaIeftina::set_proc(float p)
{
    this -> proc_impuritati = p;
}
float SubstantaIeftina::get_proc()
{
    return this -> proc_impuritati;
}
float SubstantaIeftina::get_pret()
{
    return this -> Substanta::get_pret()*0.75;
}
float SubstantaIeftina::calculeaza_intensitatea()
{
    return Substanta::calculeaza_intensitatea() * (1 - proc_impuritati);
}
void SubstantaIeftina::citeste(istream& in)
{
    Substanta::citeste(in);
    in>>proc_impuritati;
}
void SubstantaIeftina::afiseaza(ostream& out)
{
    afiseaza_substanta(out, this);
    out<<"Am atatea impuritati: "<<proc_impuritati<<'\n';
}
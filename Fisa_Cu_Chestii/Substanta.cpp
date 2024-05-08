#pragma once
#include "./Substanta.hpp"

void afiseaza_substanta(ostream& out, Substanta* subst)
{
    out<<subst -> get_nume()<<" "<<subst -> get_cantitate()<<" "<<subst -> get_unitate()<<"\nPret: "<<subst -> get_pret()<<" RON\nData expirare: "<<subst -> get_expirare();

}
void Substanta::set_nume(string nume)
{
    this -> nume = nume;
}
void Substanta::set_unitate(string unitate)
{
    this -> unitate = unitate;
}
void Substanta::set_cantitate(float c)
{
    this -> cantitate = c;
}
void Substanta::set_expirare(Data d)
{
    this -> expirare = d;
}
void Substanta::set_indice(float idx)
{
    this -> indice_intensitate = idx;
}
void Substanta::set_pret(float p)
{
    this -> pret = p;
}
string Substanta::get_nume()
{
    return this -> nume;
}
string Substanta::get_unitate()
{
    return this -> unitate;
}
float Substanta::get_cantitate()
{
    return this -> cantitate;
}
Data Substanta::get_expirare()
{
    return this -> expirare;
}
float Substanta::get_indice()
{
    return this -> indice_intensitate;
}
float Substanta::get_pret()
{
    return this -> pret;
}
float Substanta::calculeaza_intensitatea()
{
    time_t t;
    struct tm* ti;
    time(&t);
    ti = localtime(&t);
    string aux = asctime(ti);
    map<string, int> mluna = {{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};
    string nuj = "";
    nuj += aux[4];
    nuj += aux[5];
    nuj += aux[6];
    int anul = (aux[(aux.size()-4)]-'0')*1000 + (aux[(aux.size()-3)]-'0')*100 + (aux[(aux.size()-2)]-'0')*10 + aux[(aux.size()-1)]-'0';
    Data azi((aux[8]-'0')*10+(aux[9]-'0'), mluna[nuj], anul, '.');
    if ( expirare.nrzile() < azi.nrzile() )
        return 0;
    return (expirare.nrzile()-azi.nrzile())*indice_intensitate*cantitate;
}
void Substanta::afiseaza(ostream& out)
{
    afiseaza_substanta(out, this);
}
void Substanta::citeste(istream& in)
{
    in>>this -> nume>>
    this -> unitate>>
    this -> cantitate>>
    this -> indice_intensitate>>
    this -> pret>>
    this -> expirare;
}

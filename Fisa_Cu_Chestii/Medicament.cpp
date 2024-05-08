#pragma once
#include "./Medicament.hpp"

void Medicament::set_nume(string nume)
{
    this -> nume = nume;
}
void Medicament::adauga_substanta(Substanta s)
{
    substante.push_back(&s);
}
void Medicament::sterge_substanta(int i)
{
    substante.erase(substante.begin() + i);
}
void Medicament::sterge_substanta(string nume)
{
    for ( int i = 0 ; i < substante.size() ; i++ )
    {
        if ( substante[i] -> get_nume() == nume )
        {
            substante.erase(substante.begin() + i);
            return;
        }
    }
}
string Medicament::get_nume()
{
    return this -> nume;
}
float Medicament::get_pret()
{
    float ans = 0;
    for ( Substanta* s : substante )
    {
        ans += s -> get_pret();
    }
    return ans;
}
float Medicament::get_intensitate_totala()
{
    float ans = 0;
    for( Substanta* s : substante )
    {
        ans += s -> calculeaza_intensitatea();
    }
    return ans;
}
Substanta* Medicament::get_substanta(int i)
{
    return substante[i];
}
Substanta* Medicament::get_substanta(string nume)
{
    for ( Substanta* s : substante )
    {
        if ( s -> get_nume() == nume )
            return s;
    }
    string msg = "Medicamentul nu are Substanta" + nume;
    throw Exceptie_Proprie(msg.c_str());
}
ostream& operator<<(ostream& out, const Medicament& m)
{
    out<<m.nume<<":\n";
    for ( Substanta* s : m.substante )
    {
        s -> afiseaza(out);
        out<<'\n';
    }
    return out;
}
istream& operator>>(istream& in, Medicament& m)
{
    int nr_substante;
    in>>m.nume;
    in>>nr_substante;
    for ( int i = 1 ; i <= nr_substante ; i++ )
    {
        int tip; ///0=normal, 1=ieftin, 2=onsale, 3=ambele
        in>>tip;
        in.get();
        Substanta* s;
        SubstantaIeftina_onsale sios;
        if ( tip == 1 )
        {
            s = new SubstantaIeftina();
            s -> citeste(in);
        }
        else if ( tip == 2 )
        {
            s = new Substanta_onsale();
            s -> citeste(in);
        }
        else if ( tip == 3 )
        {
            s = new SubstantaIeftina_onsale();
            s -> citeste(in);
        }
        else
        {
            s = new Substanta();
            s -> citeste(in);
        }
        m.substante.push_back(s);
    }
    return in;
}
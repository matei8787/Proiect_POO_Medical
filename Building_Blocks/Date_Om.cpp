#pragma once
#include "Date_Om.hpp"

void Date_om::set_nume(string nume)
{
    this -> nume = nume;
}
void Date_om::set_prenume(string prenume)
{
    this -> prenu = prenume;
}
void Date_om::set_adresa(string ad)
{
    this -> adresa = ad;
}
void Date_om::set_ani(int a)
{
    this -> ani = a;
}
string Date_om::get_nume()
{
    return nume;
}
string Date_om::get_prenume()
{
    return prenu;
}
string Date_om::get_adresa()
{
    return adresa;
}
int Date_om::get_ani()
{
    return ani;
}
bool Date_om::operator==(const Date_om& om) const
{
    return (this -> nume == om.nume && this -> prenu == om.prenu && this -> ani == om.ani);
}
ostream& operator<<(ostream& out, const Date_om& om)
{
    out<<om.nume<<" "<<om.prenu<<"\nVarsta: "<<om.ani<<" ani\nLocuinta: "<<om.adresa;
    return out;
}
istream& operator>>(istream& in, Date_om& om)
{
    in>>om.nume>>om.prenu>>om.ani;
    in.get();
    getline(in, om.adresa);
    return in;
}
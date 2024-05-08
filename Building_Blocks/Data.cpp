#pragma once

#include "./Data.hpp"

int Data::nrzile(int luna, int an)
{
    int Z[13]={31,31,28,31,30,31,30,31,31,30,31,30,31};
    if(luna!=2 || !(an%4==0 && an%100!=0 || an%400==0)) return Z[luna];
    else return 29;
}
int Data::nrzile()
{
    Data d = *this;
    int z=(d.an-1)*365+(d.an-1)/4-(d.an-1)/100+(d.an-1)/400;
    for(int i=1;i<d.luna;i++)
        z=z+nrzile(i,d.an);
    return z+d.zi;
}
void Data::set_zi(int zi)
{
    this -> zi = zi;
}
void Data::set_luna(int luna)
{
    this -> luna = luna;
}
void Data::set_an(int an)
{
    this -> an = an;
}
void Data::set_sep(char c)
{
    this -> sep = c;
}
int Data::get_zi()
{
    return zi;
}
int Data::get_luna()
{
    return luna;
}
int Data::get_an()
{
    return an;
}
char Data::get_sep()
{
    return sep;
}
bool Data::operator==(const Data& d) const
{
    return (this -> zi == d.zi && this -> luna == d.luna && this -> an == d.an);
}
ostream& operator<< (ostream& out, const Data& d)
{
    if ( d.zi < 10 )
        out<<0;
    out<<d.zi<<d.sep;
    if ( d.luna < 10 )
        out<<0;
    out<<d.luna<<d.sep<<d.an;
    return out;
}
istream& operator>> (istream& in, Data& d)
{
    in>>d.zi>>d.luna>>d.an;
    return in;
}
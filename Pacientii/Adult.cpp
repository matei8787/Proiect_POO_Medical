#pragma once
#include "Adult.hpp"

Adult::Adult(Pacient& eu, Pacient* copil): Pacient(eu)
{
    copii.push_back(copil);
}
void Adult::adauga_copil(Pacient* p)
{
    copii.push_back(p);
}
void Adult::sterge_copil(Pacient* p)
{
    for ( int i = 0 ; i < copii.size() ; i++ )
    {
        if ( copii[i] == p )
        {
            copii.erase(copii.begin() + i);
            return;
        }
    }
}
void Adult::sterge_copil(string prenume)
{
    for ( int i = 0 ; i < copii.size() ; i++ )
    {
        if ( copii[i]->get_date().get_prenume() == prenume )
        {
            copii.erase(copii.begin() + i);
            return;
        }
    }
}
void Adult::sterge_copil(int i)
{
    copii.erase(copii.begin() + i);
}
bool Adult::operator==(const Adult& a) const
{
    return (this->date == a.date);
}
istream& operator>>(istream& in, Adult& a)
{
    Pacient aux;
    in>>aux;
    int n; /// nr_copii
    in>>n;
    vector<Pacient*> v;
    for ( int i = 1 ; i <= n ; i++ )
    {
        Pacient* p = new Pacient();
        in>>(*p);
        v.push_back(p);
    }
    a = Adult(aux, v);
    return in;
}


ostream& operator<<(ostream& out, const Adult& a)
{
    const Pacient* aux = &a;
    out<<aux<<'\n';
    out<<"Cu "<<a.copii.size()<<" copii\n";
    for ( int i = 0 ; i < a.copii.size() ; i++ )
    {
        out<<a.copii[i]<<'\n';
    }
    return out;
}

#pragma once
#include "./Afisare_Abstracta.hpp"
template<typename T, typename U>
void Afisare_Abstracta<T, U>::set_nume(string n)
{
    this -> nume = n;
}
template<typename T, typename U>
string Afisare_Abstracta<T, U>::get_nume()
{
    return this -> nume;
}
template<typename T, typename U>
void Afisare_Abstracta<T, U>::creeaza(vector<U*>& total)
{
    for ( U* chestie : total )
    {
        T bucket = crt(chestie);
        if ( afisati.find(bucket) == afisati.end() )
        {
            afisati.insert(make_pair(bucket, *(new vector<U*>({chestie}))));
        }
        else
        {
            afisati[bucket].push_back(chestie);
        }
    }
}
template<typename T, typename U>
void Afisare_Abstracta<T, U>::afisare_simplu(ostream& out, T select)
{
    for ( U* chestie : afisati[select] )
    {
        out<<(*chestie)<<'\n';
    }
}
template<typename T, typename U>
void Afisare_Abstracta<T, U>::afisare_specific(ostream&out, T select, function<int(U*)>& f, vector<int>& ord, map<int, string>& den)
{
    int j = 0;
    while ( j < ord.size() )
    {
        out<<den[ord[j]]<<'\n';
        for ( U* chestie : afisati[select] )
        {
            int aux = f(chestie);
            if ( aux == ord[j] )
            {
                out<<(*chestie)<<'\n';
            }
        }
        j++;
    }
}
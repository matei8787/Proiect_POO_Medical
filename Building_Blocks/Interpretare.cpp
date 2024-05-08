#pragma once
#include "Interpretare.hpp"

template<typename T, typename U>
void Restrictie<T, U>::set_restrictie(function<T(U)>& f)
{
    this -> restrictie = f;
}
template<typename T, typename U>
bool Restrictie<T, U>::e_normal(U prop)
{
    T eval = restrictie(prop);
    for ( T e : evaluari_normale )
    {
        if ( e == eval )
            return true;
    }
    return false;
}
template<typename T, typename U>
void Restrictie<T, U>::set_denumiri(map<T, string>& m)
{
    this -> denumiri = m;
}
template<typename T, typename U>
map<T, string>& Restrictie<T, U>::get_denumiri()
{
    return denumiri;
}
template<typename T, typename U>
function<T(U)>& Restrictie<T, U>::get_restrictie()
{
    return restrictie;
}
template<typename T, typename U>
string Restrictie<T, U>::evalueaza(U prop)
{
    T retur = restrictie(prop);
    return denumiri[retur];
}
template<typename T, typename U>
void Restrictie<T,U>::set_normale(vector<T>& v)
{
    this -> evaluari_normale = v;
}
template<typename T, typename U>
void Restrictie<T, U>::adauga_normal(T normal)
{
    this -> evaluari_normale.push_back(normal);
}
template<typename T, typename U>
vector<T>& Restrictie<T, U>::get_normale()
{
    return this -> evaluari_normale;
}
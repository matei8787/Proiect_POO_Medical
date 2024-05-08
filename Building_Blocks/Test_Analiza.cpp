#pragma once

#include "Test_Analiza.hpp"

template<typename T, typename U>
void Test_analiza<T, U>::set_substanta(string s)
{
    this -> substanta = s;
}
template<typename T, typename U>
void Test_analiza<T, U>::set_indicator(U i)
{
    this -> indicator = i;
}
template<typename T, typename U>
void Test_analiza<T, U>::set_data(Data& d)
{
    this -> d = d;
}
template<typename T, typename U>
void Test_analiza<T, U>::set_data(int zi, int luna, int an, char sep)
{
    this -> d.set_zi(zi);
    this -> d.set_luna(luna);
    this -> d.set_an(an);
    this -> d.set_sep(sep);
}
template<typename T, typename U>
void Test_analiza<T, U>::set_unitate(string u)
{
    this -> unitate = u;
}
template<typename T, typename U>
string Test_analiza<T, U>::get_substanta()
{
    return substanta;
}
template<typename T, typename U>
string Test_analiza<T, U>::get_unitate()
{
    return unitate;
}
template<typename T, typename U>
U Test_analiza<T, U>::get_indicator()
{
    return indicator;
}
template<typename T, typename U>
Data& Test_analiza<T, U>::get_data()
{
    return d;
}
template<typename T, typename U>
void Test_analiza<T, U>::set_restrictia(Restrictie<T, U>& r)
{
    this -> restrictia = r;
}
template<typename T, typename U>
Restrictie<T, U>& Test_analiza<T, U>::get_restrictia()
{
    return restrictia;
}
template<typename T, typename U>
string Test_analiza<T, U>::evalueaza()
{
    return this -> restrictia.evalueaza(this -> indicator);
}
template<typename T, typename U>
void Test_analiza<T, U>::afiseaza(ostream& out)
{
    out<<substanta<<" ("<<d<<"): "<<indicator<<" "<<unitate;
}
template<typename T, typename U>
void Test_analiza<T, U>::citeste(istream& in)
{
    in>>this -> substanta>>this -> indicator>>this -> d>>this -> unitate;

}
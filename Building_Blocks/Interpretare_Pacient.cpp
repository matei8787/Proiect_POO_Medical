#pragma once
#include "./Interpretare_Pacient.hpp"

template<typename T, typename U>
void Restrictie_Pacient<T, U>::set_nume(string nume)
{
    this -> nume = nume;
}
template<typename T, typename U>
void Restrictie_Pacient<T, U>::set_eval(U eval)
{
    this -> evaluare = eval;
}
template<typename T, typename U>
U Restrictie_Pacient<T, U>::get_eval()
{
    return this -> evaluare;
}
template<typename T, typename U>
string Restrictie_Pacient<T, U>::get_nume()
{
    return this -> nume;
}
template<typename T, typename U>
string Restrictie_Pacient<T, U>::evalueaza()
{
    return Restrictie<T, U>::evalueaza(this -> evaluare);
}
template<typename T, typename U>
void Restrictie_Pacient<T, U>::citeste(istream& in)
{
    in>>this -> nume>>this -> evaluare;
}
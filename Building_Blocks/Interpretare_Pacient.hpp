#pragma once
#include "./Interpretare.cpp"
#include "./Interpretare.hpp"

template<typename T, typename U>
class Restrictie_Pacient : public Restrictie<T, U>
{
    string nume;
    U evaluare;
public:
    Restrictie_Pacient(){}
    Restrictie_Pacient(Restrictie<T, U>& r, string nume, U prop): Restrictie<T, U>(r), nume(nume), evaluare(prop){}
    Restrictie_Pacient(function<T(U)>& f, map<T, string>& m, vector<T>& eval, string nume, U prop): Restrictie<T, U>(f, m, eval), nume(nume), evaluare(prop){}
    void set_nume(string nume);
    void set_eval(U eval);
    U get_eval();
    string get_nume();
    string evalueaza();
    void citeste(istream& in);
    template<typename V, typename W>
    bool operator==(const Restrictie_Pacient<V, W>& r) const
    {
        return this -> nume == r.nume;
    }
    virtual ~Restrictie_Pacient(){}
};
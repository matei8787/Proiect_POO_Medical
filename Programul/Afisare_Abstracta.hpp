#pragma once
#include "../includuri.hpp"
template<typename T, typename U>
class Afisare_Abstracta
{
    string nume;
    function<T(U*)> crt;
    map< T, vector<U*> > afisati;
    void creeaza(vector<U*>& total);
public:
    Afisare_Abstracta(){}
    Afisare_Abstracta(string n, function<T(U*)>& f, vector<U*>& total): nume(n), crt(f) { creeaza(total); }
    string get_nume();
    void set_nume(string n);
    void afisare_simplu(ostream& out, T selectarea);
    void afisare_specific(ostream& out, T selectarea, function<int(U*)> &care, vector<int>& ordine, map<int, string>& denumiri);
};
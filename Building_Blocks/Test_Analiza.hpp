#pragma once
#include "./Data.cpp"
#include "./Interpretare.cpp"

template<typename T, typename U>
class Test_analiza
{
    string substanta, unitate;
    U indicator;
    Data d;
    Restrictie<T, U> restrictia;
public:
    Test_analiza(){}
    Test_analiza(string s, string u, U i, Data& d, Restrictie<T, U> r): substanta(s), unitate(u), indicator(i), d(d), restrictia(r){}
    Test_analiza(string s, string u, U i, int zi, int luna, int an, char sep, Restrictie<T, U> r): substanta(s), unitate(u), indicator(i), d(zi, luna, an, sep), restrictia(r){}
    Test_analiza(string s, string u, U i, Data& d, function<T(U)> &f, map<T, string>& m, vector<T>& evals): substanta(s), unitate(u), indicator(i), d(d), restrictia(f, m, evals){}
    Test_analiza(string s, string u, U i, int zi, int luna, int an, char sep, function<T(U)> &f, map<T, string>& m, vector<T>& evals): substanta(s), unitate(u), indicator(i), d(zi, luna, an, sep), restrictia(f, m, evals){}
    void set_substanta(string s);
    void set_indicator(U i);
    void set_data(Data& d);
    void set_data(int zi, int luna, int an, char sep);
    void set_unitate(string u);
    void set_restrictia(Restrictie<T, U>& r);
    string get_substanta();
    string get_unitate();
    U get_indicator();
    Data& get_data();
    Restrictie<T, U>& get_restrictia();
    string evalueaza();
    void afiseaza(ostream& out);
    void citeste(istream& in);
    virtual ~Test_analiza(){}
};
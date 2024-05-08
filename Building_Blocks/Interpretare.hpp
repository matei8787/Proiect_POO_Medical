#pragma once
#include "../includuri.hpp"

///nivelurile T de restrictie pentru proprietatea U
///in mare, T e o multime de numere pentru care se va verifica
///cu ajutorul unei functii reguli pentru proprietatea U

///edit: acum cand dau design la baza de date,
///observ ca mai puteam abstractiza putin map-ul
///la modul ca mai puteam sa mai bag un tip si sa mapeze la acel tip
///pentru map<T, Pacient> gen

template<typename T, typename U>
class Restrictie
{
    function<T(U)> restrictie;
    map<T, string> denumiri; ///gen 0 = optim, 1 = normal, 2 = crescut     (sau)
                             ///0 = nefumator, 1 = fumator
    vector<T> evaluari_normale;
public:
    Restrictie(){}
    Restrictie(function<T(U)>& f, map<T, string>& denumiri, vector<T>& evals):restrictie(f), denumiri(denumiri), evaluari_normale(evals){}
    void set_restrictie(function<T(U)>& f);
    void set_denumiri(map<T, string>& m);
    void set_normale(vector<T>& evals);
    void adauga_normal(T normal);
    map<T, string>& get_denumiri();
    function<T(U)>& get_restrictie();
    vector<T>& get_normale();
    bool e_normal(U prop);
    string evalueaza(U prop);
    virtual ~Restrictie(){}
};
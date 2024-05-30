#pragma once
#include "./Baza_De_Date.hpp"

namespace util
{
    ///acum imi dau seama ca pot face asta
    template<typename T, typename U>
    void sterge_din_vector(vector<T>& v, U x, function<bool(T, U)>& f)
    {
        for ( int i = 0 ; i < v.size() ; i++ )
        {
            if ( f(v[i], x) )
            {
                v.erase(v.begin() + i);
                return;
            }
        }
    }
}


Pacient* Baza_De_Date::get_pacient(string nume, string prenume)
{
    for ( Pacient* p : pacienti_totali )
    {
        if ( p->get_date().get_nume() == nume && p -> get_date().get_prenume() == prenume )
            return p;
    }
    return NULL;
}
Medicament* Baza_De_Date::get_medicament(string nume)
{
    for ( Medicament* m : medicamente )
    {
        if ( m -> get_nume() == nume )
            return m;
    }
    return NULL;
}
void Baza_De_Date::adauga_pacient(Pacient* p)
{
    pacienti_totali.push_back(p);
}
void Baza_De_Date::adauga_medicament(Medicament* m)
{
    medicamente.push_back(m);
}
void Baza_De_Date::adauga_afp_simplu(Afisare_Abstracta<bool, Pacient>* af)
{
    afisari_simple.push_back(af);
}
void Baza_De_Date::adauga_afp_select(Afisare_Abstracta<string, Pacient>* af)
{
    afisari_selective.push_back(af);
}
void Baza_De_Date::adauga_afm_simplu(Afisare_Abstracta<bool, Medicament>* af)
{
    afisari_simple_medicamente.push_back(af);
}
void Baza_De_Date::adauga_afm_select(Afisare_Abstracta<string, Medicament>* af)
{
    afisari_selective_medicamente.push_back(af);
}
void Baza_De_Date::sterge_pacient(Pacient* p)
{  
    function<bool(Pacient*, Pacient*)> aux = ([](Pacient* p, Pacient* u){return p == u;});
    util::sterge_din_vector<Pacient*, Pacient*>(pacienti_totali, p, aux);
}
void Baza_De_Date::sterge_pacient(Date_om d)
{
    function<bool(Pacient*, Date_om)>aux = ([](Pacient* p, Date_om u){return p->get_date() == u;});
    util::sterge_din_vector<Pacient*, Date_om>(pacienti_totali, d, aux);
}
void Baza_De_Date::sterge_pacient(string nume, string prenume)
{
    function<bool(Pacient*, pair<string, string>)> aux = ([](Pacient* p, pair<string, string> u){return (p->get_date().get_nume() == u.first && p->get_date().get_prenume() == u.second);});
    util::sterge_din_vector<Pacient*, pair<string, string> >(pacienti_totali, make_pair(nume, prenume), aux);
}
void Baza_De_Date::sterge_pacient(int i)
{
    pacienti_totali.erase(pacienti_totali.begin() + i);
}
void Baza_De_Date::sterge_medicament(Medicament* m)
{
    function<bool(Medicament*, Medicament*)> aux = ([](Medicament* p, Medicament* u){return p == u;});
    util::sterge_din_vector<Medicament*, Medicament*>(medicamente, m, aux);
}
void Baza_De_Date::sterge_medicament(string nume)
{
    function<bool(Medicament*, string)> aux = ([](Medicament* p, string u){return p->get_nume() == u;});
    util::sterge_din_vector<Medicament*, string>(medicamente, nume, aux);
}
void Baza_De_Date::sterge_medicament(int i)
{
    medicamente.erase(medicamente.begin() + i);
}
vector<Pacient*>& Baza_De_Date::get_pacienti()
{
    return this -> pacienti_totali;
}
vector<Medicament*>& Baza_De_Date::get_medicamente()
{
    return this -> medicamente;
}
vector<Afisare_Abstracta<bool, Pacient>*>& Baza_De_Date::get_afp_simplu()
{
    return this -> afisari_simple;
}
Afisare_Abstracta<bool, Pacient>* Baza_De_Date::get_afp_simplu(string nume)
{
    for ( Afisare_Abstracta<bool, Pacient>* af : this -> afisari_simple )
    {
        if ( af->get_nume() == nume )
            return af;
    }
    return NULL;
}
vector<Afisare_Abstracta<string, Pacient>*>& Baza_De_Date::get_afp_select()
{
    return this -> afisari_selective;
}
Afisare_Abstracta<string, Pacient>* Baza_De_Date::get_afp_select(string nume)
{
    for ( Afisare_Abstracta<string, Pacient>* af : this -> afisari_selective )
    {
        if ( af->get_nume() == nume )
            return af;
    }
    return NULL;
}
vector<Afisare_Abstracta<bool, Medicament>*>& Baza_De_Date::get_afm_simplu()
{
    return this -> afisari_simple_medicamente;
}
Afisare_Abstracta<bool, Medicament>* Baza_De_Date::get_afm_simplu(string nume)
{
    for ( Afisare_Abstracta<bool, Medicament>* af : this -> afisari_simple_medicamente )
    {
        if ( af->get_nume() == nume )
            return af;
    }
    return NULL;
}
vector<Afisare_Abstracta<string, Medicament>*>& Baza_De_Date::get_afm_select()
{
    return this -> afisari_selective_medicamente;
}
Afisare_Abstracta<string, Medicament>* Baza_De_Date::get_afm_select(string nume)
{
    for ( Afisare_Abstracta<string, Medicament>* af : this -> afisari_selective_medicamente )
    {
        if ( af->get_nume() == nume )
            return af;
    }
    return NULL;
}
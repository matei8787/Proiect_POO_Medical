#pragma once
#include "Fisa.hpp"

void Fisa::adauga_medicament(Medicament* m)
{
    this -> tratament_activ.push_back(m);
}
void Fisa::adauga_numeric(Test_analiza<int, float>* t)
{
    this -> analize_numerice.push_back(t);
}
void Fisa::adauga_boolean(Test_analiza<bool, float>* t)
{
    this -> analize_booleene.push_back(t);
}
void Fisa::sterge_medicament(string nume)
{
    for ( int i = 0 ; i < tratament_activ.size() ; i++ )
    {
        if ( tratament_activ[i] -> get_nume() == nume )
        {
            tratament_activ.erase(tratament_activ.begin() + i);
            return;
        }
    }
}
void Fisa::sterge_medicament(int i)
{
    tratament_activ.erase(tratament_activ.begin() + i);
}
void Fisa::sterge_numeric(string nume)
{
    for ( int i = 0 ; i < analize_numerice.size() ; i++ )
    {
        try{
            if ( analize_numerice[i]->get_substanta() == nume )
            {
                analize_numerice.erase(analize_numerice.begin() + i);
                return;
            }
        } catch (const exception& e)
        {
            cerr<<e.what()<<'\n';
        }
    }
}
void Fisa::sterge_numeric(int i)
{
    analize_numerice.erase(analize_numerice.begin() + i);
}
void Fisa::sterge_boolean(string nume)
{
    for ( int i = 0 ; i < analize_booleene.size() ; i++ )
    {
        try{
        if ( analize_booleene[i]->get_substanta() == nume )
        {
            analize_booleene.erase(analize_booleene.begin() + i);
            return;
        }
        }catch(const exception& e)
        {
            cerr<<e.what()<<'\n';
        }
    }
}
void Fisa::sterge_boolean(int i)
{
    analize_booleene.erase(analize_booleene.begin() + i);
}
vector< Test_analiza<int, float>* >& Fisa::get_analize_numerice()
{
    return this -> analize_numerice;
}
vector< Test_analiza<bool, float>* >& Fisa::get_analize_booleene()
{
    return this -> analize_booleene;
}
Medicament* Fisa::get_medicament(string nume)
{
    for ( Medicament* m : tratament_activ )
    {
        if ( m -> get_nume() == nume )
            return m;
    }
    return nullptr;
}
Medicament* Fisa::get_medicament(int i)
{
    return tratament_activ[i];
}
Test_analiza<int, float>* Fisa::get_analiza_numerica(string nume)
{
    for ( Test_analiza<int, float>* t : analize_numerice )
    {
        try{
        if ( t -> get_substanta() == nume )
            return t;
        }catch(const exception& e)
        {
            cerr<<e.what()<<'\n';
        }
    }
    string msg = "Nu am gasit analiza " + nume;
    throw Exceptie_Proprie(msg.c_str());
}
Test_analiza<int, float>* Fisa::get_analiza_numerica(int i)
{
    return analize_numerice[i];
}
Test_analiza<bool, float>* Fisa::get_analiza_booleana(string nume)
{
    for ( Test_analiza<bool, float>* t : analize_booleene )
    {
        if ( t -> get_substanta() == nume )
            return t;
    }
    return nullptr;
}
Test_analiza<bool, float>* Fisa::get_analiza_booleana(int i)
{
    return analize_booleene[i];
}
void Fisa::citeste_tratament_activ(istream& in)
{
    int n;///nr_medicamente
    in>>n;
    for ( int i = 1 ; i <= n ; i++ )
    {
        Medicament aux;
        in>>aux;
        tratament_activ.push_back(&aux);
    }
}
void Fisa::citeste_analize_numerice(istream& in)
{
    int n; ///nr analize
    in>>n;
    for ( int i = 1 ; i <= n ; i++ )
    {
        Test_analiza<int, float> t;
        t.citeste(in);
        analize_numerice.push_back(&t);
    }
}
void Fisa::citeste_analize_booleene(istream& in)
{
    int n;
    in>>n;
    for ( int i = 1 ; i <= n ; i++ )
    {
        Test_analiza<bool, float> t;
        t.citeste(in);
        analize_booleene.push_back(&t);
    }
}

void Fisa::afiseaza_analize_booleene(ostream& out)
{
    for ( Test_analiza<bool, float>* t : analize_booleene )
    {
        t -> afiseaza(out);
    }
}
void Fisa::afiseaza_analize_numerice(ostream& out)
{
    for ( Test_analiza<int, float>* t: analize_numerice )
    {
        t -> afiseaza(out);
    }
}
void Fisa::afiseaza_tratament_activ(ostream& out)
{
    for ( Medicament* m : tratament_activ )
    {
        out<<(*m);
    }
}
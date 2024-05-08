#pragma once
#include "../Building_Blocks/Test_Analiza.cpp"
#include "../Building_Blocks/Test_Analiza.hpp"
#include "./Medicament.cpp"
#include "./Medicament.hpp"

class Fisa
{
    vector<Medicament*> tratament_activ;
    vector< Test_analiza<int, float>* > analize_numerice; ///care verifica o valoare si il pune intr-un bucket
    vector< Test_analiza<bool, float>* > analize_booleene; ///care verifica o valoare si vede daca este sau nu cumva
public:
    Fisa(){}
    Fisa(vector<Medicament*>& v, vector<Test_analiza<int, float>*>& an, vector<Test_analiza<bool, float>*>& ab): tratament_activ(v), analize_numerice(an), analize_booleene(ab){}
    void adauga_medicament(Medicament* m);
    void adauga_numeric(Test_analiza<int, float>* t);
    void adauga_boolean(Test_analiza<bool, float>* t);
    void sterge_medicament(string nume);
    void sterge_medicament(int i);
    void sterge_numeric(string nume_sub);
    void sterge_numeric(int i);
    void sterge_boolean(string nuem_sub);
    void sterge_boolean(int i);
    Medicament* get_medicament(int i);
    Medicament* get_medicament(string nume);
    Test_analiza<int, float>* get_analiza_numerica(int i);
    Test_analiza<int, float>* get_analiza_numerica(string nume_substanta);
    Test_analiza<bool, float>* get_analiza_booleana(int i);
    Test_analiza<bool, float>* get_analiza_booleana(string nume_substanta);
    vector< Test_analiza<int, float>* >& get_analize_numerice();
    vector< Test_analiza<bool, float>* >& get_analize_booleene();
    void citeste_tratament_activ(istream& in);
    void citeste_analize_numerice(istream& in);
    void citeste_analize_booleene(istream& in);
    void afiseaza_analize_numerice(ostream& out);
    void afiseaza_analize_booleene(ostream& out);
    void afiseaza_tratament_activ(ostream& out);
    virtual ~Fisa(){}
};
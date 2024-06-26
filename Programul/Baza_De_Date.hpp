#pragma once
#include "../includuri_baza_date.hpp"

class Baza_De_Date
{
    static Baza_De_Date* baza;
    vector<Pacient*> pacienti_totali;
    vector<Medicament*> medicamente;
    vector<Afisare_Abstracta<bool, Pacient>*> afisari_simple; ///toti pacientii care ...
    vector<Afisare_Abstracta<string, Pacient>*> afisari_selective; ///toti pacientii care fac parte din familia x
    vector<Afisare_Abstracta<bool, Medicament>* >afisari_simple_medicamente;
    vector<Afisare_Abstracta<string, Medicament>* >afisari_selective_medicamente;
    Baza_De_Date(){}
    Baza_De_Date(vector<Pacient*> pacienti, vector<Medicament*> medicamente): pacienti_totali(pacienti), medicamente(medicamente){}
public:
    static Baza_De_Date* get_instanta()
    {
        if ( baza == NULL )
        {
            baza = new Baza_De_Date();
        }
        return baza;
    }
    void adauga_pacient(Pacient* p);
    void adauga_medicament(Medicament* m);
    void adauga_afp_simplu(Afisare_Abstracta<bool, Pacient>* af);
    void adauga_afp_select(Afisare_Abstracta<string, Pacient>* af);
    void adauga_afm_simplu(Afisare_Abstracta<bool, Medicament>* af);
    void adauga_afm_select(Afisare_Abstracta<string, Medicament>* af);
    void sterge_pacient(Pacient* p);
    void sterge_pacient(Date_om d);
    void sterge_pacient(string nume, string prenume);
    void sterge_pacient(int i);
    void sterge_medicament(Medicament* m);
    void sterge_medicament(string nume);
    void sterge_medicament(int i);
    ///NU EXISTA SA STERGI AFISARI :)
    vector<Pacient*>& get_pacienti();
    Pacient* get_pacient(string nume, string prenume);
    vector<Medicament*>& get_medicamente();
    Medicament* get_medicament(string nume);
    vector<Afisare_Abstracta<bool, Pacient>*>& get_afp_simplu();
    Afisare_Abstracta<bool, Pacient>* get_afp_simplu(string nume);
    vector<Afisare_Abstracta<string, Pacient>*>& get_afp_select();
    Afisare_Abstracta<string, Pacient>* get_afp_select(string nume);
    vector<Afisare_Abstracta<bool, Medicament>*>& get_afm_simplu();
    Afisare_Abstracta<bool, Medicament>* get_afm_simplu(string nume);
    vector<Afisare_Abstracta<string, Medicament>*>& get_afm_select();
    Afisare_Abstracta<string, Medicament>* get_afm_select(string nume);
};
Baza_De_Date* Baza_De_Date::baza= NULL;
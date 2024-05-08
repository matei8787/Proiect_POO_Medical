#pragma once
#include "./Baza_De_Date.cpp"
#include "./Baza_De_Date.hpp"

class Program
{
    static map<int, string> mpcardio;
    vector<float> masoara;
    Baza_De_Date baza;
    vector<Data> date_random;
    Test_analiza<bool, float> tensiune_buna, tensiune_naspa, proteina_c_optim, proteina_c_naspa;
    Test_analiza<int, float> colesterol_optim, colesterol_normal, colesterol_crescut;
public:
    template<typename T, typename ...Types>
    static T* creeaza(Types ...args_constructor);
    template<typename T>
    static void Adauga_Risc_Cardiovascular(T*& p);
    void baga_date_random(int nr);
    void baga_medicamente_random(int nr);
    vector<Medicament*> tratament_random(int cate);
    void creeaza_teste();
    void afis_medicamente(ostream& _out);
    void baga_ierarhia();
    void baga_afisari();
    void incepe_baza_de_date();
    void af_medicamente();
    void af_pacienti();
    void afisari();
    void run();
};
map<int, string> Program::mpcardio = {{0, "NU"}, {1, "DA"}, {2, "RIDICAT"}};

#pragma once
#include "../Fisa_Cu_Chestii/Fisa.cpp"
#include "../Fisa_Cu_Chestii/Fisa.hpp"
#include "../Building_Blocks/Interpretare_Pacient.cpp"
#include "../Building_Blocks/Interpretare_Pacient.hpp"
class Pacient
{
    Fisa* f;
    vector< Restrictie_Pacient<int, float>* > prop_numerice; ///cat de sedentar este
    vector< Restrictie_Pacient<bool, float>* > prop_booleene_masurabile; ///cat de gras este
    vector< Restrictie_Pacient<bool, bool>* > prop_booleene; ///este fumator sau nu
protected:
    Date_om date;
public:
    Pacient(){}
    Pacient(Date_om d, Fisa* f): f(f), date(d){}
    Pacient(Date_om d, Fisa* f, vector< Restrictie_Pacient<int, float>* > & pn, vector< Restrictie_Pacient<bool, float>* >& pbm, vector< Restrictie_Pacient<bool, bool>* >& pb);
    Pacient(string n, string p, string ad, int a, Fisa* f, vector< Restrictie_Pacient<int, float>* > & pn, vector< Restrictie_Pacient<bool, float>* >& pbm, vector< Restrictie_Pacient<bool, bool>* >& pb);
    /// imi cer scuze pentru ce am facut mai sus
    /// promit ca nu mi-am dat seama ca se rezolva usor problema cand am mai multi parametrii de tipuri mai de baza decat prea tarziu
    /// aia e, csf, ncsf
    void set_date(Date_om d);
    void set_fisa(Fisa* f);
    void adauga_prop_numerica(Restrictie_Pacient<int, float>* prop);
    void adauga_prop_bool_mas(Restrictie_Pacient<bool, float>* prop);
    void adauga_prop_booleana(Restrictie_Pacient<bool, bool>* prop);
    void sterge_prop_numerica(Restrictie_Pacient<int, float>* prop);
    void sterge_prop_bool_mas(Restrictie_Pacient<bool, float>* prop);
    void sterge_prop_booleana(Restrictie_Pacient<bool, bool>* prop);
    void sterge_prop_numerica(int i);
    void sterge_prop_bool_mas(int i);
    void sterge_prop_booleana(int i);
    void sterge_prop_numerica(string nume);
    void sterge_prop_bool_mas(string nume);
    void sterge_prop_booleana(string nume);
    vector< Restrictie_Pacient<int, float>* >& get_prop_numerice();
    vector< Restrictie_Pacient<bool, float>* >& get_prop_bool_mas();
    vector< Restrictie_Pacient<bool, bool>* >& get_prop_booleene();
    Restrictie_Pacient<int, float>* get_prop_numerica(string nume);
    Restrictie_Pacient<bool, float>* get_prop_bool_mas(string nume);
    Restrictie_Pacient<bool, bool>* get_prop_booleana(string nume);
    Date_om get_date();
    Fisa* get_fisa();
    int get_cate_naspa();
    bool operator==(const Pacient& p) const;
    friend istream& operator>>(istream& in, Pacient& p);
    friend ostream& operator<<(ostream& out, const Pacient& p);
    virtual ~Pacient(){}
};

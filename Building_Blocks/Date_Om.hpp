#pragma once
#include "../includuri.hpp"

class Date_om
{
    string nume, prenu, adresa;
    int ani;
public:
    Date_om(){}
    Date_om(string n, string p, string ad, int a): nume(n), prenu(p), adresa(ad), ani(a){}
    void set_nume(string nume);
    void set_prenume(string prenume);
    void set_adresa(string adresa);
    void set_ani(int ani);
    string get_nume();
    string get_prenume();
    string get_adresa();
    int get_ani();
    bool operator==(const Date_om& om) const;
    friend ostream& operator<< (ostream& out, const Date_om& om);
    friend istream& operator>> (istream& in, Date_om& om);
    virtual ~Date_om(){}
};
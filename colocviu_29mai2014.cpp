#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <functional>
#include <list>
#include <chrono>
#include <ctime> 
#define pb push_back
using namespace std;

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
    friend ostream& operator<< (ostream& out, const Date_om& om);
    friend istream& operator>> (istream& in, Date_om& om);
};
void Date_om::set_nume(string nume)
{
    this -> nume = nume;
}
void Date_om::set_prenume(string prenume)
{
    this -> prenu = prenume;
}
void Date_om::set_adresa(string ad)
{
    this -> adresa = ad;
}
void Date_om::set_ani(int a)
{
    this -> ani = a;
}
string Date_om::get_nume()
{
    return nume;
}
string Date_om::get_prenume()
{
    return prenu;
}
string Date_om::get_adresa()
{
    return adresa;
}
int Date_om::get_ani()
{
    return ani;
}
ostream& operator<<(ostream& out, const Date_om& om)
{
    out<<om.nume<<" "<<om.prenu<<"\nVarsta: "<<om.ani<<" ani\nLocuinta: "<<om.adresa;
    return out;
}
istream& operator>>(istream& in, Date_om& om)
{
    in>>om.nume>>om.prenu>>om.ani;
    in.get();
    getline(in, om.adresa);
    return in;
}
class Data
{
    int zi, luna, an;
    char sep;
public:
    Data(){}
    Data(int zi, int luna, int an, char sep): zi(zi), luna(luna), an(an), sep(sep){}
    void set_zi(int zi);
    void set_luna(int luna);
    void set_an(int an);
    void set_sep(char c);
    int get_zi();
    int get_luna();
    int get_an();
    char get_sep();
    int nrzile(int luna, int an);
    int nrzile();
    friend ostream& operator<< (ostream& out, const Data& d);
    friend istream& operator>> (istream& in, Data& d);
};
int Data::nrzile(int luna, int an)
{
    int Z[13]={31,31,28,31,30,31,30,31,31,30,31,30,31};
    if(luna!=2 || !(an%4==0 && an%100!=0 || an%400==0)) return Z[luna];
    else return 29;
}
int Data::nrzile()
{
    Data d = *this;
    int z=(d.an-1)*365+(d.an-1)/4-(d.an-1)/100+(d.an-1)/400;
    for(int i=1;i<d.luna;i++)
        z=z+nrzile(i,d.an);
    return z+d.zi;
}
void Data::set_zi(int zi)
{
    this -> zi = zi;
}
void Data::set_luna(int luna)
{
    this -> luna = luna;
}
void Data::set_an(int an)
{
    this -> an = an;
}
void Data::set_sep(char c)
{
    this -> sep = c;
}
int Data::get_zi()
{
    return zi;
}
int Data::get_luna()
{
    return luna;
}
int Data::get_an()
{
    return an;
}
char Data::get_sep()
{
    return sep;
}
ostream& operator<< (ostream& out, const Data& d)
{
    if ( d.zi < 10 )
        out<<0;
    out<<d.zi<<d.sep;
    if ( d.luna < 10 )
        out<<0;
    out<<d.luna<<d.sep<<d.an;
    return out;
}
istream& operator>> (istream& in, Data& d)
{
    in>>d.zi>>d.luna>>d.an;
    return in;
}
///nivelurile T de restrictie pentru proprietatea U
///in mare, T e o multime de numere pentru care se va verifica
///cu ajutorul unei functii reguli pentru proprietatea U
template<typename T, typename U> 
class Restrictie
{
    function<T(U)> restrictie;
    map<T, string> denumiri; ///gen 0 = optim, 1 = normal, 2 = crescut     (sau)
                             ///0 = nefumator, 1 = fumator
public:
    Restrictie(){}
    Restrictie(function<T(U)>& f, map<T, string>& denumiri):restrictie(f), denumiri(denumiri){}
    void set_restrictie(function<T(U)>& f);
    void set_denumiri(map<T, string>& m);
    map<T, string>& get_denumiri();
    function<T(U)>& get_restrictie();
    string evalueaza(U prop);
};
template<typename T, typename U> 
void Restrictie<T, U>::set_restrictie(function<T(U)>& f)
{
    this -> restrictie = f;
}
template<typename T, typename U> 
void Restrictie<T, U>::set_denumiri(map<T, string>& m)
{
    this -> denumiri = m;
}
template<typename T, typename U> 
map<T, string>& Restrictie<T, U>::get_denumiri()
{
    return denumiri;
}
template<typename T, typename U> 
function<T(U)>& Restrictie<T, U>::get_restrictie()
{
    return restrictie;
}
template<typename T, typename U> 
string Restrictie<T, U>::evalueaza(U prop)
{
    return denumiri[restrictie(prop)];
}

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
    Test_analiza(string s, string u, U i, Data& d, function<T(U)> &f, map<T, string>& m): substanta(s), unitate(u), indicator(i), d(d), restrictia(f, m){}
    Test_analiza(string s, string u, U i, int zi, int luna, int an, char sep, function<T(U)> &f, map<T, string>& m): substanta(s), unitate(u), indicator(i), d(zi, luna, an, sep), restrictia(f, m){}
    void set_substanta(string s);
    void set_indicator(U i);
    void set_data(Data& d);
    void set_data(int zi, int luna, int an, char sep);
    void set_unitate(string u);
    void set_restrictia(Restrictie<T, U>& r);
    void set_restrictia(function<T(U)>& f, map<T, string>& m);
    string get_substanta();
    string get_unitate();
    U get_indicator();
    Data& get_data();
    Restrictie<T, U>& get_restrictia();
    void afiseaza(ostream& out);
    void citeste(istream& in);
};
template<typename T, typename U>
void Test_analiza<T, U>::set_substanta(string s)
{
    this -> substanta = s;
}
template<typename T, typename U>
void Test_analiza<T, U>::set_indicator(U i)
{
    this -> indicator = i;
}
template<typename T, typename U>
void Test_analiza<T, U>::set_data(Data& d)
{
    this -> d = d;
}
template<typename T, typename U>
void Test_analiza<T, U>::set_data(int zi, int luna, int an, char sep)
{
    this -> d.set_zi(zi);
    this -> d.set_luna(luna);
    this -> d.set_an(an);
    this -> d.set_sep(sep);
}
template<typename T, typename U>
void Test_analiza<T, U>::set_unitate(string u)
{
    this -> unitate = u;
}
template<typename T, typename U>
string Test_analiza<T, U>::get_substanta()
{
    return substanta;
}
template<typename T, typename U>
string Test_analiza<T, U>::get_unitate()
{
    return unitate;
}
template<typename T, typename U>
U Test_analiza<T, U>::get_indicator()
{
    return indicator;
}
template<typename T, typename U>
Data& Test_analiza<T, U>::get_data()
{
    return d;
}
template<typename T, typename U>
void Test_analiza<T, U>::set_restrictia(Restrictie<T, U>& r)
{
    this -> restrictia = r;
}
template<typename T, typename U>
void Test_analiza<T, U>::set_restrictia(function<T(U)>&f, map<T, string>& m)
{
    this -> restrictia.set_denumiri(m);
    this -> restrictia.set_restrictie(f);
}
template<typename T, typename U>
Restrictie<T, U>& Test_analiza<T, U>::get_restrictia()
{
    return restrictia;
}
template<typename T, typename U>
void Test_analiza<T, U>::afiseaza(ostream& out)
{
    out<<substanta<<" ("<<d<<"): "<<indicator<<" "<<unitate;
}
template<typename T, typename U>
void Test_analiza<T, U>::citeste(istream& in)
{
    in>>this -> substanta>>this -> indicator>>this -> d;
}

























///de implementat de aici


class Substanta
{
    string nume, unitate;
    float cantitate, indice_intensitate, pret;
    Data expirare;

public:
    Substanta(){}
    Substanta(string n, string u, float c, float i, float p, Data d): nume(n), unitate(u), cantitate(c), indice_intensitate(i), pret(p), expirare(d){}
    void set_nume(string nume);
    void set_unitate(string unitate);
    void set_cantitate(float c);
    void set_expirare(Data d);
    void set_indice(float i);
    void set_pret(float p);
    float get_pret();
    float get_indice();
    Data get_expirare();
    float get_cantitate();
    string get_nume();
    string get_unitate();
    float calculeaza_intensitatea();
    friend istream& operator>> (istream& in, Substanta& s);
    friend ostream& operator<< (ostream& out, const Substanta& s);
};

float Substanta::calculeaza_intensitatea()
{
    time_t t;
    struct tm* ti;
    time(&t);
    ti = localtime(&t);
    string aux = asctime(ti);
    map<string, int> mluna = {{"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4}, {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8}, {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}};
    string nuj = "";
    nuj += aux[4];
    nuj += aux[5];
    nuj += aux[6];
    int anul = (aux[(aux.size()-4)]-'0')*1000 + (aux[(aux.size()-3)]-'0')*100 + (aux[(aux.size()-2)]-'0')*10 + aux[(aux.size()-1)]-'0';
    Data azi((aux[8]-'0')*10+(aux[9]-'0'), mluna[nuj], anul, '.');
    if ( expirare.nrzile() < azi.nrzile() )
        return 0;
    return (expirare.nrzile()-azi.nrzile())*indice_intensitate*cantitate;
}

class SubstantaIeftina: public Substanta
{
    float proc_impuritati;
public:
    SubstantaIeftina(){}
    SubstantaIeftina(Substanta& s, float p): Substanta(s), proc_impuritati(p){}
    SubstantaIeftina(string n, string u, float c, float i, float pr, Data d, float p): Substanta(n, u, c, i, pr, d), proc_impuritati(p){}
    void set_proc(float p);
    float get_proc();
    float get_pret(); ///0,75 * pretul normal
    float calculeaza_intensitatea();
};
float SubstantaIeftina::calculeaza_intensitatea()
{
    return Substanta::calculeaza_intensitatea() * (1 - proc_impuritati);
}

class Substanta_onsale : public Substanta
{
    float reducere;
public:
    Substanta_onsale(){}
    Substanta_onsale(Substanta& s, float r): Substanta(s), reducere(r){}
    Substanta_onsale(string n, string u, float c, float i, float pr, Data d, float r): Substanta(n, u, c, i, pr, d), reducere(r){}
    float get_pret();
    void set_reducere();
    float get_reducere();
};

class SubstantaIeftina_onsale : public SubstantaIeftina, public Substanta_onsale
{
public:
    SubstantaIeftina_onsale(){}
    SubstantaIeftina_onsale(SubstantaIeftina& s1, Substanta_onsale& s2):SubstantaIeftina(s1), Substanta_onsale(s2){}
    SubstantaIeftina_onsale(string n, string u, float c, float i, float pr, Data d, float r, float p):SubstantaIeftina(n, u, c, i, pr, d, p), Substanta_onsale(n, u, c, i, p, d, r){}
    float get_pret();
};

class Medicament
{
    vector<Substanta*> substante;
    string nume;
public:
    Medicament(){}
    Medicament(string nume, vector<Substanta*>& v): nume(nume), substante(v){}
    void set_nume(string nume);
    void adauga_substanta(Substanta s);
    void sterge_substanta(string nume);
    void sterge_substanta(int i);
    float get_intensitate_totala();
    float get_pret();
    string get_nume();
    Substanta* get_substanta(int i);
    Substanta* get_substanta(string nume);
};



class Fisa
{
    vector<Medicament*> tratament_activ;
    vector< Test_analiza<int, float>* > analize_numerice; ///care verifica o valoare si il pune intr-un bucket
    vector< Test_analiza<bool, bool>* > analize_booleene; ///care verifica daca este sau nu cumva
public:
    void adauga_medicament(Medicament* m);
    void adauga_numeric(Test_analiza<int, float>* t);
    void adauga_boolean(Test_analiza<bool, bool>* t);
    void sterge_medicament(Medicament* m);
    void sterge_medicament(int i);
    void sterge_numeric(Test_analiza<int, float>* t);
    void sterge_numeric(int i);
    void sterge_boolean(Test_analiza<bool, bool>* t);
    void sterge_boolean(int i);
    friend ostream& operator<< (ostream& out, const Fisa& f);
    friend istream& operator>> (istream& in, Fisa& f);
};

class Fisa_Copil : public Fisa
{
    pair<Date_om*, Date_om*> parinti;

public:  
};

class Pacient
{
    Date_om date;
    Fisa* f;
public:

};

class Program
{

};

int cole(float col)
{
    if ( col <= 200 )
        return 0;
    if ( col <= 239 )
        return 1;
    return 2;
}
bool efum(bool x)
{
    return x;
}
///Colesterol 250 25 5 2024
int main()
{
    map<int, string> m = {{0, "Optim"}, {1, "Normal"}, {2, "Crescut"}};
    map<bool, string> mp = {{false, "Nefumator"}, {true, "Fumator"}};
    function<int(float)> aux = cole;
    function<bool(bool)> plm = efum;
    Test_analiza<int, float> colesterolul("Colesterol", "mg/dl", 250, 25, 5, 2024, '.', aux, m);
    Test_analiza<bool, bool> fumator("Fumatul", "mg/dl", true, 25, 5, 2024, '.', plm, mp);
    
    return 0;
}
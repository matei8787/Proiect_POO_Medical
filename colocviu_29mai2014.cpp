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
    bool operator==(const Date_om& om) const;
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
bool Date_om::operator==(const Date_om& om) const
{
    return (this -> nume == om.nume && this -> prenu == om.prenu && this -> ani == om.ani);
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
    char sep='.';
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
    bool operator==(const Data& d) const;
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
bool Data::operator==(const Data& d) const
{
    return (this -> zi == d.zi && this -> luna == d.luna && this -> an == d.an);
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
    string evalueaza();
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
string Test_analiza<T, U>::evalueaza()
{
    return this -> restrictia.evalueaza(this -> indicator);
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
    void afiseaza(ostream& out);
    void citeste(istream& in);
};

void Substanta::set_nume(string nume)
{
    this -> nume = nume;
}
void Substanta::set_unitate(string unitate)
{
    this -> unitate = unitate;
}
void Substanta::set_cantitate(float c)
{
    this -> cantitate = c;
}
void Substanta::set_expirare(Data d)
{
    this -> expirare = d;
}
void Substanta::set_indice(float idx)
{
    this -> indice_intensitate = idx;
}
void Substanta::set_pret(float p)
{
    this -> pret = p;
}
string Substanta::get_nume()
{
    return this -> nume;
}
string Substanta::get_unitate()
{
    return this -> unitate;
}
float Substanta::get_cantitate()
{
    return this -> cantitate;
}
Data Substanta::get_expirare()
{
    return this -> expirare;
}
float Substanta::get_indice()
{
    return this -> indice_intensitate;
}
float Substanta::get_pret()
{
    return this -> pret;
}
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
void Substanta::afiseaza(ostream& out)
{
    out<<nume<<" "<<cantitate<<unitate<<"\nPret: "<<this -> get_pret()<<" RON\nData expirare: "<<expirare;
}
void Substanta::citeste(istream& in)
{
    in>>this -> nume>>
    this -> cantitate>>
    this -> unitate>>
    this -> indice_intensitate>>
    this -> pret>>
    this -> expirare;
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
    float get_pret();
    float calculeaza_intensitatea();
    void citeste(istream& in);
};
void SubstantaIeftina::set_proc(float p)
{
    this -> proc_impuritati = p;
}
float SubstantaIeftina::get_proc()
{
    return this -> proc_impuritati;
}
float SubstantaIeftina::get_pret()
{
    return Substanta::get_pret()*0.75;
}
float SubstantaIeftina::calculeaza_intensitatea()
{
    return Substanta::calculeaza_intensitatea() * (1 - proc_impuritati);
}
void SubstantaIeftina::citeste(istream& in)
{
    Substanta::citeste(in);
    in>>proc_impuritati;
}

class Substanta_onsale : public Substanta
{
    float reducere;
public:
    Substanta_onsale(){}
    Substanta_onsale(Substanta& s, float r): Substanta(s), reducere(r){}
    Substanta_onsale(string n, string u, float c, float i, float pr, Data d, float r): Substanta(n, u, c, i, pr, d), reducere(r){}
    float get_pret();
    void set_reducere(float r);
    float get_reducere();
    void citeste(istream& in);
};
float Substanta_onsale::get_pret()
{
    return Substanta::get_pret()*reducere;
}
void Substanta_onsale::set_reducere(float r)
{
    this -> reducere = r;
}
float Substanta_onsale::get_reducere()
{
    return this -> reducere;
}
void Substanta_onsale::citeste(istream& in)
{
    Substanta::citeste(in);
    in>>reducere;
}


class SubstantaIeftina_onsale : virtual public SubstantaIeftina, virtual public Substanta_onsale
{
public:
    SubstantaIeftina_onsale(){}
    SubstantaIeftina_onsale(SubstantaIeftina& s1, Substanta_onsale& s2):SubstantaIeftina(s1), Substanta_onsale(s2){}
    SubstantaIeftina_onsale(string n, string u, float c, float i, float pr, Data d, float r, float p):SubstantaIeftina(n, u, c, i, pr, d, p), Substanta_onsale(n, u, c, i, p, d, r){}
    float get_pret();
    void citeste(istream& in);
};
float SubstantaIeftina_onsale::get_pret()
{
    return Substanta_onsale::get_pret()*0.75;
}
void SubstantaIeftina_onsale::citeste(istream& in)
{
    SubstantaIeftina::citeste(in);
    int aux;
    in>>aux;
    Substanta_onsale::set_reducere(aux);
}

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
    void afiseaza(ostream& out);
    void citeste(istream& in);
};
void Medicament::set_nume(string nume)
{
    this -> nume = nume;
}
void Medicament::adauga_substanta(Substanta s)
{
    substante.push_back(&s);
}
void Medicament::sterge_substanta(int i)
{
    substante.erase(substante.begin() + i);
}
void Medicament::sterge_substanta(string nume)
{
    for ( int i = 0 ; i < substante.size() ; i++ )
    {
        if ( substante[i] -> get_nume() == nume )
        {
            substante.erase(substante.begin() + i);
            return;
        }
    }
}
string Medicament::get_nume()
{
    return this -> nume;
}
float Medicament::get_pret()
{
    float ans = 0;
    for ( Substanta* s : substante )
    {
        ans += s -> get_pret();
    }
    return ans;
}
float Medicament::get_intensitate_totala()
{
    float ans = 0;
    for( Substanta* s : substante )
    {
        ans += s -> calculeaza_intensitatea();
    }
    return ans;
}
Substanta* Medicament::get_substanta(int i)
{
    return substante[i];
}
Substanta* Medicament::get_substanta(string nume)
{
    for ( Substanta* s : substante )
    {
        if ( s -> get_nume() == nume )
            return s;
    }
    return nullptr;
}
void Medicament::afiseaza(ostream& out)
{
    out<<this -> nume<<":\n";
    for ( Substanta* s : substante )
    {
        s -> afiseaza(out);
        out<<'\n';
    }
}
void Medicament::citeste(istream& in)
{
    int nr_substante;
    in>>nume;
    in>>nr_substante;
    for ( int i = 1 ; i <= nr_substante ; i++ )
    {
        int tip; ///0=normal, 1=ieftin, 2=onsale, 3=ambele
        in>>tip;
        Substanta* s = new Substanta();
        SubstantaIeftina sui;
        Substanta_onsale sos, *aux = new Substanta_onsale();
        SubstantaIeftina_onsale sios;
        if ( tip == 1 )
        {
            sui.citeste(in);
            s = &sui;
        }
        else if ( tip == 2 )
        {
            sos.citeste(in);
            s = &sos;
        }
        else if ( tip == 3 )
        {
            sios.citeste(in);
            aux = &sios; ///duamne ajuta
            s = aux;
        }
        else
        {
            s -> citeste(in);
        }
        substante.push_back(new Substanta(*s));
    }
}
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
};
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
        if ( analize_numerice[i]->get_substanta() == nume )
        {
            analize_numerice.erase(analize_numerice.begin() + i);
            return;
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
        if ( analize_booleene[i]->get_substanta() == nume )
        {
            analize_booleene.erase(analize_booleene.begin() + i);
            return;
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
        if ( t -> get_substanta() == nume )
            return t;
    }
    return nullptr;
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
        aux.citeste(in);
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
        m -> afiseaza(out);
    }
}

template<typename T, typename U>
class Restrictie_Pacient : public Restrictie<T, U>
{
    string nume;
    U evaluare;
public:
    Restrictie_Pacient(){}
    Restrictie_Pacient(Restrictie<T, U>& r, string nume, U prop): Restrictie<T, U>(r), nume(nume), evaluare(prop){}
    Restrictie_Pacient(function<T(U)>& f, map<T, string>& m, string nume, U prop): Restrictie<T, U>(f, m), nume(nume), evaluare(prop){}
    void set_nume(string nume);
    void set_eval(U eval);
    U get_eval();
    string get_nume();
    string evalueaza();
    void citeste(istream& in);
    template<typename V, typename W>
    bool operator==(const Restrictie_Pacient<V, W>& r) const
    {
        return this -> nume == r.nume;
    }
};
template<typename T, typename U>
void Restrictie_Pacient<T, U>::set_nume(string nume)
{
    this -> nume = nume;
}
template<typename T, typename U>
void Restrictie_Pacient<T, U>::set_eval(U eval)
{
    this -> evaluare = eval;
}
template<typename T, typename U>
U Restrictie_Pacient<T, U>::get_eval()
{
    return this -> evaluare;
}
template<typename T, typename U>
string Restrictie_Pacient<T, U>::get_nume()
{
    return this -> nume;
}
template<typename T, typename U>
string Restrictie_Pacient<T, U>::evalueaza()
{
    return Restrictie<T, U>::evalueaza(this -> evaluare);
}
template<typename T, typename U>
void Restrictie_Pacient<T, U>::citeste(istream& in)
{
    in>>this -> nume>>this -> evaluare;
}
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
    Pacient(Date_om d, Fisa* f, vector< Restrictie_Pacient<int, float>* > & pn, vector< Restrictie_Pacient<bool, float>* >& pbm, vector< Restrictie_Pacient<bool, bool>* >& pb): date(d), f(f), prop_numerice(pn), prop_booleene_masurabile(pbm), prop_booleene(pb){}
    Pacient(string n, string p, string ad, int a, Fisa* f, vector< Restrictie_Pacient<int, float>* > & pn, vector< Restrictie_Pacient<bool, float>* >& pbm, vector< Restrictie_Pacient<bool, bool>* >& pb): date(n, p, ad, a), f(f), prop_numerice(pn), prop_booleene_masurabile(pbm), prop_booleene(pb){}
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
    bool operator==(const Pacient& p) const;
    friend istream& operator>>(istream& in, Pacient& p);
    friend ostream& operator<<(ostream& out, const Pacient& p);
};
void Pacient::set_date(Date_om d)
{
    this -> date = d;
}
void Pacient::set_fisa(Fisa* f)
{
    this -> f = f;
}
void Pacient::adauga_prop_numerica(Restrictie_Pacient<int, float>* prop)
{
    this -> prop_numerice.push_back(prop);
}
void Pacient::adauga_prop_booleana(Restrictie_Pacient<bool, bool>* prop)
{
    this -> prop_booleene.push_back(prop);
}
void Pacient::adauga_prop_bool_mas(Restrictie_Pacient<bool, float>* prop)
{
    this -> prop_booleene_masurabile.push_back(prop);
}
void Pacient::sterge_prop_numerica(Restrictie_Pacient<int, float>* prop)
{
    for ( int i = 0 ; i < this -> prop_numerice.size() ; i++ )
    {
        if ( prop == this -> prop_numerice[i] )
        {
            this -> prop_numerice.erase(this -> prop_numerice.begin() + i);
            return;
        }
    }
}
void Pacient::sterge_prop_numerica(string nume)
{
    for ( int i = 0 ; i < this -> prop_numerice.size() ; i++ )
    {
        if ( nume == this -> prop_numerice[i]->get_nume() )
        {
            this -> prop_numerice.erase(this -> prop_numerice.begin() + i);
            return;
        }
    }
}
void Pacient::sterge_prop_numerica(int i)
{
    this -> prop_numerice.erase(this -> prop_numerice.begin() + i);
}
void Pacient::sterge_prop_booleana(Restrictie_Pacient<bool, bool>* prop)
{
    for ( int i = 0 ; i < this -> prop_booleene.size() ; i++ )
    {
        if ( prop == this -> prop_booleene[i] )
        {
            this -> prop_booleene.erase(this -> prop_booleene.begin() + i);
            return;
        }
    }
}
void Pacient::sterge_prop_booleana(string nume)
{
    for ( int i = 0 ; i < this -> prop_booleene.size() ; i++ )
    {
        if ( nume == this -> prop_booleene[i]->get_nume() )
        {
            this -> prop_booleene.erase(this -> prop_booleene.begin() + i);
            return;
        }
    }
}
void Pacient::sterge_prop_booleana(int i)
{
    this -> prop_booleene.erase(this -> prop_booleene.begin() + i);
}
void Pacient::sterge_prop_bool_mas(Restrictie_Pacient<bool, float>* prop)
{
    for ( int i = 0 ; i < this -> prop_booleene_masurabile.size() ; i++ )
    {
        if ( prop == this -> prop_booleene_masurabile[i] )
        {
            this -> prop_booleene_masurabile.erase(this -> prop_booleene_masurabile.begin() + i);
            return;
        }
    }
}
void Pacient::sterge_prop_bool_mas(string nume)
{
    for ( int i = 0 ; i < this -> prop_booleene_masurabile.size() ; i++ )
    {
        if ( nume == this -> prop_booleene_masurabile[i]->get_nume() )
        {
            this -> prop_booleene_masurabile.erase(this -> prop_booleene_masurabile.begin() + i);
            return;
        }
    }
}
void Pacient::sterge_prop_bool_mas(int i)
{
    this -> prop_booleene_masurabile.erase(this -> prop_booleene_masurabile.begin() + i);
}
vector<Restrictie_Pacient<int, float>*>& Pacient::get_prop_numerice()
{
    return this -> prop_numerice;
}
vector<Restrictie_Pacient<bool, float>*>& Pacient::get_prop_bool_mas()
{
    return this -> prop_booleene_masurabile;
}
vector<Restrictie_Pacient<bool, bool>*>& Pacient::get_prop_booleene()
{
    return this -> prop_booleene;
}
Restrictie_Pacient<int, float>* Pacient::get_prop_numerica(string nume)
{
    for ( int i = 0 ; i < this -> prop_numerice.size() ; i++ )
    {
        if ( nume == this -> prop_numerice[i]->get_nume() )
        {
            return this -> prop_numerice[i];
        }
    }
    return nullptr;
}
Restrictie_Pacient<bool, float>* Pacient::get_prop_bool_mas(string nume)
{
    for ( int i = 0 ; i < this -> prop_booleene_masurabile.size() ; i++ )
    {
        if ( nume == this -> prop_booleene_masurabile[i]->get_nume() )
        {
            return this -> prop_booleene_masurabile[i];
        }
    }
    return nullptr;
}
Restrictie_Pacient<bool, bool>* Pacient::get_prop_booleana(string nume)
{
    for ( int i = 0 ; i < this -> prop_booleene.size() ; i++ )
    {
        if ( nume == this -> prop_booleene[i]->get_nume() )
        {
            return this -> prop_booleene[i];
        }
    }
    return nullptr;
}
Date_om Pacient::get_date()
{
    return this -> date;
}
Fisa* Pacient::get_fisa()
{
    return this -> f;
}
bool Pacient::operator==(const Pacient& p) const
{
    return (this -> date == p.date  && this -> f == p.f);
}
istream& operator>>(istream& in, Pacient& p)
{
    in>>p.date;
    p.f->citeste_analize_numerice(in);
    p.f->citeste_analize_booleene(in);
    p.f->citeste_tratament_activ(in);
    int n;
    in>>n; ///nr_prop_numerice
    for ( int i = 1 ; i <= n ; i++ )
    {
        Restrictie_Pacient<int, float>* r = new Restrictie_Pacient<int, float>();
        r -> citeste(in);
        p.adauga_prop_numerica(r);
    }
    in>>n; ///prop_bool_mas
    for ( int i = 1 ; i <= n ; i++ )
    {
        Restrictie_Pacient<bool, float>* r = new Restrictie_Pacient<bool, float>();
        r -> citeste(in);
        p.adauga_prop_bool_mas(r);
    }
    in>>n;
    for ( int i = 1 ; i <= n ; i++ )
    {
        Restrictie_Pacient<bool, bool>* r = new Restrictie_Pacient<bool, bool>();
        r -> citeste(in);
        p.adauga_prop_booleana(r);
    }
    return in;
}
ostream& operator<<(ostream& out, const Pacient& p)
{
    out<<p.date<<'\n';
    for (Restrictie_Pacient<int, float>* r : p.prop_numerice)
    {
        out<<r->get_nume()<<" - "<<r->evalueaza()<<'\n';
    }
    for (Restrictie_Pacient<bool, float>* r : p.prop_booleene_masurabile)
    {
        out<<r->get_nume()<<" - "<<r->evalueaza()<<'\n';
    }
    for (Restrictie_Pacient<bool, bool>* r : p.prop_booleene)
    {
        out<<r->get_nume()<<" - "<<r->evalueaza()<<'\n';
    }
    for ( Test_analiza<int, float>* t : p.f -> get_analize_numerice() )
    {
        t->afiseaza(out);
    }
    for ( Test_analiza<bool, float>* t: p.f -> get_analize_booleene() )
    {
        t->afiseaza(out);
    }
    return out;
}
class Adult : public Pacient
{
    vector<Pacient*> copii;
public:
    Adult(){}
    Adult(Pacient& eu, vector<Pacient*>& copiii): Pacient(eu), copii(copiii){}
    Adult(Pacient& eu, Pacient* copil): Pacient(eu){ copii.push_back(copil); }
    void adauga_copil(Pacient* copil);
    void sterge_copil(Pacient* copil);
    void sterge_copil(int i);
    void sterge_copil(string prenume);
    bool operator==(const Adult& p) const;
    friend istream& operator>>(istream& in, Adult& p);
    friend ostream& operator<<(ostream& out, const Adult& p);
};
void Adult::adauga_copil(Pacient* p)
{
    copii.push_back(p);
}
void Adult::sterge_copil(Pacient* p)
{
    for ( int i = 0 ; i < copii.size() ; i++ )
    {
        if ( copii[i] == p )
        {
            copii.erase(copii.begin() + i);
            return;
        }
    }
}
void Adult::sterge_copil(string prenume)
{
    for ( int i = 0 ; i < copii.size() ; i++ )
    {
        if ( copii[i]->get_date().get_prenume() == prenume )
        {
            copii.erase(copii.begin() + i);
            return;
        }
    }
}
void Adult::sterge_copil(int i)
{
    copii.erase(copii.begin() + i);
}
bool Adult::operator==(const Adult& a) const
{
    return (this->date == a.date);
}
istream& operator>>(istream& in, Adult& a)
{
    Pacient aux;
    in>>aux;
    int n; /// nr_copii
    in>>n;
    vector<Pacient*> v;
    for ( int i = 1 ; i <= n ; i++ )
    {
        Pacient* p = new Pacient();
        in>>(*p);
        v.push_back(p);
    }
    a = Adult(aux, v);
    return in;
}
ostream& operator<<(ostream& out, const Adult& a)
{
    Pacient aux = a;
    out<<aux<<'\n';
    out<<"Cu "<<a.copii.size()<<" copii\n";
    for ( int i = 0 ; i < a.copii.size() ; i++ )
    {
        out<<a.copii[i]<<'\n';
    }
    return out;
}

class Adult_peste40 : public Adult
{

public:

};

class Copil : public Pacient
{
    pair<Adult*, Adult*> parinti;
public:

};

template<typename T>
class Afisare
{
    string nume;
    function<T(Pacient*)> criteriu;
public:
    Afisare(){}
    Afisare(string nume, function<T(Pacient*)>& f): nume(nume), criteriu(f){}
    virtual void creeaza(function<T(Pacient*)>& f) = 0;
    virtual void afiseaza() = 0;
    void set_nume(string nume);
    string get_nume();
};

class Afisare_Simpla : public Afisare<bool>
{
    vector<Pacient*> pacienti;
public:
    Afisare_Simpla(){}
    Afisare_Simpla(string nume, function<bool(Pacient*)>& f): Afisare<bool>(nume, f){ creeaza(f); }
    void creeaza(function<bool(Pacient*)>& f) override;
    void afiseaza() override;
};

template<typename T>
class Afisare_Selectiva : public Afisare<T>
{
    map<T, Pacient*> pacienti;
public:
    Afisare_Selectiva(){}
    Afisare_Selectiva(string nume, function<T(Pacient*)>& f): Afisare<T>(nume, f){ creeaza(f); }
    void creeaza(function<T(Pacient*)>& f) override;
    void afiseaza(T selectare);
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
bool efum(float x)
{
    if ( x > 0 )
        return true;
    return false;
}
///Colesterol 250 25 5 2024
int main()
{
    map<int, string> m = {{0, "Optim"}, {1, "Normal"}, {2, "Crescut"}};
    map<bool, string> mp = {{false, "Nefumator"}, {true, "Fumator"}};
    function<int(float)> aux = cole;
    function<bool(float)> plm = efum;
    Test_analiza<int, float> colesterolul("Colesterol", "mg/dl", 250, 25, 5, 2024, '.', aux, m);
    Test_analiza<bool, float> fumator("Fumatul", "mg/dl", 1, 25, 5, 2024, '.', plm, mp);
    Medicament s;
    s.citeste(cin);
    s.afiseaza(cout);
    return 0;
}

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
#include <cstdarg>
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
    virtual ~Date_om(){}
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
    virtual ~Data(){}
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
template<typename T, typename U>
void Restrictie<T, U>::set_restrictie(function<T(U)>& f)
{
    this -> restrictie = f;
}
template<typename T, typename U>
bool Restrictie<T, U>::e_normal(U prop)
{
    T eval = restrictie(prop);
    for ( T e : evaluari_normale )
    {
        if ( e == eval )
            return true;
    }
    return false;
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
    T retur = restrictie(prop);
    return denumiri[retur];
}
template<typename T, typename U>
void Restrictie<T,U>::set_normale(vector<T>& v)
{
    this -> evaluari_normale = v;
}
template<typename T, typename U>
void Restrictie<T, U>::adauga_normal(T normal)
{
    this -> evaluari_normale.push_back(normal);
}
template<typename T, typename U>
vector<T>& Restrictie<T, U>::get_normale()
{
    return this -> evaluari_normale;
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
    Test_analiza(string s, string u, U i, Data& d, function<T(U)> &f, map<T, string>& m, vector<T>& evals): substanta(s), unitate(u), indicator(i), d(d), restrictia(f, m, evals){}
    Test_analiza(string s, string u, U i, int zi, int luna, int an, char sep, function<T(U)> &f, map<T, string>& m, vector<T>& evals): substanta(s), unitate(u), indicator(i), d(zi, luna, an, sep), restrictia(f, m, evals){}
    void set_substanta(string s);
    void set_indicator(U i);
    void set_data(Data& d);
    void set_data(int zi, int luna, int an, char sep);
    void set_unitate(string u);
    void set_restrictia(Restrictie<T, U>& r);
    string get_substanta();
    string get_unitate();
    U get_indicator();
    Data& get_data();
    Restrictie<T, U>& get_restrictia();
    string evalueaza();
    void afiseaza(ostream& out);
    void citeste(istream& in);
    virtual ~Test_analiza(){}
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
    in>>this -> substanta>>this -> indicator>>this -> d>>this -> unitate;

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
    virtual ~Substanta(){}
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
    this -> unitate>>
    this -> cantitate>>
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
    virtual ~SubstantaIeftina(){}
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
    virtual ~Substanta_onsale(){}
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
    virtual ~SubstantaIeftina_onsale(){}
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
    friend ostream& operator<<(ostream& out, const Medicament& m);
    friend istream& operator>>(istream& in, Medicament& m);
    virtual ~Medicament(){}
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
ostream& operator<<(ostream& out, const Medicament& m)
{
    out<<m.nume<<":\n";
    for ( Substanta* s : m.substante )
    {
        s -> afiseaza(out);
        out<<'\n';
    }
    return out;
}
istream& operator>>(istream& in, Medicament& m)
{
    int nr_substante;
    in>>m.nume;
    in>>nr_substante;
    for ( int i = 1 ; i <= nr_substante ; i++ )
    {
        int tip; ///0=normal, 1=ieftin, 2=onsale, 3=ambele
        in>>tip;
        in.get();
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
        m.substante.push_back(new Substanta(*s));
    }
    return in;
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
    virtual ~Fisa(){}
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

template<typename T, typename U>
class Restrictie_Pacient : public Restrictie<T, U>
{
    string nume;
    U evaluare;
public:
    Restrictie_Pacient(){}
    Restrictie_Pacient(Restrictie<T, U>& r, string nume, U prop): Restrictie<T, U>(r), nume(nume), evaluare(prop){}
    Restrictie_Pacient(function<T(U)>& f, map<T, string>& m, vector<T>& eval, string nume, U prop): Restrictie<T, U>(f, m, eval), nume(nume), evaluare(prop){}
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
    virtual ~Restrictie_Pacient(){}
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
int Pacient::get_cate_naspa()
{
    int cate_naspa=0;
    for ( Restrictie_Pacient<int, float>* r : prop_numerice )
    {
        if ( !(r->e_normal(r->get_eval())) )
            cate_naspa++;
    }
    for ( Restrictie_Pacient<bool, float>* r : prop_booleene_masurabile )
    {
        if ( !(r->e_normal(r->get_eval())))
            cate_naspa++;
    }
    for ( Restrictie_Pacient<bool, bool>* r : prop_booleene )
    {
        if ( !(r->e_normal(r->get_eval())))
            cate_naspa++;
    }
    for ( Test_analiza<int, float>* t : f -> get_analize_numerice() )
    {
        if ( !(t->get_restrictia().e_normal(t->get_indicator())) )
        {
            cate_naspa++;
        }
    }
    for ( Test_analiza<bool, float>* t : f -> get_analize_booleene() )
    {
        if ( !(t->get_restrictia().e_normal(t->get_indicator())))
        {
            cate_naspa++;
        }
    }
    return cate_naspa;
}
Pacient::Pacient(string n, string p, string ad, int a, Fisa* f, vector< Restrictie_Pacient<int, float>* > & pn, vector< Restrictie_Pacient<bool, float>* >& pbm, vector< Restrictie_Pacient<bool, bool>* >& pb): date(n, p, ad, a), f(f), prop_numerice(pn), prop_booleene_masurabile(pbm), prop_booleene(pb){}

Pacient::Pacient(Date_om d, Fisa* f, vector< Restrictie_Pacient<int, float>* > & pn, vector< Restrictie_Pacient<bool, float>* >& pbm, vector< Restrictie_Pacient<bool, bool>* >& pb): date(d), f(f), prop_numerice(pn), prop_booleene_masurabile(pbm), prop_booleene(pb)
{
}
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
    if ( p.f == NULL )
        p.f = new Fisa();
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
        out<<'\n';
    }
    for ( Test_analiza<bool, float>* t: p.f -> get_analize_booleene() )
    {
        t->afiseaza(out);
        out<<'\n';
    }
    return out;
}
class Adult : public Pacient
{
    vector<Pacient*> copii;
public:
    Adult(){}
    Adult(Pacient& eu, vector<Pacient*>& copiii): Pacient(eu), copii(copiii){}
    Adult(Pacient& eu, Pacient* copil);
    void adauga_copil(Pacient* copil);
    void sterge_copil(Pacient* copil);
    void sterge_copil(int i);
    void sterge_copil(string prenume);
    bool operator==(const Adult& p) const;
    friend istream& operator>>(istream& in, Adult& p);
    friend ostream& operator<<(ostream& out, const Adult& p);
    virtual ~Adult(){}
};
Adult::Adult(Pacient& eu, Pacient* copil): Pacient(eu)
{
    copii.push_back(copil);
}
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
    const Pacient* aux = &a;
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
    Adult_peste40(){}
    Adult_peste40(Adult& a, bool fumator, float sedentarism);
    virtual ~Adult_peste40(){}
};
bool fummmm(bool x)
{
    return x;
}
int sedentarul(float nr)
{
    if ( (float)(nr - ((int)nr)) >= 0.5 )
            return (int)nr + 1;
        return (int)nr;
}
Adult_peste40::Adult_peste40(Adult& a, bool fumator, float sedentarism): Adult(a)
{
    function<bool(bool)> ffum = fummmm;
    map<bool, string> mpfum = {{false, "Nefumator"}, {true, "Fumator"}};
    function<int(float)> fsed = sedentarul;
    map<int, string> mpsed = {{0, "Scazut"}, {1, "Mediu"}, {2, "Ridicat"}};
    vector<bool> normal_fum = {false};
    vector<int> normal_sed = {0, 1};
    Restrictie<bool, bool> rfum(ffum, mpfum, normal_fum);
    Restrictie<int, float> rsed(fsed, mpsed, normal_sed);
    Restrictie_Pacient<bool, bool>* fumatul = new Restrictie_Pacient<bool, bool>(rfum, "E Fumator", fumator);
    Restrictie_Pacient<int, float>* sedentar = new Restrictie_Pacient<int, float>(rsed, "Nivel Sedentar", sedentarism);
    this -> adauga_prop_numerica(sedentar);
    this -> adauga_prop_booleana(fumatul);
}

class Copil : public Pacient
{
    pair<Adult*, Adult*> parinti;
public:
    Copil(){}
    Copil(Pacient& eu, Adult* a1, Adult* a2): Pacient(eu), parinti(a1, a2){}
    int get_cate_naspa();
    pair<Adult*, Adult*>& get_parinti();
};
int Copil::get_cate_naspa()
{
    int ans = Pacient::get_cate_naspa();
    Adult* a = this -> parinti.first, *b = this -> parinti.second;
    Restrictie_Pacient<int, float>* risc_a1 = a -> get_prop_numerica("Risc Cardiovascular"), *risc_a2 = b -> get_prop_numerica("Risc Cardiovascular");
    if ( !(risc_a1 -> e_normal(risc_a1 -> get_eval())) || !(risc_a2 -> e_normal(risc_a2 -> get_eval())))
        return ans + 1;
    return ans;
}

pair<Adult*, Adult*>& Copil::get_parinti()
{
    return this -> parinti;
}







































template<typename T, typename U>
class Afisare_Abstracta
{
    string nume;
    function<T(U*)> crt;
    map< T, vector<U*> > afisati;
    void creeaza(vector<U*>& total);
public:
    Afisare_Abstracta(){}
    Afisare_Abstracta(string n, function<T(U*)>& f, vector<U*>& total): nume(n), crt(f) { creeaza(total); }
    string get_nume();
    void set_nume(string n);
    void afisare_simplu(ostream& out, T selectarea);
    void afisare_specific(ostream& out, T selectarea, function<int(U*)> &care, vector<int>& ordine, map<int, string>& denumiri);
};
template<typename T, typename U>
void Afisare_Abstracta<T, U>::set_nume(string n)
{
    this -> nume = n;
}
template<typename T, typename U>
string Afisare_Abstracta<T, U>::get_nume()
{
    return this -> nume;
}
template<typename T, typename U>
void Afisare_Abstracta<T, U>::creeaza(vector<U*>& total)
{
    for ( U* chestie : total )
    {
        T bucket = crt(chestie);
        if ( afisati.find(bucket) == afisati.end() )
        {
            afisati.insert(make_pair(bucket, *(new vector<U*>({chestie}))));
        }
        else
        {
            afisati[bucket].push_back(chestie);
        }
    }
}
template<typename T, typename U>
void Afisare_Abstracta<T, U>::afisare_simplu(ostream& out, T select)
{
    for ( U* chestie : afisati[select] )
    {
        out<<(*chestie)<<'\n';
    }
}
template<typename T, typename U>
void Afisare_Abstracta<T, U>::afisare_specific(ostream&out, T select, function<int(U*)>& f, vector<int>& ord, map<int, string>& den)
{
    int j = 0;
    while ( j < ord.size() )
    {
        out<<den[ord[j]]<<'\n';
        for ( U* chestie : afisati[select] )
        {
            int aux = f(chestie);
            if ( aux == ord[j] )
            {
                out<<(*chestie)<<'\n';
            }
        }
        j++;
    }
}
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
class Baza_De_Date
{
    vector<Pacient*> pacienti_totali;
    vector<Medicament*> medicamente;
    vector<Afisare_Abstracta<bool, Pacient>*> afisari_simple; ///toti pacientii care ...
    vector<Afisare_Abstracta<string, Pacient>*> afisari_selective; ///toti pacientii care fac parte din familia x
    vector<Afisare_Abstracta<bool, Medicament>* >afisari_simple_medicamente;
    vector<Afisare_Abstracta<string, Medicament>* >afisari_selective_medicamente;
    
public:
    Baza_De_Date(){}
    Baza_De_Date(vector<Pacient*> pacienti, vector<Medicament*> medicamente): pacienti_totali(pacienti), medicamente(medicamente){}
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
    vector<Medicament*>& get_medicamente();
    vector<Afisare_Abstracta<bool, Pacient>*>& get_afp_simplu();
    Afisare_Abstracta<bool, Pacient>* get_afp_simplu(string nume);
    vector<Afisare_Abstracta<string, Pacient>*>& get_afp_select();
    Afisare_Abstracta<string, Pacient>* get_afp_select(string nume);
    vector<Afisare_Abstracta<bool, Medicament>*>& get_afm_simplu();
    Afisare_Abstracta<bool, Medicament>* get_afm_simplu(string nume);
    vector<Afisare_Abstracta<string, Medicament>*>& get_afm_select();
    Afisare_Abstracta<string, Medicament>* get_afm_select(string nume);
};
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
bool f_tensiune_buna(float t)
{
    if ( t > 139 )
        return false;
    return true;
}
int cole(float col)
{
    if ( col <= 200 )
        return 0;
    if ( col <= 239 )
        return 1;
    return 2;
}
bool protc_optim(float p)
{
    if ( p <= 0.60 )
        return true;
    return false;
}
template<typename T, typename ...Types>
T* creeaza(Types ...args_constructor)
{
    T* ans = new T(args_constructor...);
    return ans;

}
Data* da_data_random()
{
    int zi = (rand() % 28) + 1;
    int luna = (rand() % 12) + 1;
    int an = 2000 + (rand() % 25);
    return creeaza<Data>(zi, luna, an, '/');
}

string da_nume_random(int nrlit)
{
    string ans = "";
    for ( int i = 1 ; i <= nrlit ; i++ )
    {
        ans += ('a' + (rand()%('z'-'a'+1)));
    }
    return ans;
}

void baga_un_medicament(string fisier)
{
    ofstream out(fisier);
    out<<da_nume_random(15)<<'\n'; ///numele medicamentului
    int cate = rand() % 5 + 1;
    out<<cate<<'\n';
    for ( int i = 1 ; i <= cate ; i++ )
    {
        int tip = rand() % 4;
        out<<tip<<'\n';
        Data* aux = da_data_random();
        out<<da_nume_random(6)<<" "<<da_nume_random(2)<<"/"<<da_nume_random(2)<<" "<<rand()%200+0.23<<" "<<rand()%4 + 0.1<<" "<<rand()%1000<<" "<<aux->get_zi()<<" "<<aux->get_luna()<<" "<<aux->get_an()<<" ";
        if ( tip == 0 )
        {
            out<<'\n';
            continue;
        }
        out<<1.0*((rand()%100)/100) + 0.1<<' ';
        if ( tip == 1 || tip == 2)
        {
            out<<'\n';
            continue;
        }
        out<<((1.0*(rand()%100))/100)<<'\n';
    }
}
string to_str(int i)
{
    string ans = "";
    while ( i )
    {
        ans += ((i % 10) + '0');
        i /= 10;
    }
    if ( ans == "" )
        ans = "0";
    return ans;
}
int f_cardio(float cate_naspa)
{
    return min((int)cate_naspa, 2);
}
bool f_pacient_mereu(Pacient* p)
{
    return true;
}
bool f_adult_risc_ridicat(Pacient* p)
{
    if ( dynamic_cast<Adult*>(p) != 0 )
    {
        if ( p -> get_prop_numerica("Risc Cardiovascular") -> evalueaza() == "RIDICAT" )
            return true;
    }
    return false;
}
bool f_copil_risc(Pacient* p)
{
    if ( dynamic_cast<Copil*>(p) != 0 )
    {
        if ( p -> get_prop_numerica("Risc Cardiovascular") -> evalueaza() != "NU" )
            return true;
    }
    return false;
}
string f_nume_familie(Pacient* p)
{
    return p->get_date().get_nume();
}
int f_tip_date(Pacient* p)
{
    if ( dynamic_cast<Copil*>(p) != 0 )
    {
        return 2;
    }
    if ( dynamic_cast<Adult_peste40*>(p) != 0 )
    {
        return 0;
    }
    return 1;
}
class Program
{
    Baza_De_Date baza;
    vector<Data> date_random;
    Test_analiza<bool, float> tensiune_buna, tensiune_naspa, proteina_c_optim, proteina_c_naspa;
    Test_analiza<int, float> colesterol_optim, colesterol_normal, colesterol_crescut;
public:
    template<typename T>
    void Adauga_Risc_Cardiovascular(T*& p)
    {
        function<int(float)> fcardio = f_cardio;
        map<int, string> mpcardio = {{0, "NU"}, {1, "DA"}, {2, "RIDICAT"}};
        vector<int> normal = {0};
        int aux = p -> get_cate_naspa();
        Restrictie<int, float> r(fcardio, mpcardio, normal);
        Restrictie_Pacient<int, float>* cardio = new Restrictie_Pacient<int, float>(r, "Risc Cardiovascular", aux);
        p->adauga_prop_numerica(cardio);
    }
    void baga_date_random(int nr)
    {
        for ( int i = 1 ; i <= nr ; i++ )
        {
            int zi = (rand() % 28) + 1;
            int luna = (rand() % 12) + 1;
            int an = 2000 + (rand() % 25);
            date_random.push_back(*(creeaza<Data>(zi, luna, an, '.')));
        }
    }
    void baga_medicamente_random(int nr)
    {
        for ( int i = 1 ; i <= nr ; i++ )
        {
            string numf = "medicamente" + to_str(i) + ".txt";
            baga_un_medicament(numf);
            Medicament aux;
            ifstream in(numf);
            in>>aux;
            Medicament* med = new Medicament(aux);
            baza.adauga_medicament(med);
        }
    }
    vector<Medicament*> tratament_random(int cate)
    {
        const int PAS = baza.get_medicamente().size() / cate;
        int i = 0, puse = 0, timer = rand()%PAS;
        vector<Medicament*> ans;
        while ( i < baza.get_medicamente().size() && puse < cate )
        {
            if ( timer == 0 )
            {
                timer = rand() % PAS;
                ans.push_back(baza.get_medicamente()[i]);
                puse++;
            }
            i++;
            timer--;
        }
        return ans;
    }
    void creeaza_teste()
    {
        map<bool, string> mp = {{true, "OK"}, {false, "Ridicat"}};
        map<int, string> mpcol = {{0, "Optim"}, {1, "Normal"}, {2, "Crescut"}};
        map<bool, string> mpc = {{true, "OK"}, {false, "Neoptim"}};
        vector<bool> v = {true};
        vector<int> vcol = {0, 1};
        function<bool(float)> aux = f_tensiune_buna, auxc = protc_optim;
        function<int(float)> auxcol = cole;
        Restrictie<bool, float> r(aux, mp, v), rc(auxc, mpc, v);
        Restrictie<int, float> rcol(auxcol, mpcol, vcol);
        tensiune_buna = *(new Test_analiza<bool, float>("Tensiune", "", 137, date_random[0], r));
        tensiune_naspa = *(new Test_analiza<bool, float>("Tensiune", "", 151, date_random[1], r));
        colesterol_optim = *(new Test_analiza<int, float>("Colesterol", "mg/dl", 190, date_random[2], rcol));
        colesterol_normal = *(new Test_analiza<int, float>("Colesterol", "mg/dl", 220.4, date_random[3], rcol));
        colesterol_crescut = *(new Test_analiza<int, float>("Colesterol", "mg/dl", 250.69, date_random[4], rcol));
        proteina_c_optim = *(new Test_analiza<bool, float>("Proteina C", "mg/dl", 0.20, date_random[5], rc));
        proteina_c_naspa = *(new Test_analiza<bool, float>("Proteina C", "mg/dl", 0.70, date_random[6], rc));
    }
    void afis_medicamente(ostream& out)
    {
        for ( Medicament* m : baza.get_medicamente() )
        {
            out<<*m<<'\n';
        }
    }
    void baga_ierarhia()
    {   vector<Test_analiza<int, float>*> col_normal({&colesterol_normal}), col_crescut({&colesterol_crescut}), col_optim({&colesterol_optim});
        vector<Test_analiza<bool, float>*> t_normal({&tensiune_buna}), t_naspa({&tensiune_naspa});
        vector<Medicament*> aux1 = tratament_random(2), aux2 = tratament_random(3), aux3 = tratament_random(4), aux4 = tratament_random(3), aux5 = tratament_random(1), aux6, aux7, aux8, aux9;
        Pacient* p1 = new Pacient(*(new Date_om("Tau", "Bunicul", "La stanga si te duci", 79)), new Fisa(aux1, col_normal, t_naspa));
        Pacient* p2 = new Pacient(*(new Date_om("Tau", "Bunica", "La stanga si te duci", 69)), new Fisa(aux2, col_optim, t_normal));
        Pacient* p3 = new Pacient(*(new Date_om("Ta", "Bunicul", "La dreapta si te duci", 89)), new Fisa(aux3, col_crescut, t_naspa));
        Pacient* p4 = new Pacient(*(new Date_om("Ta", "Bunica", "La dreapta si te duci", 100)), new Fisa(aux4, col_crescut, t_normal));
        Pacient* p5 = new Pacient(*(new Date_om("Tau", "Tatal", "In fata si te duci", 49)), new Fisa(aux5, col_normal, t_normal));
        Pacient* p6 = new Pacient(*(new Date_om("Tau", "Mama", "In fata si te duci", 49)), new Fisa(aux6, col_optim, t_normal));
        Pacient* p7 = new Pacient(*(new Date_om("Tau", "Copil1", "In fata si te duci", 15)), new Fisa(aux7, col_optim, t_normal));
        Pacient* p8 = new Pacient(*(new Date_om("Tau", "Copil2", "In fata si te duci", 12)), new Fisa(aux8, col_normal, t_normal));
        Pacient* p9 = new Pacient(*(new Date_om("Tau", "Copil3", "In fata si te duci", 9)), new Fisa(aux9, col_crescut, t_naspa));
        Adult_peste40* a1 = new Adult_peste40(*(new Adult(*p1, p5)), true, 2); 
        Adult_peste40* a2 = new Adult_peste40(*(new Adult(*p2, p5)), false, 1); 
        Adult_peste40* a3 = new Adult_peste40(*(new Adult(*p3, p6)), false, 2); 
        Adult_peste40* a4 = new Adult_peste40(*(new Adult(*p4, p6)), false, 0); 
        Adult* a5 = new Adult(*p5, p7); 
        Adult* a6 = new Adult(*p6, p7); 
        Copil* c1 = new Copil(*p7, a5, a6);
        Copil* c2 = new Copil(*p8, a5, a6);
        Copil* c3 = new Copil(*p9, a5, a6);
        a5 -> sterge_copil(p7);
        a6 -> sterge_copil(p7);
        a5 -> adauga_copil(c1);
        a5 -> adauga_copil(c2);
        a5 -> adauga_copil(c3);
        a6 -> adauga_copil(c1);
        a6 -> adauga_copil(c2);
        a6 -> adauga_copil(c3);
        Adauga_Risc_Cardiovascular(a1);
        Adauga_Risc_Cardiovascular(a2);
        Adauga_Risc_Cardiovascular(a3);
        Adauga_Risc_Cardiovascular(a4);
        Adauga_Risc_Cardiovascular(a5);
        Adauga_Risc_Cardiovascular(a6);
        Adauga_Risc_Cardiovascular(c1);
        Adauga_Risc_Cardiovascular(c2);
        Adauga_Risc_Cardiovascular(c3);
        baza.adauga_pacient(a1);
        baza.adauga_pacient(a2);
        baza.adauga_pacient(a3);
        baza.adauga_pacient(a4);
        baza.adauga_pacient(a5);
        baza.adauga_pacient(a6);
        baza.adauga_pacient(c1);
        baza.adauga_pacient(c2);
        baza.adauga_pacient(c3);
    }
    void baga_afisari()
    {
        ///Afisam toti pacientii
        function<bool(Pacient*)> f_mereu = f_pacient_mereu, f_a_ridicat = f_adult_risc_ridicat, f_c_risc = f_copil_risc;
        function<string(Pacient*)> f_familie = f_nume_familie;
        Afisare_Abstracta<bool, Pacient>* af_tot = new Afisare_Abstracta<bool, Pacient>("Toti Pacientii", f_mereu, baza.get_pacienti());
        Afisare_Abstracta<bool, Pacient>* af_a_ridicat = new Afisare_Abstracta<bool, Pacient>("Adulti cu factor de risc cardiovascular ridicat", f_a_ridicat, baza.get_pacienti());
        Afisare_Abstracta<bool, Pacient>* af_c_risc = new Afisare_Abstracta<bool, Pacient>("Copiii cu factor de risc cardiovascular", f_c_risc, baza.get_pacienti());
        Afisare_Abstracta<string, Pacient>* af_dupa_nume = new Afisare_Abstracta<string, Pacient>("Afisare dupa numele de familie", f_familie, baza.get_pacienti());
        baza.adauga_afp_select(af_dupa_nume);
        baza.adauga_afp_simplu(af_tot);
        baza.adauga_afp_simplu(af_a_ridicat);
        baza.adauga_afp_simplu(af_c_risc);
    }
    void incepe_baza_de_date()
    {
        baga_date_random(50);
        creeaza_teste();
        baga_medicamente_random(20);
        baga_ierarhia();
        baga_afisari();
    }
    void af_medicamente()
    {
        cout<<"Ce vrei afisat?\n";
        int idx = 0;
        for ( int i = 0 ; i < baza.get_afm_simplu().size() ; i++ )
        {
            cout<<++idx<<") "<<baza.get_afm_simplu()[i]->get_nume()<<'\n';
        }
        for ( int i = 0 ; i < baza.get_afm_select().size() ; i++ )
        {
            cout<<++idx<<") "<<baza.get_afm_select()[i]->get_nume()<<'\n';
        }
        int optiune;
        cin>>optiune;
        if ( optiune <= baza.get_afm_simplu().size() )
            baza.get_afm_simplu()[optiune-1]->afisare_simplu(cout, true);
        else{
            cout<<"Alege ce tipuri de medicamente vrei?\n";
            string s;
            getline(cin, s);
            baza.get_afm_select()[optiune-baza.get_afm_simplu().size()-1]->afisare_simplu(cout, s);
        }
    }
    void af_pacienti()
    {
        cout<<"Ce vrei afisat?\n";
        int idx = 0;
        for ( int i = 0 ; i < baza.get_afp_simplu().size() ; i++ )
        {
            cout<<++idx<<") "<<baza.get_afp_simplu()[i]->get_nume()<<'\n';
        }
        for ( int i = 0 ; i < baza.get_afp_select().size() ; i++ )
        {
            cout<<++idx<<") "<<baza.get_afp_select()[i]->get_nume()<<'\n';
        }
        int optiune;
        function<int(Pacient*)> faux = f_tip_date;
        vector<int> ord = {0, 1, 2};
        map<int, string> mp = {{0, "Adulti\nAdulti peste 40 de ani"}, {1, "Adulti sub 40 de ani"}, {2, "Copii"}};
        cin>>optiune;
        if ( optiune <= baza.get_afp_simplu().size() ){
            baza.get_afp_simplu()[optiune-1]->afisare_specific(cout, true, faux, ord, mp);
        }
        else{
            cout<<"Alege ce tipuri de persoane vrei?\n";
            string s;
            cin.get();
            getline(cin, s);
            baza.get_afp_select()[optiune-baza.get_afp_simplu().size()-1]->afisare_specific(cout, s, faux, ord, mp);
        }
    }
    void afisari()
    {
        cout<<"Vrei sa vezi medicamente sau pacienti?\n1)Medicamente\n2)Pacienti\n";
        int optiune;
        cin>>optiune;
        if ( optiune == 1 )
        {
            af_medicamente();
        }
        else
        {
            af_pacienti();
        }
    }
    void run()
    {
        afisari();
    }
};



bool efum(float x)
{
    if ( x > 0 )
        return true;
    return false;
}

///Colesterol 250 25 5 2024
///TODO Testare!!
int main()
{
    srand(time(NULL));
    Program p;
    p.incepe_baza_de_date();
    p.run();
    return 0;
}

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
    in>>this -> nume>>this -> cantitate>>this -> unitate>>this -> indice_intensitate>>this -> pret>>this -> expirare;
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
        Substanta* s;
        if ( tip == 1 )
        {
            SubstantaIeftina su;
            su.citeste(in);
            s = &su;
            
        }
        else if ( tip == 2 )
        {
            Substanta_onsale su;
            su.citeste(in);
            s = &su;
        }
        else if ( tip == 3 )
        {
            SubstantaIeftina_onsale su;
            su.citeste(in);
            Substanta_onsale* aux = &su; ///duamne ajuta
            s = aux;
        }
        else
        {
            s -> citeste(in);
        }
        substante.push_back(s);
    }
}
class Fisa
{
    vector<Medicament*> tratament_activ;
    vector< Test_analiza<int, float>* > analize_numerice; ///care verifica o valoare si il pune intr-un bucket
    vector< Test_analiza<bool, bool>* > analize_booleene; ///care verifica daca este sau nu cumva
public:
    Fisa(){}
    Fisa(vector<Medicament*>& v, vector<Test_analiza<int, float>*>& an, vector<Test_analiza<bool, bool>*>& ab): tratament_activ(v), analize_numerice(an), analize_booleene(ab){}
    void adauga_medicament(Medicament* m);
    void adauga_numeric(Test_analiza<int, float>* t);
    void adauga_boolean(Test_analiza<bool, bool>* t);
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
    Test_analiza<bool, bool>* get_analiza_booleana(int i);
    Test_analiza<bool, bool>* get_analiza_booleana(string nume_substanta);
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
void Fisa::adauga_boolean(Test_analiza<bool, bool>* t)
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
Test_analiza<bool, bool>* Fisa::get_analiza_booleana(string nume)
{
    for ( Test_analiza<bool, bool>* t : analize_booleene )
    {
        if ( t -> get_substanta() == nume )
            return t;
    }
    return nullptr;
}
Test_analiza<bool, bool>* Fisa::get_analiza_booleana(int i)
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
        Test_analiza<bool, bool> t;
        t.citeste(in);
        analize_booleene.push_back(&t);
    }
}

void Fisa::afiseaza_analize_booleene(ostream& out)
{
    for ( Test_analiza<bool, bool>* t : analize_booleene )
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
#pragma once
#include "./Program.hpp"

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

Data* da_data_random();

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
    reverse(ans.begin(), ans.end());
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
Data* da_data_random()
{
    int zi = (rand() % 28) + 1;
    int luna = (rand() % 12) + 1;
    int an = 2000 + (rand() % 25);
    return Program::creeaza<Data>(zi, luna, an, '/');
}

template<typename T, typename ...Types>
T* Program::creeaza(Types ...args_constructor)
{
    T* ans = new T(args_constructor...);
    return ans;
}
template<typename T>
void Program::Adauga_Risc_Cardiovascular(T*& p)
{
    function<int(float)> fcardio = f_cardio;
    
    vector<int> normal = {0};
    int aux = p -> get_cate_naspa();
    Restrictie<int, float> r(fcardio, mpcardio, normal);
    Restrictie_Pacient<int, float>* cardio = new Restrictie_Pacient<int, float>(r, "Risc Cardiovascular", aux);
    p->adauga_prop_numerica(cardio);
}
void Program::baga_date_random(int nr)
{
    for ( int i = 1 ; i <= nr ; i++ )
    {
        int zi = (rand() % 28) + 1;
        int luna = (rand() % 12) + 1;
        int an = 2000 + (rand() % 25);
        date_random.push_back(*(creeaza<Data>(zi, luna, an, '.')));
    }
}
void Program::baga_medicamente_random(int nr)
{
    for ( int i = 1 ; i <= nr ; i++ )
    {
        string numf = "medicamente" + to_str(i) + ".txt";
        baga_un_medicament(numf);
        Medicament aux;
        ifstream in(numf);
        in>>aux;
        Medicament* med = new Medicament(aux);
        Baza_De_Date::get_instanta()->adauga_medicament(med);
    }
}
vector<Medicament*> Program::tratament_random(int cate)
{
    const int PAS = Baza_De_Date::get_instanta()->get_medicamente().size() / cate;
    int i = 0, puse = 0, timer = rand()%PAS;
    vector<Medicament*> ans;
    while ( i < Baza_De_Date::get_instanta()->get_medicamente().size() && puse < cate )
    {
        if ( timer == 0 )
        {
            timer = rand() % PAS;
            ans.push_back(Baza_De_Date::get_instanta()->get_medicamente()[i]);
            puse++;
        }
        i++;
        timer--;
    }
    return ans;
}
void Program::creeaza_teste()
{
    map<bool, string> mp_tensiune = {{true, "OK"}, {false, "Ridicat"}};
    map<int, string> mpcol = {{0, "Optim"}, {1, "Normal"}, {2, "Crescut"}};
    map<bool, string> mpc = {{true, "OK"}, {false, "Neoptim"}};
    vector<bool> v = {true};
    vector<int> vcol = {0, 1};
    function<bool(float)> aux = f_tensiune_buna, auxc = protc_optim;
    function<int(float)> auxcol = cole;
    Restrictie<bool, float> r(aux, mp_tensiune, v), rc(auxc, mpc, v);
    Restrictie<int, float> rcol(auxcol, mpcol, vcol);
    tensiune_buna = *(new Test_analiza<bool, float>("Tensiune", "", 137, date_random[0], r));
    tensiune_naspa = *(new Test_analiza<bool, float>("Tensiune", "", 151, date_random[1], r));
    colesterol_optim = *(new Test_analiza<int, float>("Colesterol", "mg/dl", 190, date_random[2], rcol));
    colesterol_normal = *(new Test_analiza<int, float>("Colesterol", "mg/dl", 220.4, date_random[3], rcol));
    colesterol_crescut = *(new Test_analiza<int, float>("Colesterol", "mg/dl", 250.69, date_random[4], rcol));
    proteina_c_optim = *(new Test_analiza<bool, float>("Proteina C", "mg/dl", 0.20, date_random[5], rc));
    proteina_c_naspa = *(new Test_analiza<bool, float>("Proteina C", "mg/dl", 0.70, date_random[6], rc));
}
void Program::afis_medicamente(ostream& _out)
{
    for ( Medicament* m : Baza_De_Date::get_instanta()->get_medicamente() )
    {
        _out<<*m<<'\n';
    }
}
void Program::baga_ierarhia()
{   
    vector<Test_analiza<int, float>*> col_normal({&colesterol_normal}), col_crescut({&colesterol_crescut}), col_optim({&colesterol_optim});
    vector<Test_analiza<bool, float>*> t_normal({&tensiune_buna}), t_naspa({&tensiune_naspa});
    vector<Medicament*> aux1 = tratament_random(2), aux2 = tratament_random(3), aux3 = tratament_random(4), aux4 = tratament_random(3), aux5 = tratament_random(1), aux6, aux7, aux8, aux9;
    Pacient* p5 = new Pacient(*(new Date_om("Tau", "Tatal", "In fata si te duci", 49)), new Fisa(aux5, col_normal, t_normal));
    Pacient* a1 = new Adult_peste40(*(new Adult(*(new Pacient(*(new Date_om("Tau", "Bunicul", "La stanga si te duci", 79)), new Fisa(aux1, col_normal, t_naspa))), p5)), true, 2); ;
    Pacient* p2 = new Pacient(*(new Date_om("Tau", "Bunica", "La stanga si te duci", 69)), new Fisa(aux2, col_optim, t_normal));
    Pacient* p3 = new Pacient(*(new Date_om("Ta", "Bunicul", "La dreapta si te duci", 89)), new Fisa(aux3, col_crescut, t_naspa));
    Pacient* p4 = new Pacient(*(new Date_om("Ta", "Bunica", "La dreapta si te duci", 100)), new Fisa(aux4, col_crescut, t_normal));
    Pacient* p6 = new Pacient(*(new Date_om("Tau", "Mama", "In fata si te duci", 49)), new Fisa(aux6, col_optim, t_normal));
    Pacient* p7 = new Pacient(*(new Date_om("Tau", "Copil1", "In fata si te duci", 15)), new Fisa(aux7, col_optim, t_normal));
    Pacient* p8 = new Pacient(*(new Date_om("Tau", "Copil2", "In fata si te duci", 12)), new Fisa(aux8, col_normal, t_normal));
    Pacient* p9 = new Pacient(*(new Date_om("Tau", "Copil3", "In fata si te duci", 9)), new Fisa(aux9, col_crescut, t_naspa));
    Adult_peste40* a2 = new Adult_peste40(*(new Adult(*p2, p5)), false, 1); 
    Adult_peste40* a3 = new Adult_peste40(*(new Adult(*p3, p6)), false, 2); 
    Adult_peste40* a4 = new Adult_peste40(*(new Adult(*p4, p6)), false, 0); 
    Adult* a5 = new Adult(*p5, p7); 
    Adult* a6 = new Adult(*p6, p7); 
    reference_wrapper<Adult*> aux = a6;
    Copil* c1 = new Copil(*p7, a5, aux.get());
    Copil* c2 = new Copil(*p8, a5, aux.get());
    Copil* c3 = new Copil(*p9, a5, aux.get());
    a5 -> sterge_copil(p7);
    aux.get() -> sterge_copil(p7);
    a5 -> adauga_copil(c1);
    a5 -> adauga_copil(c2);
    a5 -> adauga_copil(c3);
    aux.get() -> adauga_copil(c1);
    aux.get() -> adauga_copil(c2);
    aux.get() -> adauga_copil(c3);
    Adauga_Risc_Cardiovascular(a1);
    Adauga_Risc_Cardiovascular(a2);
    Adauga_Risc_Cardiovascular(a3);
    Adauga_Risc_Cardiovascular(a4);
    Adauga_Risc_Cardiovascular(a5);
    Adauga_Risc_Cardiovascular(aux.get());
    Adauga_Risc_Cardiovascular(c1);
    Adauga_Risc_Cardiovascular(c2);
    Adauga_Risc_Cardiovascular(c3);
    Baza_De_Date::get_instanta()->adauga_pacient(a1);
    Baza_De_Date::get_instanta()->adauga_pacient(a2);
    Baza_De_Date::get_instanta()->adauga_pacient(a3);
    Baza_De_Date::get_instanta()->adauga_pacient(a4);
    Baza_De_Date::get_instanta()->adauga_pacient(a5);
    Baza_De_Date::get_instanta()->adauga_pacient(aux.get());
    Baza_De_Date::get_instanta()->adauga_pacient(c1);
    Baza_De_Date::get_instanta()->adauga_pacient(c2);
    Baza_De_Date::get_instanta()->adauga_pacient(c3);
}
void Program::baga_afisari()
{
    function<bool(Pacient*)> f_mereu = f_pacient_mereu, f_a_ridicat = f_adult_risc_ridicat, f_c_risc = f_copil_risc;
    function<string(Pacient*)> f_familie = f_nume_familie;
    function<bool(Medicament*)> f = [](Medicament* ){return true;};
    Afisare_Abstracta<bool, Medicament>* af_tot_med = new Afisare_Abstracta<bool, Medicament>("Toate Medicamentele", f, Baza_De_Date::get_instanta()->get_medicamente());
    Afisare_Abstracta<bool, Pacient>* af_tot = new Afisare_Abstracta<bool, Pacient>("Toti Pacientii", f_mereu, Baza_De_Date::get_instanta()->get_pacienti());
    Afisare_Abstracta<bool, Pacient>* af_a_ridicat = new Afisare_Abstracta<bool, Pacient>("Adulti cu factor de risc cardiovascular ridicat", f_a_ridicat, Baza_De_Date::get_instanta()->get_pacienti());
    Afisare_Abstracta<bool, Pacient>* af_c_risc = new Afisare_Abstracta<bool, Pacient>("Copiii cu factor de risc cardiovascular", f_c_risc, Baza_De_Date::get_instanta()->get_pacienti());
    Afisare_Abstracta<string, Pacient>* af_dupa_nume = new Afisare_Abstracta<string, Pacient>("Afisare dupa numele de familie", f_familie, Baza_De_Date::get_instanta()->get_pacienti());
    Baza_De_Date::get_instanta()->adauga_afm_simplu(af_tot_med);
    Baza_De_Date::get_instanta()->adauga_afp_select(af_dupa_nume);
    Baza_De_Date::get_instanta()->adauga_afp_simplu(af_tot);
    Baza_De_Date::get_instanta()->adauga_afp_simplu(af_a_ridicat);
    Baza_De_Date::get_instanta()->adauga_afp_simplu(af_c_risc);
}
void Program::incepe_baza_de_date()
{
    baga_date_random(50);
    creeaza_teste();
    baga_medicamente_random(20);
    baga_ierarhia();
    baga_afisari();
}
void Program::af_medicamente()
{
    cout<<"Ce vrei afisat?\n";
    int idx = 0;
    for ( int i = 0 ; i < Baza_De_Date::get_instanta()->get_afm_simplu().size() ; i++ )
    {
        cout<<++idx<<") "<<Baza_De_Date::get_instanta()->get_afm_simplu()[i]->get_nume()<<'\n';
    }
    for ( int i = 0 ; i < Baza_De_Date::get_instanta()->get_afm_select().size() ; i++ )
    {
        cout<<++idx<<") "<<Baza_De_Date::get_instanta()->get_afm_select()[i]->get_nume()<<'\n';
    }
    int optiune;
    cin>>optiune;
    if ( optiune <= Baza_De_Date::get_instanta()->get_afm_simplu().size() )
        Baza_De_Date::get_instanta()->get_afm_simplu()[optiune-1]->afisare_simplu(cout, true);
    else{
        cout<<"Alege ce tipuri de medicamente vrei?\n";
        string s;
        getline(cin, s);
        Baza_De_Date::get_instanta()->get_afm_select()[optiune-Baza_De_Date::get_instanta()->get_afm_simplu().size()-1]->afisare_simplu(cout, s);
    }
}
void Program::af_pacienti()
{
    cout<<"Ce vrei afisat?\n";
    int idx = 0;
    for ( int i = 0 ; i < Baza_De_Date::get_instanta()->get_afp_simplu().size() ; i++ )
    {
        cout<<++idx<<") "<<Baza_De_Date::get_instanta()->get_afp_simplu()[i]->get_nume()<<'\n';
    }
    for ( int i = 0 ; i < Baza_De_Date::get_instanta()->get_afp_select().size() ; i++ )
    {
        cout<<++idx<<") "<<Baza_De_Date::get_instanta()->get_afp_select()[i]->get_nume()<<'\n';
    }
    int optiune;
    function<int(Pacient*)> faux = f_tip_date;
    vector<int> ord = {0, 1, 2};
    map<int, string> mp = {{0, "Adulti\nAdulti peste 40 de ani"}, {1, "Adulti sub 40 de ani"}, {2, "Copii"}};
    cin>>optiune;
    if ( optiune <= Baza_De_Date::get_instanta()->get_afp_simplu().size() ){
        Baza_De_Date::get_instanta()->get_afp_simplu()[optiune-1]->afisare_specific(cout, true, faux, ord, mp);
    }
    else{
        cout<<"Alege ce tipuri de persoane vrei?\n";
        string s;
        cin.get();
        getline(cin, s);
        Baza_De_Date::get_instanta()->get_afp_select()[optiune-Baza_De_Date::get_instanta()->get_afp_simplu().size()-1]->afisare_specific(cout, s, faux, ord, mp);
    }
}
void Program::afisari()
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
void Program::run()
{
    afisari();
}
/*void citeste_persoana(istream& in, ostream& out, Pacient& p)
{
    out<<"-Date Personale\nNume: ";
    string nume, prenume, adresa;
    in>>nume;
    out<<"Prenume: ";
    in>>prenume;
    out<<"Adresa: ";
    in>>adresa;
    int varsta;
    out<<"Varsta: ";
    in>>varsta;
    Date_om d(nume, prenume, adresa, varsta);
    vector<Test_analiza<int, float>*> col_normal({&colesterol_normal}), col_crescut({&colesterol_crescut}), col_optim({&colesterol_optim});
    vector<Test_analiza<bool, float>*> t_normal({&tensiune_buna}), t_naspa({&tensiune_naspa});
    vector<Medicament*> tratament;
    int nr_medicamente;
    Fisa *f = new Fisa();
    out<<"-Tratament:\nNumar de medicamente: ";
    in>>nr_medicamente;
    for ( int i = 1 ; i <= nr_medicamente ; i++ )
    {
        string nume;
        out<<"Nume medicament: ";
        getline(in, nume);
        Medicament* m = Baza_De_Date::get_instanta()->get_medicament(nume);
        if ( m != NULL )
        {
            f->adauga_medicament(m);
        }
        else
        {
            out<<"Nu avem acest medicament\n";
        }
    }
    out<<"-Analize\nNumar de analize: ";
    in>>nr_medicamente;
    string nume, unitate;
    float masurare;
    int zi, luna, an, tip;
    for ( int i = 1 ; i <= nr_medicamente ; i++ )
    {
        out<<"Ce fel de tip de analiza?\n1)Care este masurat in mai multe nivele?\n2)Care poate sa fie naspa sau nu?\n";
        in>>tip;
        out<<"Numele substantei masurate: ";
        in>>nume;
        out<<"Unitatea de masura: ";
        in>>unitate;
        out<<"Valoarea Masurata: ";
        in>>masurare;
        out<<"Data la care a fost masurata(zi luna an): ";
        in>>zi>>luna>>an;
        if ( tip == 1 )
        {
            ///NU FAC ASA CEVA, VOI REVENI CAND DAU REFACTOR LA TEST_ANALIZE
        }
    }
}*/
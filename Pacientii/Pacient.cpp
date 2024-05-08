#pragma once
#include "./Pacient.hpp"

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
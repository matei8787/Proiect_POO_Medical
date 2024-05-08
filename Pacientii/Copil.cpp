#pragma once
#include "./Copil.hpp"

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



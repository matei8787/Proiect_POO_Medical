#pragma once
#include "Adult_Peste40.hpp"

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
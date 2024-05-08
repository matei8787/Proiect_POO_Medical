#include "./includuri.hpp"
#include "./rest_includuri.hpp"
/*template<typename T, typename U>
function<T(U)> creeaza_functie_universala(vector<U>& trepte) ///prea multe structuri algebrice :))
{
    function<T(U)> f=[](U prop){
        for ( int i = 0 ; i < trepte.size() ; i++ )
        {
            if ( prop > trepte[i] )
                return i;
        }
        return trepte.size()
    };
    return f;
}*/
int main()
{
    srand(time(NULL));
    Program p;
    p.incepe_baza_de_date();
    p.run();
    return 0;
}

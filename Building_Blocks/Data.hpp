#pragma once
#include "../includuri.hpp"

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
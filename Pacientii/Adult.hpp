#pragma once
#include "./Pacient.cpp"
#include "./Pacient.hpp"

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
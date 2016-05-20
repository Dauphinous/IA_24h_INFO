#ifndef CAVE_H
#define CAVE_H
#include"Salle.h"
#include<vector>
#include<cstdlib>

class Cave
{
private:
    std::vector<std::vector <Salle *>> m_salles;


public:
    Cave(int lignes, int colonnes, const std::string &casiers);
    virtual ~Cave();
    Salle* getSalle(int l, int c);
};

#endif // CAVE_H

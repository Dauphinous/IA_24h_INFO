#ifndef CAVE_H
#define CAVE_H
#include"Salle.h"
#include<vector>


class Cave
{
private:
    std::vector<std::vector <Salle *>> m_salles;

public:
    Cave(std::vector<std::vector<Salle*>> salles);
    virtual ~Cave();
    Salle* getSalle(int l, int c);
};

#endif // CAVE_H

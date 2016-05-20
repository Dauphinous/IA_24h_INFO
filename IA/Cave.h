#ifndef CAVE_H
#define CAVE_H
#include"Salle.h"
#include<vector>
#include<cstdlib>

class Cave
{
private:
    std::vector<std::vector <Salle *>> m_salles;
    std::pair<int, int> m_pos_escalier;
public:
    Cave(int lignes, int colonnes, const std::string &casiers);
    virtual ~Cave();
    Salle * getSalle(int l, int c);
    Salle * getEscalier();

    std::vector<std::vector <Salle *> > & getSalles();
};

#endif // CAVE_H

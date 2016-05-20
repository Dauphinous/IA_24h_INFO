#ifndef SALLE_H
#define SALLE_H

#include <utility>
#include <vector>
#include <map>

enum Direction
{
    Nord,
    Est,
    Sud,
    Ouest,

    NbDeDirections
};

class Salle
{
public:
    Salle(int ligne, int colonne, bool stock, int nbEmplacementsLibres, const std::map<Direction, Salle *> voisins);
    virtual ~Salle();

    const std::pair<int, int> & getPosition()  const;
    Salle *                     voisin(const Direction & laDirection);
    int                         nbEmplacementsLibres()  const;
    bool                        possedeStock()  const;
    std::pair<int, int>         distanceParRapportA(const Salle & uneSalle)  const;
private:
    const std::pair<int, int>              m_position;
    std::vector<bool>                      m_emplacementsLibres;
    std::map<Direction, Salle *>           m_voisins;
    const bool                             m_stock;
};

#endif // SALLE_H

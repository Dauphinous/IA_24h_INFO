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
    int Points = 0;

    Salle(int ligne, int colonne, int distance, int nbEmplacementsLibres);
    virtual ~Salle();

    const std::pair<int, int> & getPosition()  const;
    Salle *                     voisin(const Direction & laDirection);
    int                         nbEmplacementsLibres()  const;
    bool                        possedeStock()  const;
    std::pair<int, int>         distanceParRapportA(const Salle & uneSalle)  const;
    int                         distanceParRapportA(const std::pair<int ,int> & p)  const;
    int                         scorePossible() const;
    int                         getDistance() const;
private:
    const std::pair<int, int>              m_position;
    std::map<Direction, Salle *>           m_voisins;
    int                                    m_distance;
    int                                    m_nb_emplacement;
};

#endif // SALLE_H

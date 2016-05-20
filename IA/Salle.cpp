#include "Salle.h"
#include <cmath>

using namespace std;

Salle::Salle(int ligne, int colonne, int distanceStock, int nbEmpLibres, const std::map<Direction, Salle *> lesVoisins) :
    m_position (ligne, colonne),
    m_emplacementsLibres (nbEmpLibres, true),
    m_voisins (lesVoisins),
    m_distance (distanceStock)
{

}

Salle::~Salle()
{

}

const std::pair<int, int> & Salle::getPosition() const
{
    return m_position;
}

Salle * Salle::voisin(const Direction & laDirection)
{
    if(m_voisins.find(laDirection) != m_voisins.end()) // si il y un voisin a la direction donne
        return m_voisins[laDirection];

    return nullptr; // sinon on retourne
}

int Salle::nbEmplacementsLibres() const
{
    int nb = 0;
    for(const bool & b : m_emplacementsLibres)
        if(b) nb ++;

    return nb;
}

bool Salle::possedeStock() const
{
    return m_distance == 0;
}

std::pair<int, int> Salle::distanceParRapportA(const Salle & uneSalle) const
{
    return make_pair(abs(m_position.first - uneSalle.m_position.first),
                     abs(m_position.second - uneSalle.m_position.second));
}

int Salle::scorePossible() const
{
    return 4 * (m_distance + 1);
}

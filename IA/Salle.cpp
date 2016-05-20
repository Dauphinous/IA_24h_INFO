#include "Salle.h"
#include <cmath>

using namespace std;

Salle::Salle(int ligne, int colonne, int distanceStock, int nbEmpLibres) :
    m_position (ligne, colonne),
    m_distance (distanceStock),
    m_nb_emplacement{nbEmpLibres}
{

}

Salle::~Salle()
{

}

const std::pair<int, int> & Salle::getPosition() const
{
    return m_position;
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

int Salle::nbEmplacementsLibres() const
{
    return m_nb_emplacement;
}

#include "Cave.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <cstdlib>

using namespace std;
Cave::Cave(int lignes, int colonnes,const string & casiers)
{
    //// initialisation
    vector<Salle *> courant;
    for(size_t s = 0U ; s < lignes ; ++s)
    {
        courant.clear();
        for(size_t ss = 0U ; ss < colonnes ; ++ss)
        {
            courant.push_back(nullptr);
        }
        m_salles.push_back(courant);
    }
    /////

    size_t stock = casiers.find("@");
    if(stock == string::npos)
    {
        cout<<"pas d'escalier dans la cave"<<endl;
        exit(1);
    }

    pair<int, int> positionStock;
    int numColonne = stock;
    int numLigne   = 0;
    do
    {
        numColonne -= colonnes;
        numLigne++;
    } while(numColonne - colonnes > 0);

    positionStock = make_pair(numLigne, numColonne);


    for(int i=0;i<lignes;i++)
    {
        for(int j=0; j<colonnes;j++)
        {
            m_salles[i][j]=new Salle (i,j, abs(j - positionStock.second) + abs(i - positionStock.first),
            casiers[i * lignes + j] - '0');

        }
    }
    m_pos_escalier.first = positionStock.first;
    m_pos_escalier.second = positionStock.second;
}

Cave::~Cave()
{
    for(auto &i: m_salles)
    {
        for(auto & j :i)
        {
            delete j;
        }
    }
}

Salle *Cave::getSalle(int l, int c)
{
    return m_salles[l][c];

}

std::vector<std::vector <Salle *> > & Cave::getSalles()
{
    return m_salles;
}
std::pair<int, int> Cave::getEscalier()
{
    return m_pos_escalier;
}


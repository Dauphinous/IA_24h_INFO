#include "Cave.h"
using namespace std;
Cave::Cave(vector<vector<Salle*>> salles)
    :m_salles{salles}
{


}

Cave::~Cave()
{

}

Salle *Cave::getSalle(int l, int c)
{
    return m_salles[l][c];

}

#ifndef MANUTENTIONNAIRE_H
#define MANUTENTIONNAIRE_H

#include "Bouteille.h"
#include "Action.h"

const int NB_BOUTEILLE_MAX = 10;
const int NB_MAX_ACTION = 7;


class Manutentionnaire
{
private:
    Bouteille m_bouteille;
    int m_nb_bouteille_porte;
    int m_nb_action;
    Action m_futur_action;
public:
    void setFuturAction(Action action);
    Manutentionnaire(Bouteille bouteille);
};

#endif // MANUTENTIONNAIRE_H

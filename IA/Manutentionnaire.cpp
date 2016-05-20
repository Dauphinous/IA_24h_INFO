#include "Manutentionnaire.h"

Manutentionnaire::Manutentionnaire(Bouteille bouteille)
    :m_bouteille{bouteille}, m_nb_bouteille_porte{NB_BOUTEILLE_MAX}, m_nb_action{NB_MAX_ACTION} {}

void Manutentionnaire::setFuturAction(Action action)
{
    m_futur_action = action;
}


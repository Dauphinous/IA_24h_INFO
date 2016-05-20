#include <assert.h>
#include "Manutentionnaire.h"

Manutentionnaire::Manutentionnaire(Bouteille bouteille)
    :m_bouteille{bouteille}, m_nb_bouteille_porte{NB_BOUTEILLE_MAX}, m_nb_action{NB_MAX_ACTION} {}

void Manutentionnaire::setFuturAction(Action action)
{
    m_futur_action = action;
    m_actions.push_back(action);
}

void Manutentionnaire::poserBouteille()
{
    assert(m_nb_bouteille_porte <= 0);
    m_nb_bouteille_porte--;
}

void Manutentionnaire::remplirSac()
{
    assert(m_nb_bouteille_porte<NB_BOUTEILLE_MAX);
    m_nb_bouteille_porte++;
}

std::string Manutentionnaire::getPhraseAction() const
{
    std::string res;
    for(Action a : m_actions)
    {
        res+= getCodeAction(a);
    }
    return res;
}

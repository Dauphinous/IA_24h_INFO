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
    m_nb_bouteille_porte--;
}

void Manutentionnaire::remplirSac()
{
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

void Manutentionnaire::deplacerNord()
{
    m_position.second--;
}

void Manutentionnaire::deplacerSud()
{
    m_position.second++;
}

void Manutentionnaire::deplacerOuest()
{
    m_position.first--;
}

void Manutentionnaire::deplacerEst()
{
    m_position.first++;
}

void Manutentionnaire::faireAction()
{
    switch(m_futur_action)
    {
    case NORD:
        deplacerNord();
        break;
    case EST:
        deplacerEst();
        break;
    case SUD:
        deplacerSud();
        break;
    case OUEST:
        deplacerOuest();
        break;
    case POSER:
        poserBouteille();
        break;
    case REMPLIR:
        remplirSac();
        break;
    default:
        break;
    }
}

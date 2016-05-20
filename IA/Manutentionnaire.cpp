#include <assert.h>
#include "Manutentionnaire.h"

Manutentionnaire::Manutentionnaire(Bouteille bouteille,Salle * position)
    :m_bouteille{bouteille}, m_nb_bouteille_porte{NB_BOUTEILLE_MAX}, m_nb_action{NB_MAX_ACTION},m_position{position} {m_objectif.first = -1; m_objectif.second = -1;}

void Manutentionnaire::setFuturAction(Action action)
{
    m_futur_action = action;
    m_actions.push_back(action);
}

void Manutentionnaire::poserBouteille()
{
    m_nb_bouteille_porte--;
    m_position->poseBouteille();
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
    m_position = m_position->voisin(Nord);
}

void Manutentionnaire::deplacerSud()
{
    m_position = m_position->voisin(Sud);
}

void Manutentionnaire::deplacerOuest()
{
    m_position = m_position->voisin(Ouest);
}

void Manutentionnaire::deplacerEst()
{
    m_position = m_position->voisin(Est);
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

void Manutentionnaire::setObjectif(int x, int y)
{
    m_objectif.first = x;
    m_objectif.second = y;
}

std::pair<int,int> Manutentionnaire::getObjectif() const
{
    return m_objectif;
}


void Manutentionnaire::decodeEtAppliquerAction(std::string phrase)
{
    for(char c : phrase)
    {
        m_futur_action = codeToAction(c);
        faireAction();
    }
}

Bouteille Manutentionnaire::getColorBouteille() const
{
    return m_bouteille;
}

int Manutentionnaire::getNbActuelAction() const
{
    return m_nb_action;
}

int Manutentionnaire::getNbBouteillePorte() const
{
    return m_nb_bouteille_porte;
}

Salle * Manutentionnaire::getSalle() const
{
    return m_position;
}


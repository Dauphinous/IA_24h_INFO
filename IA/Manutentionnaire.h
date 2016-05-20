#ifndef MANUTENTIONNAIRE_H
#define MANUTENTIONNAIRE_H

#include "Bouteille.h"
#include "Action.h"
#include <vector>
#include <utility>
const int NB_BOUTEILLE_MAX = 10;
const int NB_MAX_ACTION = 7;


class Manutentionnaire
{
private:
    Bouteille m_bouteille;
    int m_nb_bouteille_porte;
    int m_nb_action;
    Action m_futur_action;
    std::vector<Action> m_actions;
    std::pair<int,int> m_position;
    std::pair<int, int> m_objectif;
public:
    void setFuturAction(Action action);
    Manutentionnaire(Bouteille bouteille, std::pair<int, int> position);
    void poserBouteille();
    void remplirSac();
    void deplacerNord();
    void deplacerEst();
    void deplacerSud();
    void deplacerOuest();
    void faireAction();
    std::string getPhraseAction() const;
    void setObjectif(int x, int y);
    std::pair<int,int> getObjectif() const;
    void decodeEtAppliquerAction(std::string phrase);
    Bouteille getColorBouteille() const;
    int getNbBouteillePorte() const;
    int getNbActuelAction() const;
    std::pair<int,int> getPosition() const;
};

#endif // MANUTENTIONNAIRE_H

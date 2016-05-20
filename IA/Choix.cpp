#include "Choix.h"
#include <algorithm>

Choix::Choix(string hote, int port)
{
    m_hote = hote;
    m_port = port;
    m_tcpGdOrdo = new TcpGrandOrdonnateurUnix();
    //ctor
}

Choix::~Choix()
{
    //dtor
}

int distEuclidienne(pair<int, int> pos1, pair<int, int> pos2)
{
    int result = 0;
    result = sqrt(abs(pow((pos1.first-pos2.first), 2) + pow((pos1.second-pos2.second), 2)));
    return result;
}

string Choix::IA()
{
    string choix = "";
    Manutentionnaire * manuNous = m_manutentionnaires[m_couleur_nous];
    int nbActionEffectue = 0;
    if(manuNous->getObjectif().first == -1)
    {
        if(manuNous->getNbBouteillePorte() == 0)
        {
            manuNous->setObjectif(m_cave->getEscalier()->getPosition().first, m_cave->getEscalier()->getPosition().second);
        }
        else
        {

        }
    }
    int nbCoupAvantObjectif = distEuclidienne(manuNous->getSalle()->getPosition(), manuNous->getObjectif());
    for(int i=0; i<nbCoupAvantObjectif && nbActionEffectue<8; i++)
    {
        if(manuNous->getSalle()->getPosition().first < manuNous->getSalle()->getPosition().first)
        {
            choix += "E";
            nbActionEffectue++;
        }
        else if(manuNous->getSalle()->getPosition().first < manuNous->getSalle()->getPosition().first)
        {
            choix += "O";
            nbActionEffectue++;
        }
        else if(manuNous->getSalle()->getPosition().second < manuNous->getSalle()->getPosition().second)
        {
            choix += "S";
            nbActionEffectue++;
        }
        else if(manuNous->getSalle()->getPosition().second < manuNous->getSalle()->getPosition().second)
        {
            choix += "N";
            nbActionEffectue++;
        }
    }
    for(int i=0; i<manuNous->getSalle()->nbEmplacementsLibres() && manuNous->getNbBouteillePorte()>0 && nbActionEffectue<8; i++)
    {
        if(m_cave->getEscalier()->getPosition().first == manuNous->getSalle()->getPosition().first && m_cave->getEscalier()->getPosition().second && manuNous->getSalle()->getPosition().second)
        {
            for(int i=0; nbActionEffectue<8; i++)
            {
                choix += "R";
                nbActionEffectue++;
            }
        }
        else
        {
            for(int i=0; i<manuNous->getSalle()->nbEmplacementsLibres() && manuNous->getNbBouteillePorte()>0 && nbActionEffectue<8; i++)
            {
                manuNous->poserBouteille();
                choix += "P";
                nbActionEffectue++;
            }
            if(nbActionEffectue<8)
            {
                choix += "I";
            }
        }
    }
    return choix;
}

void Choix::partie()
{
    int nb_ligne = 0;
    int nb_colonne = 0;
    string casiers;
    int nb_ordre;
    Bouteille couleur_active = ROUGE;
    // Finalisation du « create » du protocole du Grand Ordonnateur.
    // - connexion
    m_tcpGdOrdo->connexion(m_hote, m_port);
    // Réponse au « create » du protocole du Grand Ordonnateur.
    // - envoi du nom de notre équipe
    m_tcpGdOrdo->envoiChaine("CUMULONIMBUS");
    // - envoi de l'IUT où les membres de notre équipe étudient
    m_tcpGdOrdo->envoiChaine("IUT Bordeaux");
    // Initialisation du protocole du Grand Ordonnateur.
    // - réception du nombre de lignes de la cave
    nb_ligne = m_tcpGdOrdo->receptionEntier();
    // - réception du nombre de colonnes de la cave
    nb_colonne = m_tcpGdOrdo->receptionEntier();
    // - réception des casiers (nombre d'emplacements et position de
    //   l'escalier) de la cave
    casiers = m_tcpGdOrdo->receptionChaine();
    // - réception du nombre de manutentionnaires ; 3 ici
    m_nb_manutentionnaire = m_tcpGdOrdo->receptionEntier();
    // - réception de l'ordre (entre 1 et le nombre de manutentionnaires)
    //   dans lequel l'application singeant notre manutentionnaire joue ; 2
    //   ici
    nb_ordre = m_tcpGdOrdo->receptionEntier();

    if(nb_ordre == 1)
    {
        m_couleur_nous = ROUGE;
    }
    else if(nb_ordre == 2)
    {
        m_couleur_nous = BLANC;
    }
    else
    {
        m_couleur_nous = ROSE;
    }
    m_cave = new Cave(nb_ligne, nb_colonne, casiers);
    m_manutentionnaires[ROUGE] = new Manutentionnaire(ROUGE,m_cave->getEscalier());
    m_manutentionnaires[BLANC] = new Manutentionnaire{BLANC,m_cave->getEscalier()};
    if(m_nb_manutentionnaire == 3)
    {
        m_manutentionnaires[ROSE] = new Manutentionnaire(ROSE,m_cave->getEscalier());
    }
    // Premier tour de jeu :
    // - réception des actions du premier manutentionnaire
    m_tcpGdOrdo->receptionChaine();
    // - envoi de nos actions (comme deuxième manutentionnaire) ; ici, pour
    //   changer de l'envoi de nos actions du second tour de jeu, envoi des
    //   actions une à une

    while(true)
    {
        if(m_couleur_nous == couleur_active)
        {
            m_tcpGdOrdo->envoiChaine(IA());

            m_cave = new Cave(nb_ligne, nb_colonne, casiers);
            m_manutentionnaires[ROUGE] = new Manutentionnaire(ROUGE, m_cave->getEscalier());
            m_manutentionnaires[BLANC] = new Manutentionnaire(BLANC, m_cave->getEscalier());
            if(m_nb_manutentionnaire == 3)
            {
                m_manutentionnaires[ROSE] = new Manutentionnaire(ROSE, m_cave->getEscalier());
                //        m_manutentionnaires.insert(pair<Bouteille, Manutentionnaire>(Bouteille.ROSE, pair<int, int>(m_cave->getEscalier().first,m_cave->getEscalier().second)))
            }
            // Premier tour de jeu :
            // - réception des actions du premier manutentionnaire
            m_tcpGdOrdo->receptionChaine();
            // - envoi de nos actions (comme deuxième manutentionnaire) ; ici, pour
            //   changer de l'envoi de nos actions du second tour de jeu, envoi des
            //   actions une à une

            while(true)
            {
                if(m_couleur_nous == couleur_active)
                {
                    m_tcpGdOrdo->envoiChaine(IA());
                }
                else
                {
                    m_tcpGdOrdo->receptionChaine();
                }
            }

        }
    }
}

Salle * Choix::meilleureSalle(const Manutentionnaire & m) // Affecte a chaque case une valeur
{
    int negatif;
    int positif;

    Salle * choix = nullptr;
    int meilleurPoint = -1;

    for(vector<Salle *> v : m_cave->getSalles())
    {
        for(Salle * s : v)
        {
            negatif = (s->distanceParRapportA(m.getSalle()->getPosition()) + min(m.getNbBouteillePorte(), s->nbEmplacementsLibres())
                       + (s->distanceParRapportA(m.getSalle()->getPosition()) + min(m.getNbBouteillePorte(), s->nbEmplacementsLibres()))) % 7;

            positif = 4 * (s->getDistance() + 1) + min(m.getNbBouteillePorte(), s->nbEmplacementsLibres());

            if(positif -  negatif > meilleurPoint)
            {
                meilleurPoint = positif - negatif;
                choix = s;
            }
        }
    }

    return choix;
}

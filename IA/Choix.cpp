#include "Choix.h"

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
    Manutentionnaire manuNous = m_manutentionnaires[m_couleur_nous];
    int nbActionEffectue = 0;

    if(manuNous.getObjectif().first == -1)
    {
        if(manuNous.getNbBouteillePorte() == 0)
        {
            manuNous.setObjectif(m_cave.getEscalier().first, m_cave.getEscalier().second);
        }
        else
        {

        }
    }
        int nbCoupAvantObjectif = distEuclidienne(manuNous.getPosition(), manuNous.getObjectif());
        for(int i=0; i<nbCoupAvantObjectif && nbActionEffectue<8; i++)
        {
            if(manuNous.getPosition().first < manuNous.getPosition().first)
            {
                choix += "E";
                nbActionEffectue++;
            }
            else if(manuNous.getPosition().first < manuNous.getPosition().first)
            {
                choix += "O";
                nbActionEffectue++;
            }
            else if(manuNous.getPosition().second < manuNous.getPosition().second)
            {
                choix += "S";
                nbActionEffectue++;
            }
            else if(manuNous.getPosition().second < manuNous.getPosition().second)
            {
                choix += "N";
                nbActionEffectue++;
            }
        }
        if(m_cave.getEscalier().first == manuNous.getPosition().first && m_cave.getEscalier().second && manuNous.getPosition().second)
        {
            for(int i=0; nbActionEffectue<8;i++)
            {
                choix += "R";
                nbActionEffectue++;
            }
        }
        else
        {
            for(int i=0; i<m_cave.getSalle(manuNous.getPosition().second, manuNous.getPosition().first).nbEmplacementsLibres() && manuNous.getNbBouteillePorte()>0 && nbActionEffectue<8; i++)
            {
                manuNous.poserBouteille();
                choix += "P";
                nbActionEffectue++;
            }
            if(nbActionEffectue<8)
            {
                choix += "I";
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
    m_cave = new Cave(nb_ligne, nb_colonne, casier);
    m_manutentionnaires.insert(pair<Bouteille, Manutentionnaire>(Bouteille.ROUGE, pair<int, int>(m_cave->getEscalier().first,m_cave->getEscalier().second)));
    m_manutentionnaires.insert(pair<Bouteille, Manutentionnaire>(Bouteille.BLANC, pair<int, int>(m_cave->getEscalier().first,m_cave->getEscalier().second)));
    if(m_nb_manutentionnaire == 3)
    {
        m_manutentionnaires.insert(pair<Bouteille, Manutentionnaire>(Bouteille.ROSE, pair<int, int>(m_cave->getEscalier().first,m_cave->getEscalier().second)));
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
            tcpGdOrdo->envoiChaine(IA());
        }
        else
        {
            m_tcpGdOrdo->receptionChaine();
        }
    }

}

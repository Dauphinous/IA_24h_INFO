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

void Choix::partie()
{
    int nb_ligne = 0;
    int nb_colonne = 0;
    string casiers;
    int nb_ordre;
    Bouteille couleur_active = Bouteille.ROUGE;
    // Finalisation du « create » du protocole du Grand Ordonnateur.
    // - connexion
    m_tcpGdOrdo->connexion(hote, port);
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
    casiers = tcpGdOrdo->receptionChaine();
    // - réception du nombre de manutentionnaires ; 3 ici
    m_nb_manutentionnaire = tcpGdOrdo->receptionEntier();
    // - réception de l'ordre (entre 1 et le nombre de manutentionnaires)
    //   dans lequel l'application singeant notre manutentionnaire joue ; 2
    //   ici
    nb_ordre = tcpGdOrdo->receptionEntier();

    if(nb_ordre == 1){
        m_couleur_nous = Bouteille.ROUGE
    }
    else if(nb_ordre == 2){
        m_couleur_nous == Bouteille.BLANC;
    }
    else
    {
        m_couleur_nous == Bouteille.ROSE;
    }
    // Premier tour de jeu :
    // - réception des actions du premier manutentionnaire
    tcpGdOrdo->receptionChaine();
    // - envoi de nos actions (comme deuxième manutentionnaire) ; ici, pour
    //   changer de l'envoi de nos actions du second tour de jeu, envoi des
    //   actions une à une

    while(true){
        if(m_couleur_nous == couleur_active){

        }
        else{
            tcpGdOrdo->receptionChaine();
        }
    }

}

// #define _GLIBCXX_USE_NANOSLEEP

#include <iostream>
#include <chrono>
#include <thread>

#include "IllustrProtoc.h"
#include "TcpGrandOrdonnateurUnix.h"
//#include "TcpGrandOrdonnateurWinsock.h"

using namespace std;

/**
 * Création d'une illustration du protocole du Grand Ordonnateur.
 */
IllustrProtoc::IllustrProtoc(string hote, int port)
{
    this->hote = hote;
    this->port = port;
    tcpGdOrdo = new TcpGrandOrdonnateurUnix();
    // tcpGdOrdo = new TcpGrandOrdonnateurWinsock();
}

/**
 * Destruction d'une illustration du protocole du Grand Ordonnateur.
 */
IllustrProtoc::~IllustrProtoc()
{
    delete tcpGdOrdo;
}

/**
 * Scénario illustrant le protocole du Grand Ordonnateur.
 *
 * Cf. TcpGrandOrdonnateur{Unix,Winsock}.chaineValidePourTransmission pour
 * connaître les caractères autorisés par le protocole du Grand Ordonnateur.
 */
void IllustrProtoc::scenario()
{
    // Finalisation du « create » du protocole du Grand Ordonnateur.
    // - connexion
    tcpGdOrdo->connexion(hote, port);
    // Réponse au « create » du protocole du Grand Ordonnateur.
    // - envoi du nom de notre équipe
    tcpGdOrdo->envoiChaine("nom de notre equipe");
    // - envoi de l'IUT où les membres de notre équipe étudient
    tcpGdOrdo->envoiChaine("IUT ou nous etudions C++");
    // Initialisation du protocole du Grand Ordonnateur.
    // - réception du nombre de lignes de la cave
    tcpGdOrdo->receptionEntier();
    // - réception du nombre de colonnes de la cave
    tcpGdOrdo->receptionEntier();
    // - réception des casiers (nombre d'emplacements et position de
    //   l'escalier) de la cave
    tcpGdOrdo->receptionChaine();
    // - réception du nombre de manutentionnaires ; 3 ici
    tcpGdOrdo->receptionEntier();
    // - réception de l'ordre (entre 1 et le nombre de manutentionnaires)
    //   dans lequel l'application singeant notre manutentionnaire joue ; 2
    //   ici
    tcpGdOrdo->receptionEntier();
    // Premier tour de jeu :
    // - réception des actions du premier manutentionnaire
    tcpGdOrdo->receptionChaine();
    // - envoi de nos actions (comme deuxième manutentionnaire) ; ici, pour
    //   changer de l'envoi de nos actions du second tour de jeu, envoi des
    //   actions une à une
    for (char& action : string("EPPOOPP"))
    {
        tcpGdOrdo->envoiCaractere(action);
    }
    // - réception des actions du troisième manutentionnaire
    tcpGdOrdo->receptionChaine();
    // Second tour de jeu :
    // - réception des actions du premier manutentionnaire
    tcpGdOrdo->receptionChaine();
    // - envoi de nos actions (comme deuxième manutentionnaire) ; ici, pour
    //   changer de l'envoi de nos actions du premier tour de jeu, envoi
    //   simultané des actions
    tcpGdOrdo->envoiChaine("EREPEI");
    // - réception des actions du troisième manutentionnaire
    tcpGdOrdo->receptionChaine();
    // Remarque : le reste du code de cette méthode est purement esthétique
    // puisque l'application va être arrêtée par un « destroy » du protocole
    // du Grand Ordonnateur.
    // - attente
    // TODO : attente ; this_thread::sleep_for(chrono::seconds(1 * 60));
    // - déconnexion
    try
    {
        tcpGdOrdo->deconnexion();
    }
    catch (exception& e)
    {
        // Qu'importe si le serveur s'est arrêté avant le client.
    }
}


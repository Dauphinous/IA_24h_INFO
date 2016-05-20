// #define _GLIBCXX_USE_NANOSLEEP

#include <iostream>
#include <chrono>
#include <thread>

#include "IllustrProtoc.h"
#include "TcpGrandOrdonnateurUnix.h"
//#include "TcpGrandOrdonnateurWinsock.h"

using namespace std;

/**
 * Cr�ation d'une illustration du protocole du Grand Ordonnateur.
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
 * Sc�nario illustrant le protocole du Grand Ordonnateur.
 *
 * Cf. TcpGrandOrdonnateur{Unix,Winsock}.chaineValidePourTransmission pour
 * conna�tre les caract�res autoris�s par le protocole du Grand Ordonnateur.
 */
void IllustrProtoc::scenario()
{
    // Finalisation du � create � du protocole du Grand Ordonnateur.
    // - connexion
    tcpGdOrdo->connexion(hote, port);
    // R�ponse au � create � du protocole du Grand Ordonnateur.
    // - envoi du nom de notre �quipe
    tcpGdOrdo->envoiChaine("nom de notre equipe");
    // - envoi de l'IUT o� les membres de notre �quipe �tudient
    tcpGdOrdo->envoiChaine("IUT ou nous etudions C++");
    // Initialisation du protocole du Grand Ordonnateur.
    // - r�ception du nombre de lignes de la cave
    tcpGdOrdo->receptionEntier();
    // - r�ception du nombre de colonnes de la cave
    tcpGdOrdo->receptionEntier();
    // - r�ception des casiers (nombre d'emplacements et position de
    //   l'escalier) de la cave
    tcpGdOrdo->receptionChaine();
    // - r�ception du nombre de manutentionnaires ; 3 ici
    tcpGdOrdo->receptionEntier();
    // - r�ception de l'ordre (entre 1 et le nombre de manutentionnaires)
    //   dans lequel l'application singeant notre manutentionnaire joue ; 2
    //   ici
    tcpGdOrdo->receptionEntier();
    // Premier tour de jeu :
    // - r�ception des actions du premier manutentionnaire
    tcpGdOrdo->receptionChaine();
    // - envoi de nos actions (comme deuxi�me manutentionnaire) ; ici, pour
    //   changer de l'envoi de nos actions du second tour de jeu, envoi des
    //   actions une � une
    for (char& action : string("EPPOOPP"))
    {
        tcpGdOrdo->envoiCaractere(action);
    }
    // - r�ception des actions du troisi�me manutentionnaire
    tcpGdOrdo->receptionChaine();
    // Second tour de jeu :
    // - r�ception des actions du premier manutentionnaire
    tcpGdOrdo->receptionChaine();
    // - envoi de nos actions (comme deuxi�me manutentionnaire) ; ici, pour
    //   changer de l'envoi de nos actions du premier tour de jeu, envoi
    //   simultan� des actions
    tcpGdOrdo->envoiChaine("EREPEI");
    // - r�ception des actions du troisi�me manutentionnaire
    tcpGdOrdo->receptionChaine();
    // Remarque : le reste du code de cette m�thode est purement esth�tique
    // puisque l'application va �tre arr�t�e par un � destroy � du protocole
    // du Grand Ordonnateur.
    // - attente
    // TODO : attente ; this_thread::sleep_for(chrono::seconds(1 * 60));
    // - d�connexion
    try
    {
        tcpGdOrdo->deconnexion();
    }
    catch (exception& e)
    {
        // Qu'importe si le serveur s'est arr�t� avant le client.
    }
}


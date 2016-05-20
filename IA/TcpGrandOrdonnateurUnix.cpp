#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "TcpGrandOrdonnateurUnix.h"

using namespace std;

/**
 * Cr�ation d'une interface pour le protocole du Grand Ordonnateur.
 */
TcpGrandOrdonnateurUnix::TcpGrandOrdonnateurUnix()
{
    sock = -1;
}

/**
 * Destruction d'une interface pour le protocole du Grand Ordonnateur.
 */
TcpGrandOrdonnateurUnix::~TcpGrandOrdonnateurUnix()
{
}

/**
 * Connexion au serveur.
 */
void TcpGrandOrdonnateurUnix::connexion(string hote, int port)
{
    struct sockaddr_in adrServeur;
    socklen_t lg_adr_serveur = sizeof(adrServeur);
    struct hostent* serveur;
    stringstream ss;
    ss << port;
    const string ECHEC_CONNEXION = "La connexion � l'h�te " + hote
                                   + " avec le port " + ss.str()
                                   + " n'est pas possible : ";
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        sock = -1;
        throw invalid_argument(ECHEC_CONNEXION + "ouverture du socket.");
    }
    serveur = gethostbyname(hote.c_str());
    if (serveur == NULL)
    {
        sock = -1;
        throw invalid_argument(ECHEC_CONNEXION + "nom d'h�te inexistant.");
    }
    adrServeur.sin_family = AF_INET;
    adrServeur.sin_port = htons(port);
    adrServeur.sin_addr = *(struct in_addr *) serveur->h_addr;
    if (connect(sock, (struct sockaddr *) &adrServeur, lg_adr_serveur) < 0)
    {
        sock = -1;
        throw invalid_argument(ECHEC_CONNEXION + "connexion.");
    }
}

/**
 * Envoi d'un entier au serveur.
 */
void TcpGrandOrdonnateurUnix::envoiEntier(int entier)
{
    envoiCaractere((char) entier);
}

/**
 * Envoi d'un caract�re au serveur.
 */
void TcpGrandOrdonnateurUnix::envoiCaractere(char caractere)
{
    testeSocket();
    const int NB_CARACT_A_ENVOYER = 1;
    char buffer[NB_CARACT_A_ENVOYER+1];
    bzero(buffer, NB_CARACT_A_ENVOYER+1);
    buffer[0] = caractere;
    int nbCaractEnvoyes = write(sock, buffer, NB_CARACT_A_ENVOYER);
    if (nbCaractEnvoyes < 0)
    {
        deconnexion();
        throw invalid_argument("L'envoi du caract�re n'a pas �t� possible.");
    }
    if (nbCaractEnvoyes > NB_CARACT_A_ENVOYER)
    {
        deconnexion();
        throw invalid_argument("Trop de caract�res ont �t� envoy�s !");
    }
    if (nbCaractEnvoyes < NB_CARACT_A_ENVOYER) // pas de flush() !
    {
        deconnexion();
        throw invalid_argument("La connexion (ferm�e ?) n'a pas permis d'envoyer le caract�re.");
    }
}

/**
 * Envoi d'une cha�ne de caract�res au serveur.
 */
void TcpGrandOrdonnateurUnix::envoiChaine(string chaine)
{
    if (chaineValidePourTransmission(chaine))
    {
        for (char& caractere : chaine)
        {
            envoiCaractere(caractere);
        }
        envoiCaractere(SEPARATEUR);
    }
    else
    {
        throw invalid_argument("La cha�ne de caract�res � envoyer � " + chaine
                               + " � n'est pas valide.");
    }
}

/**
 * Teste si une cha�ne de caract�res est valide (dans un certain intervalle
 * de la table ASCII (cf. https://fr.wikipedia.org/wiki/
 * American_Standard_Code_for_Information_Interchange)) pour �tre envoy�e,
 * c'est-�-dire si elle ne contient pas de caract�re sp�cial.
 */
bool TcpGrandOrdonnateurUnix::chaineValidePourTransmission(string chaine)
{
    for (char& caractere : chaine)
    {
        int entier = (int) caractere;
        if (entier < CARACTERE_MINIMAL_INCLUS || entier >= CARACTERE_MAXIMAL_EXCLU)
        {
            return false;
        }
    }
    return true;
}

/**
 * R�ception d'un entier depuis le serveur.
 */
int TcpGrandOrdonnateurUnix::receptionEntier()
{
    return (int) receptionCaractere();
}

/**
 * R�ception d'un caract�re depuis le serveur.
 */
char TcpGrandOrdonnateurUnix::receptionCaractere()
{
    testeSocket();
    const int NB_CARACT_A_RECEVOIR = 1;
    char buffer[NB_CARACT_A_RECEVOIR+1];
    bzero(buffer, NB_CARACT_A_RECEVOIR+1);
    int nbCaractRecus = read(sock, buffer, NB_CARACT_A_RECEVOIR);
    if ( nbCaractRecus < 0 )
    {
        deconnexion();
        throw invalid_argument("La connexion en r�ception a �chou�.");
    }
    if ( nbCaractRecus > NB_CARACT_A_RECEVOIR )
    {
        deconnexion();
        throw invalid_argument("Trop de caract�res ont �t� re�us !");
    }
    if ( nbCaractRecus < NB_CARACT_A_RECEVOIR )
    {
        deconnexion();
        throw invalid_argument("La connexion (ferm�e ?) n'a pas permis de recevoir le caract�re.");
    }
    return buffer[0];
}

/**
 * R�ception d'une cha�ne de caract�res depuis le serveur.
 */
string TcpGrandOrdonnateurUnix::receptionChaine()
{
    testeSocket();
    string chaine = "";
    bool separateurRecu = false;
    bool ok = true;
    while (ok && !separateurRecu)
    {
        char recu = receptionCaractere();
        ok = (recu != (char) -1); // a priori toujours vrai
        if (! ok)
        {
            deconnexion();
            throw invalid_argument("Au cours de la r�ception d'une cha�ne de caract�res, l'un d'eux n'est pas valide.");
        }
        separateurRecu = (recu == SEPARATEUR);
        if (ok && !separateurRecu)
        {
            chaine += recu; // string(1, recu);
        }
    }
    return chaine;
}

/**
 * D�connexion du serveur.
 */
void TcpGrandOrdonnateurUnix::deconnexion()
{
    testeSocket();
    close(sock);
    sock = -1;
}

/**
 * Teste si le socket est initialis� ; sinon, arr�t du programme.
 */
void TcpGrandOrdonnateurUnix::testeSocket()
{
    if (sock == -1)
    {
        cout << "Le socket n'est pas initialis�." << endl;
        cout.flush();
        exit(EXIT_FAILURE);
    }
}

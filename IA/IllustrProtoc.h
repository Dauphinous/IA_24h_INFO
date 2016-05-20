#ifndef ILLUSTRPROTOC_H
#define ILLUSTRPROTOC_H

#include <string>

/**
 * Illustration du protocole du Grand Ordonnateur, fournie par le gentil
 * organisateur de l'�preuve de d�veloppement des 24h IUT Informatique de
 * Bordeaux 2016 (OG&OG)
 *
 * Auteur : Olivier
 */

using namespace std;

class TcpGrandOrdonnateurUnix;
// class TcpGrandOrdonnateurWinsock;

class IllustrProtoc
{
public:
    /** Cr�ation d'une illustration du protocole du Grand Ordonnateur. */
    IllustrProtoc(string, int);
    /** Destruction de l'illustration du protocole du Grand Ordonnateur. */
    virtual ~IllustrProtoc();
    /** Sc�nario illustrant le protocole du Grand Ordonnateur. */
    void scenario();
protected:
private:
    /** H�te du Grand Ordonnateur. */
    string hote;
    /** Port du Grand Ordonnateur. */
    int port = -1;
    /** Interface pour le protocole du Grand Ordonnateur. */
    TcpGrandOrdonnateurUnix* tcpGdOrdo = nullptr;
    //TcpGrandOrdonnateurWinsock* tcpGdOrdo = nullptr;
};

#endif // ILLUSTRPROTOC_H

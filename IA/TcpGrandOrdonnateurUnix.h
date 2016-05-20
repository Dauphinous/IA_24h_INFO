#ifndef TCPGRANDORDONNATEURUNIX_H
#define TCPGRANDORDONNATEURUNIX_H

/**
 * Remarques du gentil organisateur destinées aux compétiteurs :
 * - utilisez cette classe pour communiquer avec le Grand Ordonnateur
 * - ne changez rien au code de cette classe
 */

/**
 * Interface pour le protocole du Grand Ordonnateur.
 *
 * Auteur : Olivier
 */

using namespace std;

class TcpGrandOrdonnateurUnix
{
public:
    /** Création d'une interface pour le protocole du Grand Ordonnateur. */
    TcpGrandOrdonnateurUnix();
    /** Destruction d'une interface pour le protocole du Grand Ordonnateur. */
    virtual ~TcpGrandOrdonnateurUnix();
    /** Séparateur entre les chaînes de caractères échangées par TCP. */
    static const char SEPARATEUR = '~';
    /** Caractère minimal (inclus) autorisé par le protocole du Grand Ordonnateur. */
    static const int CARACTERE_MINIMAL_INCLUS = 32;
    /** Caractère maximal (exclu) autorisé par le protocole du Grand Ordonnateur. */
    static const int CARACTERE_MAXIMAL_EXCLU = (int) SEPARATEUR;
    /** Connexion au serveur. */
    void connexion(string, int);
    /** Envoi d'un entier au serveur. */
    void envoiEntier(int);
    /** Envoi d'un caractère au serveur. */
    void envoiCaractere(char);
    /** Envoi d'une chaîne de caractères au serveur. */
    void envoiChaine(string);
    /** Réception d'un entier depuis le serveur. */
    int receptionEntier();
    /** Réception d'un caractère depuis le serveur. */
    char receptionCaractere();
    /** Réception d'une chaîne de caractères depuis le serveur. */
    string receptionChaine();
    /** Déconnexion du serveur. */
    void deconnexion();
protected:
private:
    /** Socket. */
    int sock = -1;
    /** Teste si une chaîne de caractères est valide (dans un certain intervalle de la table ASCII (cf. https://fr.wikipedia.org/wiki/ American_Standard_Code_for_Information_Interchange)) pour être envoyée, c'est-à-dire si elle ne contient pas de caractère spécial. */
    bool chaineValidePourTransmission(string);
    /** Teste si le socket est initialisé ; sinon, arrêt du programme. */
    void testeSocket();
};

#endif // TCPGRANDORDONNATEURUNIX_H

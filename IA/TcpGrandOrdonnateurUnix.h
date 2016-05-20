#ifndef TCPGRANDORDONNATEURUNIX_H
#define TCPGRANDORDONNATEURUNIX_H

/**
 * Remarques du gentil organisateur destin�es aux comp�titeurs :
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
    /** Cr�ation d'une interface pour le protocole du Grand Ordonnateur. */
    TcpGrandOrdonnateurUnix();
    /** Destruction d'une interface pour le protocole du Grand Ordonnateur. */
    virtual ~TcpGrandOrdonnateurUnix();
    /** S�parateur entre les cha�nes de caract�res �chang�es par TCP. */
    static const char SEPARATEUR = '~';
    /** Caract�re minimal (inclus) autoris� par le protocole du Grand Ordonnateur. */
    static const int CARACTERE_MINIMAL_INCLUS = 32;
    /** Caract�re maximal (exclu) autoris� par le protocole du Grand Ordonnateur. */
    static const int CARACTERE_MAXIMAL_EXCLU = (int) SEPARATEUR;
    /** Connexion au serveur. */
    void connexion(string, int);
    /** Envoi d'un entier au serveur. */
    void envoiEntier(int);
    /** Envoi d'un caract�re au serveur. */
    void envoiCaractere(char);
    /** Envoi d'une cha�ne de caract�res au serveur. */
    void envoiChaine(string);
    /** R�ception d'un entier depuis le serveur. */
    int receptionEntier();
    /** R�ception d'un caract�re depuis le serveur. */
    char receptionCaractere();
    /** R�ception d'une cha�ne de caract�res depuis le serveur. */
    string receptionChaine();
    /** D�connexion du serveur. */
    void deconnexion();
protected:
private:
    /** Socket. */
    int sock = -1;
    /** Teste si une cha�ne de caract�res est valide (dans un certain intervalle de la table ASCII (cf. https://fr.wikipedia.org/wiki/ American_Standard_Code_for_Information_Interchange)) pour �tre envoy�e, c'est-�-dire si elle ne contient pas de caract�re sp�cial. */
    bool chaineValidePourTransmission(string);
    /** Teste si le socket est initialis� ; sinon, arr�t du programme. */
    void testeSocket();
};

#endif // TCPGRANDORDONNATEURUNIX_H

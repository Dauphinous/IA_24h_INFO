#ifndef CHOIX_H
#define CHOIX_H


class Choix
{
    public:

        Choix(string, int);
        void partie();
        virtual ~Choix();
    protected:
        string m_hote;
        int m_port;
        Cave *m_cave;
        TcpGrandOrdonnateurUnix *m_tcpGdOrdo = nullptr;
        int m_nb_manutentionnaire;
        Bouteille m_couleur_nous;
    private:
};

#endif // CHOIX_H

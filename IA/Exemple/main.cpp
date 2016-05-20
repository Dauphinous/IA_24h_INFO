/*
 * Auteur : Olivier
 */

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cerrno>

#include "IllustrProtoc.h"

// using namespace std;

// TODO : accenter les messages

/**
 * Programme principal.
 */
int main(int argc, char** argv)
{
    time_t maintenant = time(0);
    std::cout << "Démarrage de notre application C++ ce "
              << ctime(&maintenant); // << "." << endl;
    std::cout.flush();
    // « create » du protocole du Grand Ordonnateur.
    const std::string USAGE = std::string("\n\tUsage : ") + std::string(argv[0])
                              + std::string(" <hôte> <port>");
    if (argc != 3)
    {
        std::cout << "Nombre de paramètres incorrect." << USAGE << std::endl;
        std::cout.flush();
        std::exit(EXIT_FAILURE);
    }
    std::string hote = std::string(argv[1]);
    int port = (int) strtol(argv[2], NULL, 10); // mieux que atoi(argv[2]);
    if (port == 0 || errno == ERANGE)
    {
        std::cout << "Le port doit être un entier et ne pas être trop grand pour être un port correct."
                  << USAGE << std::endl;
        std::cout.flush();
        std::exit(EXIT_FAILURE);
    }
    IllustrProtoc* illustrProtoc = new IllustrProtoc(hote, port);
    if (illustrProtoc == nullptr)
    {
        std::cout << "Erreur lors de la création d'une illustration du protocole du Grand Ordonnateur."
                  << std::endl;
        std::cout.flush();
        std::exit(EXIT_FAILURE);
    }
    try
    {
        illustrProtoc->scenario();
    }
    catch (std::exception& e)
    {
        std::cout << "Erreur lors de l'utilisation d'une illustration du protocole du Grand Ordonnateur."
                  << std::endl;
        std::cout.flush();
        std::cerr << e.what() << std::endl;
        std::cerr.flush();
        std::exit(EXIT_FAILURE);
    }
    delete illustrProtoc;
    std::exit(EXIT_SUCCESS);
    // return 0;
}

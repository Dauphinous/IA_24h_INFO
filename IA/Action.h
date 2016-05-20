#ifndef ACTION_H
#define ACTION_H

#include <string>

enum Action{NORD,EST,SUD,OUEST,POSER,REMPLIR,INTERROMPRE};

std::string getCodeAction(Action a);

#endif // ACTION_H

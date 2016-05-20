#ifndef ACTION_H
#define ACTION_H

#include <string>

enum Action{NORD,EST,SUD,OUEST,POSER,REMPLIR,INTERROMPRE};

std::string getCodeAction(Action a);

Action codeToAction(char s);

#endif // ACTION_H

#ifndef ACTION_H
#define ACTION_H

#include <string>

enum Action{NORD,EST,SUD,OUEST,POSER,REMPLIR,INTERROMPRE};

std::string getCode(Action a)
{
    switch (a)
    {
    case NORD:
        return "N";
        break;
    case EST:
        return "E";
        break;
    case SUD:
        return "S";
        break;
    case OUEST:
        return "O";
        break;
    case POSER:
        return "P";
        break;
    case REMPLIR:
        return "R";
        break;
    case INTERROMPRE:
        return "I";
        break;
    }
}

#endif // ACTION_H

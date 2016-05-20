#include "Action.h"

std::string getCodeAction(Action a)
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

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
    default:
        break;
    }
}

Action codeToAction(char s)
{
    switch (s)
    {
    case 'N':
        return NORD;
        break;
    case 'E':
        return EST;
        break;
    case 'S':
        return SUD;
        break;
    case 'O':
        return OUEST;
        break;
    case 'P':
        return POSER;
        break;
    case 'R':
        return REMPLIR;
        break;
    case 'I':
        return INTERROMPRE;
        break;
    default:
        break;
    }
}

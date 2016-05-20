#!/bin/bash

#
# ce script crée un fichier de projet .pro (pour qt)
# à partir des fichiers *.cpp et *.h du répertoire courant
#

PROJECT=$(basename $PWD).pro

#
# mode d'emploi :
# 1. se mettre dans le répertoire du projet
# 2. lancer ce script
#



if [ -e $PROJECT ]
then
    echo "le fichier $PROJECT  existe déja"
    echo "détruisez-le vous-même si vous y tenez"
    echo "moi je n'y touche pas."
    exit 0
fi

SOURCES=$(echo *.c*)
HEADERS=$(echo *.h)

if grep -q SFML *.cpp *h 2>/dev/null
then
    SFMLLIBS="-lsfml-graphics -lsfml-window -lsfml-system"
fi


cat > $PROJECT <<EOF
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += $SOURCES

HEADERS += $HEADERS

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
LIBS           += $SFMLLIBS 

# décommenter pour les tests BOOST
#LIBS          +=  -lboost_unit_test_framework
EOF

echo "le fichier $PROJECT a été créé"

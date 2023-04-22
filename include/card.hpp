#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <unistd.h>

#define N_CARDS 52 //nombre de carte fixe = 52

using namespace std;

enum Rang {Deuce , Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};
enum Couleur  {Piques , Coeurs, Carreaux, Trefles};

class card{
    private:
        Rang rang;
        Couleur couleur; 
    public:
        card() = default;
        card(Couleur, Rang);
        int getRang();//retourne le Rang de la carte
        int getCouleur();//retourne la Couleur de la carte
        void print();//affiche la carte
};

#endif
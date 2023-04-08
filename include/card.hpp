#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <unistd.h>

#define N_CARDS 52

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
        int getRang();
        int getCouleur();
        void print();
};

#endif
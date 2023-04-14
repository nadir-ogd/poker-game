#ifndef DEALER_HPP
#define DEALER_HPP

#include "./player.hpp"

#define SB 2
#define BB 2*SB

class game{
    private:
    vector<card> cards;//cartes initialisées
    vector<card> deck;//cartes mélangées
    vector<player> players;
    void shuffle();
    void blinds(player &p1, player &p2);
    void distribuer_player(player &p);
    void hitBoard();
    void prefflop(int);
    void encheres(int);
    void determine_winner(hand& hand_board);
    int lastMise;
    bool miseAvant = false;
    
    public:
    game();
    void play();
    int nbJoueurs;
    float price_pot;
    int indSB;
    int indBB;
    hand hand_board;//les cartes communes sont accessibles par tous le monde
};

#endif
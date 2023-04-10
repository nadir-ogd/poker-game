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
    bool miser_avant(int i);
    void print_cards();
    void print_deck();
    void prefflop(int);
    void encheres(int);
    void determine_winner(hand& hand_dealer);
    int lastMise;
    bool miseAvant = false;
    float price_pot;
    int indSB;
    int indBB;
    
    public:
    game();
    hand hand_board;//les cartes communes sont accessibles par tous le monde
    int nbJoueurs;
    void play();
};

#endif
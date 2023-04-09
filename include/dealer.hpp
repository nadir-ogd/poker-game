#ifndef DEALER_HPP
#define DEALER_HPP

#include "./player.hpp"

class dealer{
    private:
    vector<card> cards;//cartes initialisées
    vector<card> deck;//cartes mélangées
    vector<player> players;
    int lastMise;
    void shuffle();
    void blinds(player &p1, player &p2);
    void distribuer_player(player &p);
    void hitBoard();
    bool miser_avant(int i);
    bool player_in_game();
    void print_cards();
    void print_deck();
    void encheres(int);
    int determine_winner(hand& hand_dealer);
    
    public:
    dealer();
    hand hand_dealer;//les cartes communes sont accessibles par tous le monde
    int nbJoueurs;
    void play();
};

#endif
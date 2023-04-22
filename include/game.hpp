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
    void shuffle();//m"lange les carte initialisées
    void blinds(player &p1, player &p2);//seléctionne les deux joueurs qui paient la SB, BB chaque round
    void distribuer_player(player &p);//distribue 2 cartes pour chaque joueur, chaque début de round
    void hitBoard();//tirer une carte et la mettre sur le board
    void prefflop(int);//déroulement de Prefflop
    void encheres(int);//déroulement des 3 tours (fflop, tour, river)
    void determine_winner(hand& hand_board);//déterminer le(s) gagnants du round
    int lastMise;//la derniere valeur de mise faite 
    bool miseAvant = false;//retourne true si une mise a été faite, false sinon
    
    public:
    game();
    void play();//focntion globale de déroulement de la partie Poker
    int nbJoueurs;//nombre joueurs sur la table
    float price_pot;//la somme d'argent dans le pot
    int indSB;//indice de joueur qui paye la Small Blind
    int indBB;//indice de joueur qui paye la Big Blind
    hand hand_board;//les cartes communes sont accessibles par tous le monde (5 cartes)
};

#endif
#ifndef HAND_HPP
#define HAND_HPP

#include "./card.hpp"

class hand{
    private:
        vector<card> hand_cards;//les cartes de main (soit 2 cartes si main du joueur, soit 5 si main du board)
    public:
        hand() = default;
        //les 11 combinaisons possibles true si un joueur a le combinaison, false sinon
        bool is_royal_flush(hand&);
        bool is_straight_flush(hand&);
        bool is_4_of_a_kind(hand&);
        bool is_full_house(hand&);
        bool is_flush(hand&);
        bool is_straight(hand&);
        bool is_3_of_a_kind(hand&);
        bool is_two_pairs(hand&);
        bool is_one_pair(hand&);
        void high_card(hand&);
        void setCards(card &c);//ajoute la carte c dans la main
        card get_card(int ind);//retourne la carte
        void print_hand();//affiche une main
        void clear_hand();//vide une main(fin round)
};
#endif
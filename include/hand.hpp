#ifndef HAND_HPP
#define HAND_HPP

#include "./card.hpp"

class hand{
    private:
        vector<card> hand_cards;
    public:
        hand() = default;
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
        void setCards(card &c);
        card get_card(int ind);
        // void set_score(int val);
        // int get_score();
        void print_hand();
};
#endif
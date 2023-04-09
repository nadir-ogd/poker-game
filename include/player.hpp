#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "./hand.hpp"
#include "./card.hpp"

class player{
    private:
        float credit;
        int mise;
        hand hand_player;
  
    public:
        player(float);
        bool in_game; 
        bool is_bet = false;
        bool is_check = false;
        bool is_raise = false;
        bool is_call = false;
        void hit(card&);
        void bet(int);
        void check();
        void fold();
        void call(int);
        void raise(int);
        void print_player(int);
        void print_card();
        hand get_hand();
        float get_credit();
        void update_credit(float);
};

#endif

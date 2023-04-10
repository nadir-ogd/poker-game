#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "./hand.hpp"
#include "./card.hpp"

class player{
    private:
        float credit;
        int mise;
        int score = 0;
        hand hand_player;
  
    public:
        player(float);
        bool in_game; 
        void hit(card&);
        void bet(int);
        void check();
        void fold();
        void call(int);
        void raise(int);
        void print_player();
        void print_card();
        hand get_hand();
        float get_credit();
        void update_credit(float);
        void setScore(int val);
        int getScore();
};

#endif

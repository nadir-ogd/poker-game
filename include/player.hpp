#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "./hand.hpp"
#include "./card.hpp"

class player{
    private:
        float credit;
        int mise;
        int score = 0;//utilisé pour savoir la combiaison que le player possede
        hand hand_player;
  
    public:
        player(float);
        bool in_game; 
        bool all_in;
        void hit(card&);
        void bet(int);
        void fold();
        void allIn();
        void call(int);
        void raise(int);
        void print_player();
        void player_clear_hand();
        void print_card();
        hand get_hand();
        float get_credit();
        void update_credit(float);
        void setScore(int val);
        int getScore();
        int getMise();
};

#endif

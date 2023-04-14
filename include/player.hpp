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
        void update_credit(float);
        void setScore(int val);
        hand get_hand();
        float get_credit();
        int getScore();
        int getMise();
        void print_player();
        void print_card();
        void player_clear_hand();

};

#endif

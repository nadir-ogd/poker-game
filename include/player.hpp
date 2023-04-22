#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "./hand.hpp"
#include "./card.hpp"

class player{
    private:
        float credit;
        int mise;
        int score = 0;//utilisé pour savoir la combianison que le player possede
        hand hand_player;//main du joueur
  
    public:
        player(float);
        bool in_game;//retourne true si le joueur est toujours en jeu, false sinon
        bool all_in;//retourne true si le joueur a fait un all-in, false sinon
        void hit(card&);//une carte est distribuée au joueur(et ajoutée a sa main)
        void bet(int);//le joueur mise
        void fold();//le joueur se couche
        void allIn();//le joueur fait un all-in
        void call(int);//le joueur suit la mise
        void raise(int);//le joueur augmente la mise
        void update_credit(float);//dans le cas ou le joueur gagne, son crédit sera mis à jour
        void setScore(int val);//val est l'indice de la combinaison que le joueur possede qui sera stocké dans score
        hand get_hand();//retourne la main du joueur
        float get_credit();//retourne le crédit du joueur
        int getScore();//retourne l'indice de la combinaison que le joueur possede
        int getMise();//retourne la derniere mise faite par le joueur
        void print_player();//affiche le joueur
        void print_card();//affiche la main du joueur
        void player_clear_hand();//vider la main du joueur

};

#endif

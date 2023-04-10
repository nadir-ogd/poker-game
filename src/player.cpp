#include "../include/player.hpp"

player::player(float val)
{
    if(val <= 0){
        cout << "Votre crédit est insuffisant, vous ne pouvez pas jouer ! "<< endl;
        exit(EXIT_FAILURE);
    }
    credit = val;
    mise = 0;
    score = 0;
    in_game = true;
    is_bet = false;
}

void player::bet(int val)
{
    if(val > credit){
        cout << "Votre crédit est insuffisant, vous ne pouvez pas miser !"<< endl;
        exit(EXIT_FAILURE);
    }
    credit -= val;
    mise += val;     
    is_bet = true;   
}

void player::hit(card &c)
{
    hand_player.setCards(c);
}

void player::check()
{
    is_bet = false;
    is_check = true;
}

void player::fold()
{
    //is_bet = false;
    in_game = false;
}

void player::call(int val)
{
    if(val > credit){
        cout << "Votre crédit est insuffisant, vous ne pouvez pas miser !"<< endl;
        exit(EXIT_FAILURE);
    }
    credit -= val;
    mise += val;     
    is_bet = true;      
}

void player::raise(int val)
{
    if(val > credit){
        cout << "Votre crédit est insuffisant, vous ne pouvez pas miser !"<< endl;
        exit(EXIT_FAILURE);
    }
    credit -= val;
    mise += val;     
    is_bet = true;   
}

void player::print_card()
{
    hand_player.print_hand();
}

hand player::get_hand()
{
    return hand_player;
}

void player::print_player()
{
    cout << "cartes " << endl; print_card();
    cout << "mise " << mise << endl;
    cout << "credit " << credit << endl;
}

float player::get_credit()
{
    return credit;
}

void player::update_credit(float val)
{
    credit+=val;
}

void player::setScore(int val)
{
    score += val;
}

int player::getScore()
{
    return score;
}

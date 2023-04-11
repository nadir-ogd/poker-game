#include "../include/player.hpp"
#include "../include/game.hpp"

player::player(float val) {
    if (val <= 0) {
        cout << "Votre crédit est insuffisant, vous ne pouvez pas jouer !" << endl;
        return;
    }
    
    credit = val;
    mise = 0;
    score = 0;
    in_game = true;
    all_in = false;

}


void player::bet(int amount)
{
    if (amount > credit) {
        cout << "Erreur : la mise ne peut pas être supérieure à votre crédit actuel." << endl;
        do {
            cout << "Entrez une nouvelle mise ou tapez 0 pour fold : ";
            cin >> amount;
            if (amount == 0) {
                in_game = false;
                break;
            }
        } while (amount > credit);
    }
    else if (amount < SB) {
        cout << "Erreur : la mise ne peut pas être inferieure au Small Blind :" << SB << endl;
        do {
            cout << "Entrez une nouvelle mise ou tapez 0 pour fold : ";
            cin >> amount;
            if (amount == 0) {
                in_game = false;
                break;
            }
        } while (amount >= SB);
    }
    if (in_game) {
        credit -= amount;
        mise += amount;
    }
}

void player::hit(card &c)
{
    hand_player.setCards(c);
}


void player::fold()
{
    in_game = false;
}

void player::call(int val)
{
      if (val > credit) {
        cout << "Erreur : la mise ne peut pas être supérieure à votre crédit actuel." << endl;
        do {
            cout << "Entrez une nouvelle mise ou tapez 0 pour fold : ";
            cin >> val;
            if (val == 0) {
                in_game = false;
                break;
            }
        } while (val > credit);
    }
    if (in_game) {
        credit -= val;
        mise += val;
    }     
}

void player::raise(int val)
{
       if (val > credit) {
        cout << "Erreur : la mise ne peut pas être supérieure à votre crédit actuel." << endl;
        do {
            cout << "Entrez une nouvelle mise ou tapez 0 pour fold : ";
            cin >> val;
            if (val == 0) {
                in_game = false;
                break;
            }
        } while (val > credit);
    }
    if (in_game) {
        credit -= val;
        mise += val;
    }
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
    if(all_in)
        cout << "All-in" << endl;
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

int player::getMise()
{
    return mise;
}

void player::allIn()
{
    all_in = true;
    mise += credit;
    credit = 0;
}
#include "../include/player.hpp"
#include "../include/game.hpp"

player::player(float val) {
    if (val <= 0 || val < BB){
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
    if (amount > credit) {//crédit insuffisant pour miser
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
    else if (amount < SB) {//la mise du joueur doit etre superieure a la mise minimale
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
        credit -= amount;//crédit mis à jour après le call
        mise = amount;//derniere mise faite
    }
}

void player::hit(card &c)
{
    //lorsque une carte est distribuée au joueur, sa ain doit etre mise à jour
    hand_player.setCards(c);
}


void player::fold()
{
    //si le joueur se couche, il continue pas la round
    in_game = false;
}

void player::call(int val)
{
      if (val > credit) {
        cout << "Erreur : la mise ne peut pas être supérieure à votre crédit actuel." << endl;
        do {
            cout << "Entrez une nouvelle mise ou tapez 0 pour fold : ";//fold si le joueur ne possede pas la somme execte à miser
            cin >> val;
            if (val == 0) {
                in_game = false;
                break;
            }
        } while (val > credit);
    }
    if (in_game) {
        credit -= val;//crédit mis à jour après le call
        mise = val;//derniere mise faite
    }     
}

void player::raise(int val)
{
       if (val > credit) {//crédit insuffisant pour miser
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
        mise = val;
    }
}

void player::print_card()
{
    hand_player.print_hand();//affcher la main du joueur
}

void player::player_clear_hand()
{
    hand_player.clear_hand();//vider la main du joueur
}

hand player::get_hand()
{
    return hand_player;//retourne la main du joueur
}

void player::print_player()
{
    cout << "cartes " << endl; print_card();
    cout << "mise " << mise << endl;
    cout << "credit " << credit << endl;
    if(all_in)//seulement pour le joueurs qui ont fait un all-in
        cout << "All-in" << endl;
}

float player::get_credit()
{
    return this->credit;
}

void player::update_credit(float val)
{
    credit+=val;
}

void player::setScore(int val)
{
    score += val;//scoremis a jour apres cheque check de combinaison fait
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
    //si le joueur fait un all-in donc il mise tout son crédit 
    all_in = true;
    mise += credit;
    credit = 0;
}
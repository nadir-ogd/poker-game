#include "../include/dealer.hpp"
#include <cstdlib>

#define SB 2
#define BB 2*SB

using namespace std;

dealer::dealer()
{
    for(int i = Piques; i <= Trefles; i++)
		for(int j = Deuce; j <= Ace; j++)
			cards.push_back(card(static_cast<Couleur>(i), static_cast<Rang>(j)));
}

void dealer::shuffle()
{
    srand(time(NULL));
    int len = cards.size();
    while(len > 0)
    {
        int ind = rand() % len;
        deck.push_back(cards[ind]);
        cards.erase(cards.begin() + ind);
        len--;
    }
}

bool dealer::miser_avant(int i) // verifier si il y a une mise faite avant le joueur i
{
    int j = 0;

    while(j < nbJoueurs){
        if(j == i)
            j++;
        else
            if(players.at(j).is_bet)
                return true;
            else 
                j++;
    }     
    return false;
}

void dealer::print_cards()
{
    for(int i = 0; i < (int)cards.size(); i++)
        cards.at(i).print();
}

void dealer::print_deck()
{
    for(int i = 0; i < (int)deck.size(); i++) 
    {   
        deck.at(i).print();
    }
}

void dealer::blinds(player &g, player &gg)
{
    //Small Blind 
    cout << "La small blind : " << SB << "$ est payée..." << endl;
    g.bet(SB);
    //Big Blind
    cout << "La big blind  : " << BB << "$ est payée..." << endl;
    gg.bet(BB);
    lastMise = BB;
}

void dealer::distribuer_player(player &p)
{        
    p.hit(deck.back());
    deck.pop_back();
    p.hit(deck.back());
    deck.pop_back();
}

void dealer::hitBoard()
{
    hand_dealer.setCards(deck.back());
    deck.pop_back();
}

void dealer::encheres(int i)
{
    int choix, val = 0;
    bool bet_before;

    bet_before = miser_avant(i);

    if(players[i].in_game){
        cout << "player " << i << endl;
        cout << "Qu'est ce que vous voullez faire ?" << endl;
        if(!bet_before)
        {
            cout << "(0) bet" << endl;
            cout << "(1) check" << endl;
            
            cin >> choix;
            switch(choix) {
                case 0:
                    cout << "Entrez la somme a miser : ";
                    cin >> val;
                    players[i].bet(val);
                    lastMise = val;
                    break;
                case 1:
                    players[i].check();
                    break;
            }
        }
        else 
        {   
            
            cout << "(0) fold" << endl;
            cout << "(1) call" << endl;
            cout << "(2) raise" << endl;

            cin >> choix;
            switch(choix) {
                case 0:
                    cout << "Vous etre hors main" << endl;
                    players[i].fold();
                    players[i].is_bet = false;
                    break;
                case 1:
                    players[i].call(lastMise);
                    break;
                case 2:
                    cout << "Entrez la somme a raiser : ";
                    cin >> val;
                    while(val < lastMise)
                        cout << "Entrez une nouvelle valeur à raiser : " << endl;
                    players[i].raise(val);
                    lastMise = val; 
                    break;
            }
        }
    }
    else
        cout << "player " << i << " vous etes hors main !" << endl;
   
}

void dealer::combinaisons(int i)
{
    
}

void dealer::play()
{
    cout << "######### Poker Game #########" << endl;
    cout << "Veuillez entrer le nombre de joureurs : " << endl;
    cin >> nbJoueurs;
    for(int i = 0; i < nbJoueurs; i++)
        players.push_back(player(100));  
        
    dealer();
    cout << "Le dealer mélange les cartes..." << endl;
    sleep(rand() % 5);
    shuffle();
    //print_deck();
    cout << "Les cartes sont mélangées !" << endl;
    blinds(players[0],players[1]);
    //for(int i = 0; i < nbJoueurs; i++)
    //   players.at(i).print_player(i);
    cout << "Le dealer va distribuer 2 cartes pour chaque joueur..." << endl;
    for(int i = 0; i < nbJoueurs; i++){
        distribuer_player(players.at(i));
    }
        
    //print_deck();
    cout << "Le Flop..." << endl;

    for(int i = 2; i< nbJoueurs; i++)
        if(players[i].in_game)
            encheres(i);
    
    hitBoard();
    hitBoard();
    hitBoard();

    for(int i = 0; i < nbJoueurs; i++)
        players.at(i).print_player(i);

    cout << "Les cartes actuelles de board :" << endl;
    hand_dealer.print_hand();
       
    cout << "Le Turn..." << endl;

    for(int i = 0; i < nbJoueurs; i++)
        encheres(i);

    hitBoard();

    for(int i = 0; i < nbJoueurs; i++)
        players.at(i).print_player(i);

    cout << "Les cartes actuelles de board :" << endl;
    hand_dealer.print_hand();

           
    cout << "La River..." << endl;

    for(int i = 0; i < nbJoueurs; i++)
        encheres(i);

    hitBoard();

    for(int i = 0; i < nbJoueurs; i++)
        players.at(i).print_player(i);

    cout << "Les cartes actuelles de board :" << endl;
    hand_dealer.print_hand();

    // hand_dealer.sort_hand(players[0].get_hand());

    // hand_dealer.print_hand();

}


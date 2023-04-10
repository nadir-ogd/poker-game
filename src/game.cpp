#include "../include/game.hpp"
#include <cstdlib>

using namespace std;

game::game()
{
    for(int i = Piques; i <= Trefles; i++)
		for(int j = Deuce; j <= Ace; j++)
			cards.push_back(card(static_cast<Couleur>(i), static_cast<Rang>(j)));
    lastMise = 0;
    price_pot = SB + BB;
}

void game::shuffle()
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

// bool game::miser_avant(int i) // verifier si il y a une mise faite avant le joueur i
// {
//     int j = 0;

//     while(j < nbJoueurs){
//         if(j == i)
//             j++;
//         else
//             if(players.at(j).is_bet)
//                 return true;
//             else 
//                 j++;
//     }     
//     return false;
// }

void game::print_cards()
{
    for(int i = 0; i < (int)cards.size(); i++)
        cards.at(i).print();
}

void game::print_deck()
{
    for(int i = 0; i < (int)deck.size(); i++) 
    {   
        deck.at(i).print();
    }
}

void game::blinds(player &g, player &gg)
{
    //Small Blind 
    cout << "Player " << indSB << " paye la Small Blind : " << SB << " $" << endl; 
    g.bet(SB);
    //Big Blind
    cout << "Player " << indBB << " paye la Big Blind : " << BB << " $" << endl; 
    gg.bet(BB);
    lastMise = BB;
}

void game::distribuer_player(player &p)
{        
    p.hit(deck.back());
    deck.pop_back();
    p.hit(deck.back());
    deck.pop_back();
}

void game::hitBoard()
{
    hand_board.setCards(deck.back());
    deck.pop_back();
}

void game::prefflop(int i)
{
    int choix,val;
     if(players[i].in_game){
        if(i == indBB && !miseAvant){
            cout << "player " << i << endl;
            cout << "Qu'est ce que vous voullez faire ?" << endl;

            cout << "(0) bet" << endl;
            cout << "(1) check" << endl;
                
            cin >> choix;
            switch(choix) {
                case 0:
                    cout << "Entrez la somme a miser : ";
                    cin >> val;
                    players[i].bet(val);
                    lastMise = val;
                    price_pot += val;
                    miseAvant = true;
                    break;
                case 1:
                    miseAvant = false;
                    break;
                }
        }
        else {
            cout << "player " << i << endl;
            cout << "Qu'est ce que vous voullez faire ?" << endl;

            cout << "(0) fold" << endl;
            cout << "(1) call" << endl;
            cout << "(2) raise" << endl;

            cin >> choix;
            switch(choix) {
                case 0:
                    cout << "Vous etre hors main" << endl;
                    players[i].fold();
                    break;
                case 1:
                    players[i].call(lastMise);
                    price_pot += lastMise;
                    if(i == indBB)
                        miseAvant = false;
                    break;
                case 2:
                    cout << "Entrez la somme a raiser : ";
                    cin >> val;
                    while(val < lastMise){
                        cout << "Entrez une nouvelle valeur à raiser : " << endl;
                        cin >> val;
                    }
                    players[i].raise(val);
                    lastMise = val; 
                    price_pot += val;
                    miseAvant = true;
                    break;
            } 
        }   
    }
    else 
        cout << "player " << i << " vous etes hors main !" << endl;
}

void game::encheres(int i)
{
    int choix, val = 0;

    if(players[i].in_game){
        cout << "player " << i << endl;
        cout << "Qu'est ce que vous voullez faire ?" << endl;
        if(!miseAvant)
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
                    price_pot += val;
                    miseAvant = true;
                    break;
                case 1:
                    //players[i].check();
                    miseAvant = false;
                    break;
            }
        }
        else if(miseAvant)
        {        
            cout << "(0) fold" << endl;
            cout << "(1) call" << endl;
            cout << "(2) raise" << endl;

            cin >> choix;
            switch(choix) {
                case 0:
                    cout << "Vous etre hors main" << endl;
                    players[i].fold();
                    break;
                case 1:
                    players[i].call(lastMise);
                    price_pot += lastMise;
                    if(indSB == i)
                        miseAvant = false;
                    break;
                case 2:
                    cout << "Entrez la somme a raiser : ";
                    cin >> val;
                    while(val < lastMise){
                        cout << "Entrez une nouvelle valeur à raiser : " << endl;
                        cin >> val;
                    }
                    players[i].raise(val);
                    lastMise = val; 
                    price_pot += val;
                    miseAvant = true;
                    break;
            }
        }
    }
    else
        cout << "player " << i << " vous etes hors main !" << endl;
   
}

void game::determine_winner(hand& hand_board) {
    int max_score = 0;

    for (int i =0; i < nbJoueurs; i++) {
        if(players[i].in_game){
            int score = 0;
            if (players[i].get_hand().is_royal_flush(hand_board)) {
                score = 10;
                max_score = 10;

            } else if (players[i].get_hand().is_straight_flush(hand_board)) {
                score = 9; 
                max_score = max(max_score,9);
            
            } else if (players[i].get_hand().is_4_of_a_kind(hand_board)) {
                score = 8; 
                max_score = max(max_score,8);
            
            } else if (players[i].get_hand().is_full_house(hand_board)) {
                score = 7; 
                max_score = max(max_score,7);
            
            } else if (players[i].get_hand().is_flush(hand_board)) {
                score = 6; 
                max_score = max(max_score,6);
        
            } else if (players[i].get_hand().is_straight(hand_board)) {
                score = 5; 
                max_score = max(max_score,5);
        
            } else if (players[i].get_hand().is_3_of_a_kind(hand_board)) {
                score = 4;
                max_score = max(max_score,4);
        
            } else if (players[i].get_hand().is_two_pairs(hand_board)) {
                score = 3; 
                max_score = max(max_score,3);
        
            } else if (players[i].get_hand().is_one_pair(hand_board)) {
                score = 2; 
                max_score = max(max_score,2);
        
            } else {
                score = 1; 
                max_score = max(max_score,1); //High Card
            }
            players[i].setScore(score);
        }
        else
            players[i].setScore(0);
    }
        
        vector <int> score_players(nbJoueurs);
        vector <int> winners;

        for(int i = 0; i < nbJoueurs ; i++)
            score_players[i] = players[i].getScore();
        
        for (int i = 0; i < nbJoueurs; i++)
            if (score_players[i] == max_score)
                winners.push_back(i);

        for (int i = 0; i < static_cast<int>(winners.size()); i++)
            players[winners[i]].update_credit(price_pot / winners.size());

        string strategie;
	
	switch(max_score){
		case 1:
			strategie = "High Card";
			break;
		case 2:
			strategie = "One Pair";
			break;
		case 3:
			strategie = "Two Pairs";
			break;
		case 4:
			strategie = "Three of A Kind";
			break;
		case 5:
			strategie = "Straight";
			break;
		case 6:
			strategie = "Flush";
			break;
		case 7:
			strategie = "Full House";
			break;
		case 8:
			strategie = "Four of A Kind";
			break;
		case 9:
			strategie = "Straight Flush";
			break;
        case 10:
            strategie = "Royal Flush";
            break;
	}

        cout << "--------- " << strategie << " ---------" << endl;
        cout << "Winners of this round are : " << endl;
       
        for (int i = 0; i < static_cast<int>(winners.size()); i++) {
            int ind = winners[i];
    
            cout << "Player " << ind << " a gagné : " << price_pot / winners.size() << " $" << endl;
            players[ind].print_player();
        }

        for(int i = 0; i < nbJoueurs; i++){
            players[i].get_hand().clear_hand();
            players[i].in_game = true;
            players[i].in_game = true;
        }

        hand_board.clear_hand();
        lastMise = 0;
        price_pot = 0;        
}

void game::play()
{
    int nbRounds;
    indSB = 0, indBB = 1;

    cout << "######### Poker Game #########" << endl;
    cout << "Veuillez entrer le nombre de joureurs : ";
    cin >> nbJoueurs;

    
    nbRounds = 52 / (nbJoueurs * 2); 
    cout << "Le nombre de rounds est : " << nbRounds << endl;
    float credit;

    for(int i = 0; i < nbJoueurs; i++){
        cout << "player " << i << ", entrez votre crédit : ";
        cin >> credit;
        players.push_back(player(credit));
    }  
        
    system("clear");
    for(int i = 0; i < nbRounds; i++){
        cout << "Le dealer mélange les cartes..." << endl;
        sleep(rand() % 5);
        shuffle();
        cout << "Les cartes sont mélangées !" << endl;

        blinds(players[indSB],players[indBB]);

        cout << "Le dealer va distribuer 2 cartes pour chaque joueur..." << endl;
        for(int i = 0; i < nbJoueurs; i++){
            distribuer_player(players.at(i));
        }

        cout << "Le Prefflop..." << endl;
        
        for(int i = indBB+1; i < (nbJoueurs+indBB+1); i++)
            prefflop(i % nbJoueurs);

        hitBoard();
        hitBoard();
        hitBoard();


        cout << "Les 3 premières cartes sont dévoilées :" << endl; 
        hand_board.print_hand();

        cout << "Le fflop..." << endl;

        for(int i = indSB; i < (nbJoueurs + indSB); i++)
                encheres(i % nbJoueurs);
        
        hitBoard();

        cout << "La 4-ème carte est dévoilée :" << endl; 
        hand_board.print_hand();
    
        cout << "Le turn..." << endl;

        for(int i = indSB; i < (nbJoueurs + indSB); i++)
                encheres(i % nbJoueurs);
        
        hitBoard();

        cout << "La 5-ème carte est dévoilée :" << endl; 
        hand_board.print_hand();

        cout << "La river..." << endl;

        for(int i = indSB; i < (nbJoueurs + indSB); i++)
                encheres(i % nbJoueurs);

        for(int i = 0; i < nbJoueurs; i++){
            cout << "Player " << i << endl;
            players.at(i).print_player();
        }

        cout << "Les cartes actuelles de board :" << endl;
        hand_board.print_hand();
        
        cout << "Le Turn..." << endl;

        for(int i = 0; i < nbJoueurs; i++)
            encheres(i);

        hitBoard();

        for(int i = 0; i < nbJoueurs; i++){
            cout << "Player " << i << endl;
            players.at(i).print_player();
        }

        cout << "Les cartes actuelles de board :" << endl;
        hand_board.print_hand();

            
        cout << "La River..." << endl;

        for(int i = 0; i < nbJoueurs; i++)
            encheres(i);

        hitBoard();

        for(int i = 0; i < nbJoueurs; i++){
            cout << "Player " << i << endl;
            players.at(i).print_player();
        }

        cout << "Les cartes actuelles de board :" << endl;
        hand_board.print_hand();

        determine_winner(hand_board);

        indSB = (indSB + 1) % nbJoueurs;
        indBB = (indBB + 1) % nbJoueurs;
    }
}

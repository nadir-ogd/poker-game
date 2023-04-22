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
     if(players[i].in_game && !players[i].all_in){
        if(i == indBB && !miseAvant){
            cout << "player " << i << " crédit : "<< players[i].get_credit() << "$" << endl;
            cout << endl;
            cout << "Qu'est ce que vous voullez faire ?" << endl;
            
            do{
                cout << "(0) bet" << endl;
                cout << "(1) check" << endl;
                cout << "\n Veuillez entrer soit 0 , 1\n";
                cin >> choix;
            }while(choix < 0 || choix > 2);

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
            cout << "player " << i << " crédit : "<< players[i].get_credit() << "$" << endl;
            cout << endl;
            cout << "Qu'est ce que vous voullez faire ?" << endl;

            do{
                cout << "(0) fold" << endl;
                cout << "(1) call" << endl;
                cout << "(2) raise" << endl;
                cout << "\n Veuillez entrer soit 0 , 1 , 2\n";
                cin >> choix;
            }while(choix < 0 || choix > 2);

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
                    do{
                        cout << "(0) raise" << endl;
                        cout << "(1) all-in" << endl;
                        cout << "\n Veuillez entrer soit 0 , 1\n";
                        cin >> choix;
                        cout << "choix dakhel all-in" << endl;
                    }while(choix < 0 || choix > 1);
                    switch(choix){
                        case 0:                                               
                            cout << "Entrez la somme a raiser : ";
                            cin >> val;
                            while(val < lastMise){
                                cout << "Entrez une nouvelle valeur à raiser : " << endl;
                                cin >> val;
                            }
                            players[i].raise(val);
                            lastMise = val; 
                            price_pot += val;
                            break;

                        case 1:
                            cout << "tout le crédit est misé, le joueur " << i << " se couche alors" << endl;
                            price_pot += players[i].get_credit();
                            lastMise = players[i].get_credit();
                            players[i].allIn();
                            break;  
                        miseAvant = true;  
                    }
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

    if(players[i].in_game && !players[i].all_in){
        cout << "player " << i << " crédit : "<< players[i].get_credit() << "$" << endl;
        cout << endl;
        cout << "Qu'est ce que vous voullez faire ?" << endl;
        if(lastMise == players[i].getMise() || !miseAvant)//lastmise si tous les joueurs ont fait un call et miseAvant (en cas d'absence de mise avant)
        {
            do{
                cout << "(0) bet" << endl;
                cout << "(1) check" << endl;
                cout << "\n Veuillez entrer soit 0 , 1\n";
                cin >> choix;
            }while(choix < 0 || choix > 1);

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
                    miseAvant &= false;
                    break;
            }
        }
        else
        {        
            do{
                cout << "(0) fold" << endl;
                cout << "(1) call" << endl;
                cout << "(2) raise" << endl;
                cout << "\n Veuillez entrer soit 0 , 1 , 2\n";
                cin >> choix;
            }while(choix < 0 || choix > 2);
            
            switch(choix) {
                case 0:
                    cout << "Vous etre hors main" << endl;
                    players[i].fold();
                    break;
                case 1:
                    players[i].call(lastMise);
                    price_pot += lastMise;
                    break;
                case 2:
                    do{
                        cout << "(0) raise" << endl;
                        cout << "(1) all-in" << endl;
                        cout << "\n Veuillez entrer soit 0 , 1\n";
                        cin >> choix;
                    }while(choix < 0 || choix > 1);
                    
                    switch(choix){
                        case 0:                                                
                            cout << "Entrez la somme a raiser : ";
                            cin >> val;
                            while(val < lastMise){
                                cout << "Entrez une nouvelle valeur à raiser : " << endl;
                                cin >> val;
                            }
                            players[i].raise(val);
                            lastMise = val; 
                            price_pot += val;
                            break;

                        case 1:
                            cout << "tout le crédit est misé, le joueur " << i << " se couche alors" << endl;
                            price_pot += players[i].get_credit();
                            lastMise = players[i].get_credit();
                            players[i].allIn();
                            break;    
                    }
                    miseAvant &= true;
                    break;
            }
        }
    }
    else
        cout << "player " << i << " vous etes hors main !" << endl;
   
}

void game::determine_winner(hand& hand_board) {
    cout << "#### Annoncement des gagnants ####" << endl;
    cout << endl;

    int max_score = 0;
    int count = 0,ind;
    for (int i = 0; i < nbJoueurs; i++) {
        if (players[i].in_game) {
            count++;
            ind = i;
        }   
    }

    if(count == 0){
        cout << "Tout le monde est hors main, pas de gagnant " << endl; 
    }
    
    else if(count == 1){
        cout << "Tout le monde est hors main, le seul gagnant est :" << endl;
        cout << "Player " << ind << " a gagné : " << price_pot << " $" << endl;
        players[ind].update_credit(price_pot);
        players[ind].print_player();
    }

    else if(count > 1){

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
        cout << endl;

        cout << "## Les cartes de Board ##" << endl;
        hand_board.print_hand();
        cout << endl;

        cout << "Les gagnants de cette round sont : " << endl;

        for (int i = 0; i < static_cast<int>(winners.size()); i++) {
            int ind = winners[i];
    
            cout << "Player " << ind << " a gagné : " << price_pot / winners.size() << " $" << endl;
            players[i].update_credit(price_pot / winners.size());
            players[ind].print_player();
            cout << endl;
        }
    }
}

void game::play()
{
    int nbRounds;
    indSB = 0, indBB = 1;

    cout << "######### Poker Game #########" << endl;
    cout << endl;
    

    do{
        cout << "[*] Nombre de joueurs : ";
        cin >> nbJoueurs;
    }while(nbJoueurs < 2 || nbJoueurs > 10);

    nbRounds = 52 / (nbJoueurs * 2 + 5); 
    cout << "[*] Nombre de rounds est : " << nbRounds << endl;
    cout << endl;

    float credit;

    cout << "[*] Préparation des joueurs" << endl;
    cout << endl;

    for(int i = 0; i < nbJoueurs; i++){
        cout << "player " << i << ", entrez votre crédit : ";
        cin >> credit;
        players.push_back(player(credit));
    }  
        
    cout << "\nAppuyez sur une touche pour continuer" << endl;
    cin.get();
    system("clear");

    int indRound = 0;
    while(indRound < nbRounds){
        cout << "#### Début Round " << indRound << " ####" <<endl;
        cout << endl;

        cout << "[*] Le dealer mélange les cartes..." << endl;
        sleep(rand() % 5);
        shuffle();

        cout << "[*] Les cartes sont bien mélangées !" << endl;
        cout << endl;

        blinds(players[indSB],players[indBB]);
        cout << endl;

        cout << "[*] Le dealer distribue 2 cartes pour chaque joueur..." << endl;
        for(int i = 0; i < nbJoueurs; i++){
            distribuer_player(players.at(i));
        }

    
        cout << "\n\nAppuyez sur une touche pour passer au Prefflop..." << endl;
        cin.get();
        system("clear");

        cout << "#### Le Prefflop ####" << endl;
        cout << endl;

        for(int i = indBB+1; i < (nbJoueurs+indBB+1); i++)
            prefflop(i % nbJoueurs);

        hitBoard();
        hitBoard();
        hitBoard();

        cout << "\n[*] Les 3 premières cartes sont dévoilées :" << endl; 
        cout << endl;

        hand_board.print_hand();

        cin.get();
        cout << "\n\nAppuyez sur une touche pour passer au Fflop..." << endl;
        cin.get();
        system("clear");

        cout << "#### Le fflop ####" << endl;
        cout << endl;

        for(int i = indSB; i < (nbJoueurs + indSB); i++)
                encheres(i % nbJoueurs);
        
        hitBoard();

        cout << "\n[*] La 4-ème carte est dévoilée :" << endl; 
        cout << endl;
        hand_board.print_hand();

        cin.get();
        cout << "\n\nAppuyez sur une touche pour passer au Turn..." << endl;
        cin.get();
        system("clear");
        
        cout << "#### Le turn ####" << endl;
        cout << endl;

        for(int i = indSB; i < (nbJoueurs + indSB); i++)

                encheres(i % nbJoueurs);
        
        hitBoard();

        cout << "\n[*] La 5-ème carte est dévoilée :" << endl; 
        cout << endl;

        hand_board.print_hand();

        cin.get();
        cout << "\n\nAppuyez sur une touche pour passer au River..." << endl;
        cin.get();
        system("clear");
        
        cout << "#### La river ####" << endl;
        cout << endl;

        for(int i = indSB; i < (nbJoueurs + indSB); i++)
                encheres(i % nbJoueurs);

        cout << "\n[*] Toutes les cartes sont dévoilées :" << endl;
        cout << endl;

        hand_board.print_hand();

        cin.get();
        cout << "\n\nAppuyez sur une touche pour déterminer les gagnants..." << endl;
        cin.get();
        system("clear");

        determine_winner(hand_board);

        cout << "\n[*] Vider les mains des joueurs et du board..." << endl;
        sleep(rand()%5);

        for(int i = 0; i < nbJoueurs; i++){
            players[i].player_clear_hand();
            players[i].in_game = true;
            if(players[i].get_credit() == 0){
                cout << "Player " << i << " est retiré de la partie, car il possede plus de credit..." << endl;
                players.erase(players.begin() + i);
                nbJoueurs = nbJoueurs - 1;
            }
        }

        if(nbJoueurs == 0){
            cout << "[*] Il y a plus de joueurs dans la table " << endl;
            break;//on sort de la boucle for donc "fin du jeu"
        }

        else if(nbJoueurs == 1){
            cout << "[*] Il reste un seul joueur dans la table, c le seul gagnant il emporte tout le pot :" << price_pot << " $"  << endl;
            break;//on sort de la boucle for donc "fin du jeu"
        }

        hand_board.clear_hand();    
        
        cout << "[*] Il reste " << nbJoueurs << " joueurs dans la table..." << endl;

        cout << endl << "\n#### Fin Round "<< indRound << " ####" <<endl;
        cout << endl;

        indSB = (indSB + 1) % nbJoueurs;//L'indice de joueur qui va payer Small Blind dans le prochain round
        indBB = (indBB + 1) % nbJoueurs;//L'indice de joueur qui va payer Big Blind dans le prochain round

        lastMise = 0;//réinitialisation à zéro pour le nouvel round
        price_pot = 0;//réinitialisation à zéro pour le nouvel round

        indRound++;

        cout << "\nAppuyez sur une touche pour commencer une nouvelle round..." << endl;
        cin.get();
        system("clear");
    }
}


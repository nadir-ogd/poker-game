#include "../include/game.hpp"
#include <cstdlib>

using namespace std;

game::game()
{
    for(int i = Piques; i <= Trefles; i++)
		for(int j = Deuce; j <= Ace; j++)
			cards.push_back(card(static_cast<Couleur>(i), static_cast<Rang>(j)));//initialiser les cartes du jeur (avant les mélanger)
    lastMise = 0;
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
    price_pot = SB + BB;
    lastMise = BB;
}

void game::distribuer_player(player &p)
{        
    //deux cartes pour chaque joueur
    p.hit(deck.back());
    deck.pop_back();
    p.hit(deck.back());
    deck.pop_back();
}

void game::hitBoard()
{
    //une carte est mise sur la table
    hand_board.setCards(deck.back());
    deck.pop_back();
}

void game::prefflop(int i)
{
    int choix,val;
     if(players[i].in_game && !players[i].all_in){
        if(i == indBB && !miseAvant){//si c le tour du joueur de SB et aucune augmentation sur sa SB donc il doit soit miser soit checker
            cout << endl << "player " << i << " crédit : "<< players[i].get_credit() << "$" << endl;
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
            cout << endl << "player " << i << " crédit : "<< players[i].get_credit() << "$" << endl;
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
                    if(i == indBB)//le joueur BB joue avant dernier (SB) au prefflop c le cas ou tout le monde a suivi ou flod seulement (pas de mise)
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
        cout << endl << "player " << i << " crédit : "<< players[i].get_credit() << "$" << endl;
        cout << endl;
        cout << "Qu'est ce que vous voullez faire ?" << endl;
        if(lastMise == players[i].getMise() || !miseAvant)
        //lastmise = mise du joueur : veut dire que tous les joueurs ont fait un call et miseAvant = false (en cas d'absence de mise avant)
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
        cout << endl << "player " << i << " vous etes hors main !" << endl;
   
}

void game::determine_winner(hand& hand_board) {
    cout << "#### Annoncement des gagnants ####" << endl;
    cout << endl;

    int max_score = 0;//indice de meilleure combinaison possible
    int count = 0,ind;
    for (int i = 0; i < nbJoueurs; i++) {
        if (players[i].in_game) {
            count++;//nb de joueurs en jeu
            ind = i;//si un seul joueur seulement est en jeu
        }   
    }

    if(count == 0){
        cout << "[*] Tout le monde est hors main, pas de gagnant " << endl; 
    }
    
    else if(count == 1){
        cout << "[*] Tout le monde est hors main, le seul gagnant est :" << endl;
        cout << "Player " << ind << " a gagné : " << price_pot << " $" << endl;
        players[ind].update_credit(price_pot);
        players[ind].print_player();
    }

    else if(count > 1){

    for (int i =0; i < nbJoueurs; i++) {
        if(players[i].in_game){
            int score = 0;//[1-10] => de la plus forte combinaison au plus faible
            //on utilise max pour définir la meilleure combinaison du joueur 
            //par exemple si is_flush = 1 et is_straight_flush = 1 la combinasion choisie sera straught_flush
            //car score de straight flush = 9 et de flush est 6
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
        
        vector <int> score_players(nbJoueurs);//score_players[i] est l"indice de stratégie du joueur i
        vector <int> winners;

        for(int i = 0; i < nbJoueurs ; i++)
            score_players[i] = players[i].getScore();
        
        for (int i = 0; i < nbJoueurs; i++)
            if (score_players[i] == max_score)
                winners.push_back(i);

        string strategie;
	
	switch(max_score){//pour afficher la stratégie gagnante
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

        cout << "## cartes de board ##" <<endl;
        hand_board.print_hand();
        cout << endl;

        cout << "[*] Les gagnants de cette round sont : " << endl;

        for (int i = 0; i < static_cast<int>(winners.size()); i++) {
            int ind = winners[i];
    
            cout << endl << "Player " << ind << " a gagné : " << price_pot / winners.size() << " $" << endl;
            players[i].update_credit(price_pot / winners.size());
            players[ind].print_player();
            cout << endl;
        }
    }
}

void game::play()
{
    int nbRounds;
    indSB = 0, indBB = 1;//pour le Round 0 seulement

    cout << "######### Poker Game #########" << endl;
    cout << endl;
    

    do{
        cout << "[*] Nombre de joueurs : ";
        cin >> nbJoueurs;
    }while(nbJoueurs < 2 || nbJoueurs > 10);

    nbRounds = 52 / (nbJoueurs * 2 + 5); 
    cout << "[*] Nombre de rounds est : " << nbRounds << endl;//le nombre de round est estimé en utilisant le nombre de cartes distribués (au joueurs , sur le board)
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

        blinds(players[indSB],players[indBB]);//désigner les joueurs qui paient les blinds
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

        for(int i = indBB+1; i < (nbJoueurs+indBB+1); i++)//au prefflop le joueur après le indBB joue en premier, et le joueur BB en dernier
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

        //dans le reste des tours, le indSB joue en premier et le dealer en dernier (avant indSB)
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

        cout << "\n[*] Vider les mains des joueurs et du board..." << endl;//pour le prochain round
        sleep(rand()%5);

        for(int i = 0; i < nbJoueurs; i++){
            players[i].player_clear_hand();
            players[i].in_game = true;
            if(players[i].get_credit() == 0){//si un joueur ne possede rien, il sera retiré
                cout << "Player " << i << " est retiré de la partie, car il possede plus de credit..." << endl;
                players.erase(players.begin() + i);
                nbJoueurs = nbJoueurs - 1;
                for(int i = 0; i < players.size(); i++)
                    players[i].print_player();
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


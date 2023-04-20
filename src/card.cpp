#include "../include/card.hpp"
#include <iostream>

string couleurTxt[] = {"\u2660","\u2661","\u2662","\u2663"};
string rangTxt[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

card::card(Couleur c, Rang r){
    couleur = c;
    rang = r;
}

void card::print(){
    if (couleur == Coeurs || couleur == Carreaux)
        cout << "\033[1;31m" << couleurTxt[couleur] << " | " << rangTxt[rang] << "\033[0m" << endl; 
    else
        cout << "\033[1;30m" << couleurTxt[couleur] << " | " << rangTxt[rang] << "\033[0m" << endl; 
}

int card::getRang()
{
    return rang;
}

int card::getCouleur()
{
    return couleur;
}

#include <iostream>
#include "../include/dealer.hpp"

int main() {
    // dealer d;
    // d.play();
    hand h1,h2;
    // for(int i = 3; i < 7; i++){
    //     card c(Trefles,static_cast<Rang>(i));
    //     h1.setCards(c);
    // }        
    card c1(Coeurs, Ten);
    card c2(Trefles,Ace);
    card c3(Piques, Ten);
    card c4(Piques,Ace);
    card c5(Piques,Jack);
    card c6(Piques, King);
    card c7(Piques, Deuce);  
    h1.setCards(c1);  
    h1.setCards(c2);  
    h1.setCards(c3);  
    h1.setCards(c4);  
    h1.setCards(c5);  

    h2.setCards(c6);
    h2.setCards(c7);
    h2.print_hand();
    cout << """""""""" << endl;
    h1.print_hand();
    cout << """""""""" << endl;
    cout << h2.is_one_pair(h1) << endl;

    //cout << h1.is_royal_flush(h2) << endl;
    //cout << h1.is_straight_flush(h2) << endl;
}
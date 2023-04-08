#include <iostream>
#include "../include/dealer.hpp"

int main() {
    // dealer d;
    // d.play();
    hand h1,h2;
    for(int i = 8; i < 12; i++){
        card c(Trefles,static_cast<Rang>(i));
        h1.setCards(c);
    }        
    card c(Coeurs, King);
    card c1(Piques, King);
    card c2(Carreaux, King);  
    h1.setCards(c);  
    h2.setCards(c1);
    h2.setCards(c2);
    h2.print_hand();
    cout << """""""""" << endl;
    cout << h1.is_4_of_a_kind(h2) << endl;
    //cout << h1.is_royal_flush(h2) << endl;
    //cout << h1.is_straight_flush(h2) << endl;
}
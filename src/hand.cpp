#include "../include/hand.hpp"
#include <algorithm>

void hand::setCards(card &c)
{
    if(hand_cards.size() < 5){
        hand_cards.push_back(c);
        score+=c.getRang();
    }
    else{
        cout << "toutes les cartes communes ont été dévoilées." << endl;
    }
}

card hand::get_card(int i)
{
    return hand_cards.at(i);
}

void hand::print_hand()
{
    int len = hand_cards.size();
    for(int i = 0; i < len; i++)
        hand_cards.at(i).print();
}

int hand::sizeBroad()
{
    return hand_cards.size();
}

bool hand::is_royal_flush(hand hand_board)
{
    hand_cards.insert(hand_cards.end(), hand_board.hand_cards.begin(), hand_board.hand_cards.end());
    sort(hand_cards.begin(), hand_cards.end(), [](card& a, card& b) {
        return a.getCouleur() < b.getCouleur() ||
               (a.getCouleur() == b.getCouleur() && a.getRang() < b.getRang());
    });
    for (int i = 0; i < 3; i++) {
        if (hand_cards[i].getCouleur() == hand_cards[i + 1].getCouleur() &&
            hand_cards[i].getCouleur() == hand_cards[i + 2].getCouleur() &&
            hand_cards[i].getCouleur() == hand_cards[i + 3].getCouleur() &&
            hand_cards[i].getCouleur() == hand_cards[i + 4].getCouleur() &&
            hand_cards[i].getRang() == 8 &&
            hand_cards[i+1].getRang() == 9 &&
            hand_cards[i+2].getRang() == 10 &&
            hand_cards[i+3].getRang() == 11 &&
            hand_cards[i+4].getRang() == 12)
            {
            return true;
        }   
    }
    return false;
    
}

bool hand::is_straight_flush(hand hand_board)
{
    hand_cards.insert(hand_cards.end(), hand_board.hand_cards.begin(), hand_board.hand_cards.end());
    sort(hand_cards.begin(), hand_cards.end(), [](card& a, card& b) {
        return a.getCouleur() < b.getCouleur() ||
               (a.getCouleur() == b.getCouleur() && a.getRang() < b.getRang());
    });
    for (int i = 0; i < 3; i++) {
        if (hand_cards[i].getCouleur() == hand_cards[i + 1].getCouleur() &&
            hand_cards[i].getCouleur() == hand_cards[i + 2].getCouleur() &&
            hand_cards[i].getCouleur() == hand_cards[i + 3].getCouleur() &&
            hand_cards[i].getCouleur() == hand_cards[i + 4].getCouleur() &&
            (hand_cards[i].getRang() == hand_cards[i + 1].getRang() - 1 &&
            hand_cards[i].getRang() == hand_cards[i + 2].getRang() - 2 &&
            hand_cards[i].getRang() == hand_cards[i + 3].getRang() - 3 &&
            hand_cards[i].getRang() == hand_cards[i + 4].getRang() - 4 &&
            hand_cards[i+4].getRang() != 12) || 
            (hand_cards[i].getRang() == 0 &&
            hand_cards[i+1].getRang() == 1 &&
            hand_cards[i+2].getRang() == 2 &&
            hand_cards[i+3].getRang() == 3 &&
            hand_cards[i+4].getRang() == 12))
            {
            return true;
        }   
    }
    return false;
    
}

bool hand::is_4_of_a_kind(hand hand_board)
{
    hand_cards.insert(hand_cards.end(), hand_board.hand_cards.begin(), hand_board.hand_cards.end());
    sort(hand_cards.begin(), hand_cards.end(), [](card& a, card& b) {
               return a.getRang() < b.getRang();
    });

    for (int i = 0; i < 4; i++) {
        if (hand_cards[i].getRang() == hand_cards[i + 1].getRang() &&
            hand_cards[i].getRang() == hand_cards[i + 2].getRang() &&
            hand_cards[i].getRang() == hand_cards[i + 3].getRang()
            )
                return true;
        }   
    return false;
}


bool hand::is_full_house(hand hand_board)
{
    hand_cards.insert(hand_cards.end(), hand_board.hand_cards.begin(), hand_board.hand_cards.end());
    sort(hand_cards.begin(), hand_cards.end(), [](card& a, card& b) {
               return a.getRang() < b.getRang();
    });
    
}

bool hand::is_flush(hand hand_board)
{
    hand_cards.insert(hand_cards.end(), hand_board.hand_cards.begin(), hand_board.hand_cards.end());
    sort(hand_cards.begin(), hand_cards.end(), [](card& a, card& b) {
        return a.getCouleur() < b.getCouleur();
    });
    for (int i = 0; i < 3; i++) {
        if (hand_cards[i].getCouleur() == hand_cards[i + 1].getCouleur() &&
            hand_cards[i].getCouleur() == hand_cards[i + 2].getCouleur() &&
            hand_cards[i].getCouleur() == hand_cards[i + 3].getCouleur() &&
            hand_cards[i].getCouleur() == hand_cards[i + 4].getCouleur())
                return true;
    }
    return false;
    

}

bool hand::is_straight(hand hand_board)
{
    hand_cards.insert(hand_cards.end(), hand_board.hand_cards.begin(), hand_board.hand_cards.end());
    sort(hand_cards.begin(), hand_cards.end(), [](card& a, card& b) {
        return a.getCouleur() < b.getCouleur() ||
               (a.getCouleur() == b.getCouleur() && a.getRang() < b.getRang());
    });
    for (int i = 0; i < 3; i++) {
        if (
            (hand_cards[i].getRang() == hand_cards[i + 1].getRang() - 1 &&
            hand_cards[i].getRang() == hand_cards[i + 2].getRang() - 2 &&
            hand_cards[i].getRang() == hand_cards[i + 3].getRang() - 3 &&
            hand_cards[i].getRang() == hand_cards[i + 4].getRang() - 4 &&
            hand_cards[i+4].getRang() != 12) || 
            (hand_cards[i].getRang() == 0 &&
            hand_cards[i+1].getRang() == 1 &&
            hand_cards[i+2].getRang() == 2 &&
            hand_cards[i+3].getRang() == 3 &&
            hand_cards[i+4].getRang() == 12))
            {
            return true;
        }   
    }
    return false;
}


bool hand::is_3_of_a_kind(hand hand_board)
{
    hand_cards.insert(hand_cards.end(), hand_board.hand_cards.begin(), hand_board.hand_cards.end());
    sort(hand_cards.begin(), hand_cards.end(), [](card& a, card& b) {
               return a.getRang() < b.getRang();
    });

    for (int i = 0; i < 5; i++) {
        if (hand_cards[i].getRang() == hand_cards[i + 1].getRang() &&
            hand_cards[i].getRang() == hand_cards[i + 2].getRang())
                return true;
        }   
    return false;
}

bool hand::is_two_pairs(hand hand_board)
{
    hand_cards.insert(hand_cards.end(), hand_board.hand_cards.begin(), hand_board.hand_cards.end());
    sort(hand_cards.begin(), hand_cards.end(), [](card& a, card& b) {
               return a.getRang() < b.getRang();
    });   
    int cpt = 0;
    for (int i = 0; i < 6; i++) {
        if (hand_cards[i].getRang() == hand_cards[i+1].getRang()) {
            cpt++;
            i++;//on skip la paire (2 incrémentation : l'incrémentation du if et du for)
        }
    }
    if(cpt == 2) 
        return true;
    else
        return false;  
}

bool hand::is_one_pair(hand hand_board)
{
    hand_cards.insert(hand_cards.end(), hand_board.hand_cards.begin(), hand_board.hand_cards.end());
    sort(hand_cards.begin(), hand_cards.end(), [](card& a, card& b) {
               return a.getRang() < b.getRang();
    });
    for (int i = 0; i < 6; i++) {
        if (hand_cards[i].getRang() == hand_cards[i+1].getRang()) {
            return true;
        }
    }
    return false;
}

bool hand::is_high_card(hand hand_board)
{

}
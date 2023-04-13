#include "player.hpp"

namespace ariel
{

    Player::Player(string name) {
        this->name = name;
        number_of_cards_won = 0;
    }

    /*
     * returns the name of this player.
     */
    string Player::getName() {
        return this->name;
    }

    /*
     * prints the amount of cards left. after 5 rounds should be 21 but can be less if a draw was played.
     */
    int Player::stacksize() {
        return hand.size();
    }

    /*
     * prints the amount of cards this player has won. 
     */
    int Player::cardesTaken() {
        return number_of_cards_won;
    }

    Card Player::playCardFromHand() {
        Card ret = hand.front();
        hand.pop();
        return ret;
    } 

    void Player::addCardToHand(Card card) {
        hand.push(card);
    }
}
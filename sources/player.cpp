#include "player.hpp"

#include <algorithm>
#include <vector>

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

    /*
     * returns the top card from the player's hand.
     */
    Card Player::playCardFromHand() {
        Card ret = hand.front();
        hand.pop();
        return ret;
    } 

    /*
     * adds a card to the player's hand.
     */
    void Player::addCardToHand(Card card) {
        hand.push(card);
    }

    /*
     * shuffles the cards in the player's hand.
     */
    void Player::shuffleHand() {
        vector<Card> cards_vector;
        while (!hand.empty()) {
            cards_vector.push_back(hand.front());
            hand.pop();
        }

        random_shuffle(cards_vector.begin(), cards_vector.end());
        
        for (Card card: cards_vector) {
            hand.push(card);
        }
    }
}
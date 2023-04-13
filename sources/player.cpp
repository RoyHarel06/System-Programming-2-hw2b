#include "player.hpp"

#include <algorithm>
#include <vector>

namespace ariel
{

    Player::Player(string name) {
        name = name;
        number_of_cards_won = 0;
        in_game = false;
    }

    /*
     * returns true if the player is in a game.
     */
    bool Player::isInGame() {
        return in_game;
    }

    /*
     * sets in_game to true and returns true on success, if the player is in a game will return false.
     */
    bool Player::joinGame() {
        if (in_game)
            return false;
        
        in_game = true;
        return true;
    }

    /*
     * returns the name of this player.
     */
    string Player::getName() {
        return name;
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
     * increases the number of cards won by x.
     */
    void Player::takeCard(int x) {
        number_of_cards_won += x;
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
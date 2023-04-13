#include "player.hpp"

#include <algorithm>

namespace ariel
{

    Player::Player(string name) {
        this->name = name;
        this->number_of_cards_won = 0;
        this->in_game = false;
    }

    /*
     * returns true if the player is in a game.
     */
    bool Player::isInGame() {
        return this->in_game;
    }

    /*
     * sets in_game to true and returns true on success, if the player is in a game will return false.
     */
    bool Player::joinGame() {
        if (this->in_game)
            return false;
        
        this->in_game = true;
        return true;
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
        return this->number_of_cards_won;
    }

    /*
     * increases the number of cards won by x.
     */
    void Player::takeCards(int card_pool) {
        this->number_of_cards_won += card_pool;
    }

    /*
     * returns the top card from the player's hand.
     */
    Card& Player::playCardFromHand() {
        Card& ret = this->hand.back();
        this->hand.pop_back();
        return ret;
    }

    /*
     * adds a card to the player's hand.
     */
    void Player::addCardToHand(const Card& card) {
        this->hand.push_back(card);
    }

    /*
     * shuffles the cards in the player's hand.
     */
    void Player::shuffleHand() {
        random_shuffle(this->hand.begin(), this->hand.end());
    }
}
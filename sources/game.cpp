#include "game.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

namespace ariel
{
    Game::Game(Player& player1_, Player& player2_): player1(player1_), player2(player2_) {
        if (this->player1.getName().empty())
            throw std::invalid_argument("Player 1 has no name.");
        if (this->player2.getName().empty())
            throw std::invalid_argument("Player 2 has no name.");

        // according to test this should throw in play turn...
        //if (player1.getName() == player2.getName())
        //    throw std::invalid_argument("Same player.");

        if (this->player1.stacksize() != 0 || this->player1.cardesTaken() != 0)
            throw std::invalid_argument("Player 1 has cards.");
        if (this->player2.stacksize() != 0 || this->player2.cardesTaken() != 0)
            throw std::invalid_argument("Player 2 has cards.");

        if (this->player1.isInGame())
            throw std::invalid_argument("Player 1 is in a game!");
        if (this->player2.isInGame())
            throw std::invalid_argument("Player 2 is in a game!");

        dealCards();

        this->player1.joinGame();
        this->player2.joinGame();

        this->turn = 0;
        this->draw_counter = 0;
        this->game_ended = false;
    }

    /*
     * returns the number of turns played in the game so far.
     */
    int Game::getNumberOfTurns() {
        return this->turn;
    }

    /*
     * deals a pack of cards to the two players.
     */
    void Game::dealCards() {
        vector<Card> cards;
        for (int value = 1; value <= 13; value++)
        {
            for(string suit: {"Hearts", "Spades", "Clubs", "Diamonds"})
            {
                cards.push_back(Card(value, suit));
            }
        }
        random_shuffle(cards.begin(), cards.end());

        for (int i = 0; i < 26; i++)
        {
            this->player1.addCardToHand(cards.back());
            cards.pop_back();
            this->player2.addCardToHand(cards.back());
            cards.pop_back();
        }

        this->player1.shuffleHand();
        this->player2.shuffleHand();
    }

    /*
     * plays the next turn in the game and logs the results.
     */
    void Game::playTurn() {
        // according to test this should throw here...
        if (player1.getName() == player2.getName())
            throw std::invalid_argument("Same player.");

        if (game_ended == true)
            throw std::logic_error("The game ended.");

        if (player1.stacksize() == 0 || player2.stacksize() == 0)
            game_ended = true;
        else
        {
            turn++;

            string log_entry = war(0);
            log.push(log_entry);
        }
    }

    /*
     * implements the main logic of the game and returns the log.
     */
    string Game::war(int cards_won) {
        string log_entry = "";

        Card player1_card = player1.playCardFromHand();
        Card player2_card = player2.playCardFromHand();

        log_entry += player1.getName() + " played " + to_string(player1_card.getValue()) + " of " + player1_card.getSuit() + " ";
        log_entry += player2.getName() + " played " + to_string(player2_card.getValue()) + " of " + player2_card.getSuit() + ".";

        if (player1_card.getValue() > player2_card.getValue()) {
            player1.takeCards(cards_won + 2);
            log_entry += " " + player1.getName() + " wins.";
        }
        else if (player1_card.getValue() < player2_card.getValue()) {
            player2.takeCards(cards_won + 2);
            log_entry += " " + player2.getName() + " wins.";
        }
        else {
            draw_counter++;

            log_entry += " Draw. ";

            if (player1.stacksize() == 0) {
                player1.takeCards(cards_won/2 + 1);
                player2.takeCards(cards_won/2 + 1);

                log_entry += "No more cards.";
            }
            else if (player1.stacksize() == 1) {
                player1.playCardFromHand();
                player2.playCardFromHand();

                player1.takeCards(cards_won/2 + 2);
                player2.takeCards(cards_won/2 + 2);

                log_entry += "No more cards.";
            }
            else {
                player1.playCardFromHand();
                player2.playCardFromHand();

                log_entry += war(cards_won + 4);
            }
        }

        return log_entry;
    }

    /*
     * playes the game untill the end.
     */
    void Game::playAll() {
        while (game_ended == false) {
            playTurn();
        }
    }

    std::string Game::getWinner() {
        if (turn == 0)
            throw std::logic_error("The game hasn't started yet.");
        
        else if (player1.cardesTaken() > player2.cardesTaken())
            return player1.getName();
        else if (player1.cardesTaken() < player2.cardesTaken())
            return player2.getName();
        else
            return player1.getName() + " and " + player2.getName();
    }

    /*
     * prints the name of the currently winning player.
     */
    void Game::printWiner() {
        cout << getWinner() << " won!\n";
    }

    /*
     * print the last turn stats. For example:
     * 1) Alice played Queen of Hearts Bob played 5 of Spades. Alice wins.
     * 2) Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 10 of Diamonds.
     *    Draw. Alice played Jack of Clubs Bob played King of Diamonds. Bob wins.
     */
    void Game::printLastTurn() {
        if (turn == 0)
            throw logic_error("The game hasn't started yet.");

        cout << log.back() << "\n";
    }

    /*
     * prints the contents of a queue.
     */
    void printQueue(queue<string> queue) {
        int counter = 1;
        while (!queue.empty()) {
            cout << "Turn " << counter << ": " << queue.front() << "\n";
            queue.pop();
            counter++;
        }
    }

    /*
     * prints all the turns played one line per turn (same format as game.printLastTurn()).
     */
    void Game::printLog() {
        if (turn == 0)
            throw logic_error("The game hasn't started yet.");

        cout << "Game log:\n";
        printQueue(log);
    }

    /*
     * for each player prints basic statistics: win rate, cards won, <other stats you want to print>.
     * Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws.)
     */
    void Game::printStats() {
        if (turn == 0)
            throw logic_error("The game hasn't started yet.");
        else {
            int total = player1.cardesTaken() + player2.cardesTaken();
            total /= 2;

            cout << player1.getName() << "'s stats:\n";
            cout << "Win rate: " << (((double)player1.cardesTaken() / 2)/total) * 100 << "%\n";
            cout << "Cards won: " << player1.cardesTaken() << "\n\n";

            cout << player2.getName() << "'s stats:\n";
            cout << "Win rate: " << (((double)player2.cardesTaken() / 2)/total) * 100 << "%\n";
            cout << "Cards won: " << player2.cardesTaken() << "\n\n";
        
            cout << "Draw rate: " << ((double)draw_counter / turn) * 100 << "%\n";
            cout << "Draw counter: " << draw_counter << "\n";
        }
    }
}
#include "game.hpp"

#include <iostream>
#include <random>

namespace ariel
{
    Game::Game(Player player1, Player player2): player1(player1), player2(player2) {
        if (player1.getName().empty())
            throw std::invalid_argument("Player 1 has no name.");
        if (player2.getName().empty())
            throw std::invalid_argument("Player 2 has no name.");

        if (player1.getName() == player2.getName())
            throw std::invalid_argument("Same player.");

        if (player1.stacksize() != 0 || player1.cardesTaken() != 0)
            throw std::invalid_argument("Player 1 has cards.");
        if (player2.stacksize() != 0 || player2.cardesTaken() != 0)
            throw std::invalid_argument("Player 2 has cards.");

        if (player1.isInGame())
            throw std::invalid_argument("Player 1 is in a game!");
        if (player2.isInGame())
            throw std::invalid_argument("Player 2 is in a game!");

        player1.joinGame();
        player2.joinGame();

        this->turn = 0;
        this->draw_counter = 0;
        this->game_ended = false;
    }

    /*
     * returns the number of turns played in the game so far.
     */
    int Game::getNumberOfTurns() {
        return turn;
    }

    /*
     * deals a pack of cards to the two players.
     */
    void Game::dealCards() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 2);

        for (int value = 1; value <= 12; value++)
        {
            for(string suit: {"Hearts", "Spades", "Clubs", "Diamonds"})
            {
                Card temp(value, suit);
                if (dist(gen) == 1)
                    player1.addCardToHand(temp);
                else
                    player2.addCardToHand(temp);
            }
        }

        player1.shuffleHand();
        player2.shuffleHand();
    }

    /*
     * plays the next turn in the game and logs the results.
     */
    void Game::playTurn() {
        if (game_ended == true)
            throw std::logic_error("The game ended.");

        if (turn == 0)
            dealCards();

        if (player1.stacksize() == 0 || player2.stacksize() == 0)
            game_ended = true;
        else
        {
            turn++;

            // Alice played 6 of Hearts Bob played 6 of Spades. Draw. Alice played 10 of Clubs Bob played 11 of Diamonds. Bob wins.
            string log_entry = "";

            int cards_won = 0;

            Card player1_card = player1.playCardFromHand();
            Card player2_card = player2.playCardFromHand();

            log_entry += player1.getName() + " played " + to_string(player1_card.getValue()) + " of " + player1_card.getSuit() + " ";
            log_entry += player2.getName() + " played " + to_string(player2_card.getValue()) + " of " + player2_card.getSuit() + ".";

            if (player1_card.getValue() > player2_card.getValue()) {
                player1.takeCard(cards_won + 2);
                log_entry += " " + player1.getName() + " wins.";
            }
            else if (player1_card.getValue() < player2_card.getValue()) {
                player2.takeCard(cards_won + 2);
                log_entry += " " + player2.getName() + " wins.";
            }
            else {
                log_entry += " Draw. ";

                cards_won += 2;

                // TODO: check number of cards to see if can draw more, if not share the spoils
                // TODO: make this logic into  a recursive func!

                // facedown cards:
                player1.playCardFromHand();
                player2.playCardFromHand();

                cards_won += 2;
            }
        }
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
        else if (game_ended == false)
            throw std::logic_error("The game hasn't ended yet.");
        
        else if (player1.stacksize() > player2.stacksize())
            return player1.getName();
        else if (player1.stacksize() < player2.stacksize())
            return player2.getName();
        else
            return player1.getName() + " and " + player2.getName();
    }

    /*
     * prints the name of the winning player.
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
            cout << player1.getName() << "'s stats:\n";
            cout << "Win rate: " << (player1.cardesTaken() / 26) * 100 << "%\n";
            cout << "Cards won: " << player1.cardesTaken() << "\n\n";

            cout << player2.getName() << "'s stats:\n";
            cout << "Win rate: " << (player2.cardesTaken() / 26) * 100 << "%\n";
            cout << "Cards won: " << player2.cardesTaken() << "\n\n";
        
            cout << "Draw rate: " << ((double)draw_counter / turn) * 100 << "%\n";
            cout << "Draw counter: " << draw_counter << "\n";
        }
    }
}
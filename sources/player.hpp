#pragma once

#include "card.hpp"

#include <string>
#include <vector>
using namespace std;

namespace ariel
{
    class Player
    {
        private:
            string name;
            vector<Card> hand;
            int number_of_cards_won;
            bool in_game;

        public:
            Player(string name);

            string getName();

            bool isInGame();
            bool joinGame();

            int stacksize();
            int cardesTaken();

            void takeCards(int card_pool);

            Card& playCardFromHand();
            void addCardToHand(const Card& card);

            void shuffleHand();
    };
}
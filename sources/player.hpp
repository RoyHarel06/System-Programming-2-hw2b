#pragma once

#include "card.hpp"

#include <string>
#include <queue>
using namespace std;

namespace ariel
{
    class Player
    {
        private:
            string name;
            queue<Card> hand;
            int number_of_cards_won;
            bool in_game;

        public:
            Player(string name);

            string getName();

            bool isInGame();
            bool joinGame();

            int stacksize();
            int cardesTaken();

            void takeCard(int x);

            Card playCardFromHand();
            void addCardToHand(Card card);

            void shuffleHand();
    };
}
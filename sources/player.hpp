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

        public:
            Player(string name);

            string getName();

            int stacksize();
            int cardesTaken();

            Card playCardFromHand();
            void addCardToHand(Card card);
    };
}
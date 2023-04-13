#pragma once

#include "player.hpp"
#include <queue>

using namespace std;

namespace ariel
{
    class Game
    {
        private:
            Player& player1;
            Player& player2;
            int turn;
            int draw_counter;
            queue<string> log;
            bool game_ended;

            void dealCards();
            string war(int cards_won);
            
        public:
            Game(Player& player1_, Player& player2_);

            string getWinner();
            
            int getNumberOfTurns();
            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();
    };
}
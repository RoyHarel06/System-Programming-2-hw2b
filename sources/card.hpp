#pragma once

#include <string>
using namespace std;

namespace ariel
{
    class Card
    {
        private:
            int value;
            string suit;
            
        public:
            Card(int value, string suit);
            int getValue();
            std::string getSuit();

            // Operators are used to compare two card's values!
            bool operator==(const Card& other) const;
            bool operator>(const Card& other) const;
            bool operator<(const Card& other) const;
    };
}
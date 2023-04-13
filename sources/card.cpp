#include "card.hpp"
#include <stdexcept>

namespace ariel
{
    Card::Card(int value, string suit) {
        if (value < 1 || value > 13)
            throw std::invalid_argument("Value is out of range.");
            
        if (suit != "Hearts" && suit != "Spades" && suit != "Diamonds" && suit != "Clubs")
            throw std::invalid_argument("Suit needs to be one of the following: Clubs, Spades, Diamonds, Hearts.");

        this->value = value;
        this->suit = suit;
    }
    int Card::getValue() {
        return this->value;
    }
    string Card::getSuit() {
        return suit;
    }

    bool Card::operator==(const Card& other) const {
        return value == other.value;
    }
    bool Card::operator>(const Card& other) const {
        if (value == 1 && other.value != 2)
            return true;
        return value > other.value;
    }
    bool Card::operator<(const Card& other) const {
        if (value != 2 && other.value == 1)
            return true;
        return value < other.value;
    }
}
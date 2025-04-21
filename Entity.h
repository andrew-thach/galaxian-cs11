#ifndef ENTITY__H
#define ENTITY__H

#include <string>

// These function prototypes are implemented inline, so no need for a ".cpp" file.
class Entity {
    public:
        Entity() {
            setX(0);
            setY(0);
            setSymbol(".");
        }

        Entity(int newX, int newY, std::string newSymbol) {
            setX(newX);
            setY(newY);
            setSymbol(newSymbol);
        }

        int getX() const {return x;}
        int getY() const {return y;}
        std::string getSymbol() const {return symbol;}

        void setX(int newX) {x = newX;}
        void setY(int newY) {y = newY;}
        void setSymbol(std::string newSymbol) {symbol = newSymbol;}

        void moveUp() {y--;}
        void moveDown() {y++;}

        void moveLeft() {x--;}
        void moveRight() {x++;}

    private:
        int x;
        int y;
        std::string symbol;
};

#endif

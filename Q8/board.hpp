#ifndef BOARD_HPP
#define BOARD_HPP

#include <pthread.h>
#include <iostream>
#include "singleton.hpp"

using namespace std;

// Singleton class for the board
class Board : public Singleton {
protected:
    static int (*board)[4];  // 2D array of 4x4

    Board();  // Constructor
    virtual ~Board();  // Destructor

public:
    // Delete copy constructor and assignment operator
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    static Board& getInstance();  // Singleton getter

    // Implementations of the pure virtual function from Singleton
    virtual void action() override;
    void printBoard();
};

#endif // BOARD_HPP

#ifndef BOARD_HPP
#define BOARD_HPP

#include <pthread.h>
#include <iostream>
#include "singleton.hpp"

using namespace std;

// Singleton class for the board
class Board : public Singleton {
protected:
    static pthread_mutex_t* mutex;
    static int (*board)[4];  // 2D array of 4x4

    Board();  // Constructor
    virtual ~Board();  // Destructor

public:
    // Delete copy constructor and assignment operator
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    static Board& getInstance();  // Singleton getter

    // Implementations of the pure virtual functions from Singleton
    virtual void changeBoard() override;
    virtual void printBoard() override;
};

#endif // BOARD_HPP

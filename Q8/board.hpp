#ifndef BOARD_HPP
#define BOARD_HPP

#include <pthread.h>
#include <iostream>

using namespace std;

// Singleton base class for the board
class Board {
protected:
    static pthread_mutex_t* mutex;
    static int (*board)[4];  // 2D array of 4x4

    Board();  // Constructor
    virtual ~Board();  // Destructor

public:
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    static Board& getInstance();  // Singleton getter
    virtual void changeBoard();  // Method to modify the board
    void printBoard();  // Method to print the board
};

#endif // BOARD_HPP

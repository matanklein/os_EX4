#include <pthread.h>
#include "board.hpp"
#include <unistd.h>
#include <cstdio>
#include <iostream>

using namespace std;

// Client function to simulate the client updating the board
void* client(void* arg) {
    Board& board = Board::getInstance();
    char command;

    while (true) {
        cout << "Client, input 'c' to change the board or 'q' to quit: ";
        cin >> command;

        if (command == 'q') {
            break;  // Exit the client
        } else if (command == 'c') {
            cout << "Changing board..." << endl;
            board.changeBoard();
            board.printBoard();
        } else {
            cout << "Invalid input. Please enter 'c' to change or 'q' to quit." << endl;
        }
    }

    return nullptr;
}

int main() {
    Board& board = Board::getInstance();

    // Creating one client thread
    pthread_t client_thread;
    pthread_create(&client_thread, nullptr, client, nullptr);
    
    // Wait for the client thread to finish
    pthread_join(client_thread, nullptr);

    // Print the final board state
    cout << "Final board state:" << endl;
    board.printBoard();

    return 0;
}

#include <pthread.h>
#include "board.hpp"
#include <unistd.h>
#include <iostream>

using namespace std;

void* client(void* arg) {
    Board& board = Singleton::getInstance<Board>();;
    char command;

    while (true) {
        cout << "Client, input 'c' to change the board or 'q' to quit: ";
        cin >> command;

        if (command == 'q') {
            break;  // Exit the client
        } else if (command == 'c') {
            board.runAction();  // Use the thread-safe runAction to modify the board
            board.printBoard();
        } else {
            cout << "Invalid input. Please enter 'c' to change or 'q' to quit." << endl;
        }
    }

    return nullptr;
}

int main() {
    Board& board = Singleton::getInstance<Board>();;

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

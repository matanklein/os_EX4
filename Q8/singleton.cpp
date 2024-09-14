#include <pthread.h>
#include <iostream>
#include <vector>

using namespace std;

// Singleton base class for the board
class Board {
protected:
    static pthread_mutex_t mutex;
    vector<vector<int>> board = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

    Board(){ pthread_mutex_init(&mutex,nullptr); }

    virtual ~Board(){ pthread_mutex_destroy(&mutex); }

public:
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    static Board& getInstance() {
        static Board* instance = nullptr;
        pthread_mutex_lock(&mutex);  // Locking for thread safety
        if (!instance) {
            instance = new Board();  // Create instance if doesn't exist
        }
        pthread_mutex_unlock(&mutex);  // Unlock after creation
        return *instance;
    }

    virtual void changeBoard() {
        pthread_mutex_lock(&mutex);  // Lock mutex
        int i, j;
        cout << "Change the board:" << endl;
        cin >> i >> j;
        board[i][j] = !board[i][j];
        cout << "Board updated at [" << i << "][" << j << "]" << endl;
        printBoard();
        pthread_mutex_unlock(&mutex);  // Unlock mutex
    }

    void printBoard() {
        pthread_mutex_lock(&mutex);  // Lock mutex
        for (const auto& row : board) {
            for (int cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
        pthread_mutex_unlock(&mutex);  // Unlock mutex
    }
};

pthread_mutex_t Board::mutex;

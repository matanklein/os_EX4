#include "board.hpp"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int (*Board::board)[4] = nullptr;  // Pointer to a 2D array of size 4x4

Board::Board() {
    // Create shared memory for board
    int shm_fd = shm_open("/board_mem", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(int) * 4 * 4);

    // Map shared memory to board (4x4 array of integers)
    board = static_cast<int(*)[4]>(mmap(0, sizeof(int) * 4 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    if (board == nullptr) {
        cerr << "Failed to map shared memory for board" << endl;
        exit(EXIT_FAILURE);
    }

    memset(board, 0, sizeof(int) * 4 * 4);  // Initialize board to 0
}

Board::~Board() {
    munmap(board, sizeof(int) * 4 * 4);
}

Board& Board::getInstance() {
    static Board instance;
    return instance;
}

void Board::action() {
    int i, j;
    cout << "Change the board (input i j): ";
    cin >> i >> j;

    if (i >= 0 && i < 4 && j >= 0 && j < 4) {  // Ensure indices are valid
        board[i][j] = !board[i][j];  // Toggle board value
        cout << "Board updated at [" << i << "][" << j << "]" << endl;
    } else {
        cout << "Invalid indices, must be between 0 and 3." << endl;
    }
}

void Board::printBoard() {
    cout << "Printing board:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

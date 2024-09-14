#include "board.hpp"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

pthread_mutex_t* Board::mutex = nullptr;
int (*Board::board)[4] = nullptr;  // Pointer to a 2D array of size 4x4

Board::Board() {
    // Create shared memory for board and mutex
    int shm_fd = shm_open("/board_mem", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(int) * 4 * 4);

    // Map shared memory to board (4x4 array of integers)
    board = static_cast<int(*)[4]>(mmap(0, sizeof(int) * 4 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    if (board == nullptr) {
        cerr << "Failed to map shared memory for board" << endl;
        exit(EXIT_FAILURE);
    }

    // Initialize the board with zeros if necessary
    memset(board, 0, sizeof(int) * 4 * 4);

    // Initialize mutex in shared memory
    int shm_mutex_fd = shm_open("/mutex_mem", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_mutex_fd, sizeof(pthread_mutex_t));
    mutex = static_cast<pthread_mutex_t*>(mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_mutex_fd, 0));

    // Check if mutex needs initialization
    static bool mutex_initialized = false;
    if (!mutex_initialized) {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);  // Set mutex to be shared between processes
        pthread_mutex_init(mutex, &attr);
        pthread_mutexattr_destroy(&attr);
        mutex_initialized = true;
    }
}

Board::~Board() {
    munmap(board, sizeof(int) * 4 * 4);
    munmap(mutex, sizeof(pthread_mutex_t));
}

Board& Board::getInstance() {
    static Board instance;
    return instance;
}

void Board::changeBoard() {
    cout << "Attempting to lock mutex..." << endl;
    pthread_mutex_lock(mutex);  // Lock mutex
    cout << "Mutex locked." << endl;

    int i, j;
    cout << "Change the board (input i j): ";
    cin >> i >> j;

    if (i >= 0 && i < 4 && j >= 0 && j < 4) {  // Ensure indices are valid
        board[i][j] = !board[i][j];  // Toggle board value
        cout << "Board updated at [" << i << "][" << j << "]" << endl;
    } else {
        cout << "Invalid indices, must be between 0 and 3." << endl;
    }

    cout << "Unlocking mutex..." << endl;
    pthread_mutex_unlock(mutex);  // Unlock mutex
    cout << "Mutex unlocked." << endl;
}

void Board::printBoard() {
    pthread_mutex_lock(mutex);  // Lock mutex
    cout << "Printing board:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    pthread_mutex_unlock(mutex);  // Unlock mutex
}

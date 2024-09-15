#include <iostream>
#include <thread>
#include <mutex>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

class Guard {
public:
    Guard(std::mutex& mtx) : mutex(mtx) {
        mutex.lock(); // Lock the mutex when the Guard is created
    }

    ~Guard() {
        mutex.unlock(); // Unlock the mutex when the Guard is destroyed
    }

private:
    std::mutex& mutex; // Mutex reference
};

class BankAccount {
public:
    BankAccount(int balance) : balance(balance) {}

    void withdraw(int clientSocket) {
        Guard guard(accountMutex); // Lock the mutex for this critical section
        int amount;
        read(clientSocket, &amount, sizeof(amount));  // Read withdrawal amount
        if (amount <= 0) {
            std::cerr << "Invalid amount!" << std::endl;
            return;
        }
        if (amount > balance) {
            std::cerr << "Insufficient funds!" << std::endl;
            return;
        }
        balance -= amount;
        std::cout << "Withdrawal of " << amount << " successful. New balance: " << balance << std::endl;
    }

    // Get current balance safely
    int getBalance() {
        Guard guard(accountMutex); // Lock the mutex for this critical section
        return balance;
    }

private:
    int balance;
    std::mutex accountMutex;
};

// Function to handle each client
void handleClient(int clientSocket, BankAccount &account) {
    char buffer[256];
    while (true) {
        bzero(buffer, 256);
        read(clientSocket, buffer, 255);  // Read client command

        if (buffer[0] == 'q') {
            std::cout << "Client disconnected" << std::endl;
            close(clientSocket);
            break;
        } else if (buffer[0] == 'w') {
            account.withdraw(clientSocket);  // Withdraw from account
            int newBalance = account.getBalance();
            write(clientSocket, &newBalance, sizeof(newBalance));  // Send updated balance
        } else {
            std::cerr << "Invalid command received from client" << std::endl;
        }
    }
}

int main() {
    BankAccount account(100);  // Shared bank account

    // Create a server socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return 1;
    }

    // Bind the server to a port
    sockaddr_in serverAddr;
    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(5000);

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error on binding" << std::endl;
        return 1;
    }

    // Listen for clients
    listen(serverSocket, 5);
    std::cout << "Server listening on port 5000" << std::endl;

    // Accept clients in a loop
    sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    while (true) {
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &clientLen);
        if (clientSocket < 0) {
            std::cerr << "Error on accept" << std::endl;
            return 1;
        }

        // Handle client in a separate thread
        std::thread clientThread(handleClient, clientSocket, std::ref(account));
        clientThread.detach();
    }

    close(serverSocket);
    return 0;
}

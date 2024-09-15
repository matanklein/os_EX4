#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Create a client socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Error opening socket" << std::endl;
        return 1;
    }

    // Connect to the server
    sockaddr_in serverAddr;
    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    char command;
    int amount, newBalance;

    while (true) {
        std::cout << "Enter 'w' to withdraw or 'q' to quit: ";
        std::cin >> command;

        if (command == 'q') {
            write(clientSocket, &command, sizeof(command));  // Send quit command to server
            break;
        } else if (command == 'w') {
            write(clientSocket, &command, sizeof(command));  // Send withdraw command to server
            std::cout << "Enter amount to withdraw: ";
            std::cin >> amount;
            write(clientSocket, &amount, sizeof(amount));  // Send amount to server

            // Receive updated balance
            read(clientSocket, &newBalance, sizeof(newBalance));
            std::cout << "Updated balance: " << newBalance << std::endl;
        } else {
            std::cerr << "Invalid command!" << std::endl;
        }
    }

    close(clientSocket);
    return 0;
}

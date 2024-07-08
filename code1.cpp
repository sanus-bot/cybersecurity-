#include <iostream>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

// Function to check if a port is open
bool isPortOpen(const std::string& host, int port) {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket\n";
        return false;
    }

    server = gethostbyname(host.c_str());
    if (server == nullptr) {
        std::cerr << "No such host\n";
        close(sockfd);
        return false;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        close(sockfd);
        return false;
    }

    close(sockfd);
    return true;
}

int main() {
    std::string host;
    std::vector<int> common_ports = {21, 22, 23, 25, 80, 110, 443, 8080};  // Common ports

    std::cout << "Enter the hostname or IP address: ";
    std::cin >> host;

    std::cout << "Checking for open ports on " << host << "...\n";

    for (int port : common_ports) {
        if (isPortOpen(host, port)) {
            std::cout << "Port " << port << " is open. Potential threat detected.\n";
        } else {
            std::cout << "Port " << port << " is closed.\n";
        }
    }

    std::cout << "Threat identification completed.\n";

    return 0;
}

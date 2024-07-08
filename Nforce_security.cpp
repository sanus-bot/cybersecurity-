#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <ctime>

// Function to get current date and time as a string
std::string getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::localtime(&now));
    return std::string(buf);
}

// Class to manage user authentication
class UserManager {
private:
    std::unordered_map<std::string, std::string> users; // Stores username and password

public:
    UserManager() {
        // Pre-defined users (username, password)
        users["admin"] = "admin123";
        users["user"] = "user123";
    }

    // Function to authenticate user
    bool authenticate(const std::string& username, const std::string& password) {
        if (users.find(username) != users.end() && users[username] == password) {
            logActivity(username, "Login successful");
            return true;
        }
        logActivity(username, "Login failed");
        return false;
    }

    // Function to log user activity
    void logActivity(const std::string& username, const std::string& activity) {
        std::ofstream logFile("security_log.txt", std::ios_base::app);
        logFile << getCurrentDateTime() << " - " << username << ": " << activity << std::endl;
    }
};

int main() {
    UserManager userManager;
    std::string username, password;

    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (userManager.authenticate(username, password)) {
        std::cout << "Access granted. Welcome, " << username << "!" << std::endl;
    } else {
        std::cout << "Access denied. Invalid credentials." << std::endl;
    }

    return 0;
}
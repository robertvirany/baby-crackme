#include <iostream>
#include <cstring>

int main() {
    char input[100];

    std::cout << "Enter password: ";
    std::cin.getline(input, 100);

    if (std::strcmp(input, "password") == 0) {
        std::cout << "Access granted!\n";
    } else {
     std::cout << "Access denied!\n";
    }

    return 0;
}
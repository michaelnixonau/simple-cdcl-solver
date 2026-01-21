#include <fstream>
#include <string>
#include <iostream>

// 45

int main() {
    std::ifstream in("samples/count.txt");
    if (!in) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    std::string line;
    int count = 0;
    while (std::getline(in, line)) {
        count += std::stoi(line);
    }
    std::cout << count << std::endl;
}
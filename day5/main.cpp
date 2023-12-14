#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <format>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

// Brayden Hill - Day 5

int main() {
    std::string input = "input.txt";
    // std::string input = "test.txt";
    std::ifstream inputFile(input);
    int total = 0;

    // Load the game board
    std::string line;
    while (std::getline(inputFile, line)) {
        for (int i = 0; i < line.length(); i++){
            int ch = (int)line.at(i);
            std::string current_num = "";

            if (ch > 47 && ch < 58){
                current_num += line.at(i);
            } 
             if ((ch == 32 && current_num != "") || i == (line.length()-1)){
                current_num = "";
            }
        }

    }
    inputFile.close();

    std::cout << std::format("{}", total) << std::endl;
}

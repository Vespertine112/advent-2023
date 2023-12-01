#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <format>
#include <unordered_map>

// Brayden Hill

int main() {
    std::string input = "input.txt";
    std::ifstream inputFile(input);
    uint64_t total = 0;

    std::unordered_map<std::string, int> digits = {
        {"one",   1},
        {"two",   2},
        {"three", 3},
        {"four",  4},
        {"five",  5},
        {"six",   6},
        {"seven", 7},
        {"eight", 8},
        {"nine",  9},
    };

    std::string line;
    while (std::getline(inputFile, line)) {
        bool l = false;
        bool r = false;
        int sub = 0;
        for(int i = 0; i < line.length(); i++){
            int left = int(line[i]);
            int right = int(line[line.length()-1-i]);
            // First parse check, preempts second check
            if (((left > 47 && left < 58)) && !l){
                sub += ((left-48)*10);
                l = true;
            }
            if (right > 47 && right < 58 && !r){
                sub += (right-48);
                r = true;
            }

            for (auto && pair : digits){
                if ((line.substr(i, pair.first.length()) == pair.first) && !l){
                    sub += (pair.second*10);
                    l = true;
                }
                if ((line.substr(line.length()-1-i, pair.first.length()) == pair.first) && !r){
                    sub += (pair.second);
                    r = true;
                }
            }
        }
        total += sub;
    }

    std::cout << total << std::endl;
    inputFile.close();
}

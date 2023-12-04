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

// Brayden Hill - Day 4

int main() {
    std::string input = "input.txt";
    // std::string input = "test.txt";
    std::ifstream inputFile(input);
    std::map<int,int> mult_map;

    int total = 0;

    // Load the game board
    std::string line;
    while (std::getline(inputFile, line)) {
        int pt = 8;
        std::vector<int> win_nums;
        std::vector<int> game_nums;

        std::string current_num = "";
        bool win_mode = false;
        int game_number = std::stoi(line.substr(5,3));
        if (mult_map.find(game_number) == mult_map.end()){
            mult_map[game_number] = 1;
        } else {
            mult_map[game_number] +=1;
        }

        // Parse loop for winning / game numbers
        for (int i = pt; i < line.length(); i++){
            int ch = (int)line.at(i);

            if (ch > 47 && ch < 58){
                current_num += line.at(i);
            } 
             if ((ch == 32 && current_num != "") || i == (line.length()-1)){
                if (win_mode){
                    game_nums.push_back(std::stoi(current_num));
                } else {
                    win_nums.push_back(std::stoi(current_num));
                }
                current_num = "";
            } else if (ch == 124){
                win_mode = true;
                current_num = "";
            }
        }

        int game_score = 1;
        int number_won = 0;
        bool game_won=false;
        // Part 1 accumulation
        for (auto && wnum : win_nums){
                if (std::find(game_nums.begin(), game_nums.end(), wnum) != game_nums.end()){
                    game_score *= (!game_won) ? 1 : 2;
                    number_won++;
                    game_won=true;
                }
        }
        if (game_won) total+=game_score;

        // Set scratchcard copies
        for (int i = 1; i < number_won+1; i++){
            if (mult_map.find(game_number+i) == mult_map.end()){
                mult_map[game_number+i] = mult_map[game_number];
            } else {
                mult_map[game_number+i] += mult_map[game_number];
            }
        }

    }
    inputFile.close();

    // Summing total scratches
    int total_scratches = 0;
    for (auto && [k,v]:mult_map){
        total_scratches+=v;
    }

    std::cout << std::format("{}, {}", total, total_scratches) << std::endl;
}

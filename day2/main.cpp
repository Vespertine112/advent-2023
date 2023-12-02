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
    uint64_t game_id_total = 0;
    uint64_t game_power_total = 0;

    std::unordered_map<std::string, uint16_t> pairs = {
        {"red", 12},
        {"green", 13},
        {"blue", 14},
    };

    std::unordered_map<std::string, uint16_t> neutral_pairs = {
        {"red", 0},
        {"green", 0},
        {"blue", 0},
    };

    std::string line;
    while (std::getline(inputFile, line)) {
        // Extract game id
        std::string game_id = "";
        int g_idx = 4;
        while (int(line[g_idx]) != 58){
            game_id += line[g_idx];
            g_idx++;
        }

        // Cycle a sub game & check if permitted by bag levels
        std::string color_total = "";
        bool invalid_game = false;
        std::unordered_map<std::string, uint16_t> sub_game_pair = neutral_pairs;
        for (int idx = g_idx; idx < line.length(); idx++){
            int pt = int(line[idx]);
            // Read Number
            if (pt > 47 && pt < 58){
                color_total += line[idx];
            } else if (pt == 32){
                // Space -> Check for color validation
                for (auto & [str,clr] : pairs){
                    if (line.substr(idx+1, str.length()) == str){
                        if ((clr - std::stoi(color_total)) < 0){
                            invalid_game = true;
                        } 
                        if (std::stoi(color_total) > sub_game_pair[str]){
                            sub_game_pair.at(str) = std::stoi(color_total);
                        }
                    }
                }
            } else if (pt == 44 || pt == 59){
                // Reset color total on comma or semi
                color_total = "";
            }
        }
        // Calculate the results
        if (!invalid_game){
            game_id_total += std::stoi(game_id);
        }
        int mult = 1;
        for (auto & [str, clr] : sub_game_pair){
            mult*=clr;
        }
        game_power_total += mult;


    }

    std::cout << std::format("Game Id sum: {} \nGame Power Total: {}",game_id_total, game_power_total) << std::endl;
    inputFile.close();
}

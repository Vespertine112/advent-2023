#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <format>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>

// Brayden Hill - gah dam this ugly

int main() {
    std::string input = "input.txt";
    std::ifstream inputFile(input);

    std::vector<std::string> game_board;
    std::map<std::pair<int, int>, std::set<int>> gears;
    int game_total = 0;
    int gears_total = 0;

    // Load the game board
    std::string line;
    while (std::getline(inputFile, line)) {
        game_board.push_back(line);
    }
    inputFile.close();

    for (int i = 0; i < game_board.size(); i++){
        std::string line = game_board.at(i);
        std::string local_num = "";
        bool valid_number = false;
        for (int j = 0; j < line.length(); j++){
            int pt = int(line.at(j));
            if (pt > 47 && pt < 58){
                local_num += line.at(j);
            } 

            if (!(pt > 47 && pt < 58) || (j == line.length()-1)){
                // Perform local search for symbol
                int pt_i = j-local_num.length();
                for (auto && ch : local_num){
                    for (int i_dx = -1; i_dx <= 1; i_dx++){
                        for (int j_dx = -1; j_dx <= 1; j_dx++){
                            if ((i + i_dx) > game_board.size()-1) continue;
                            if ((pt_i + j_dx) > line.length()-1) continue;
                            int t_ch = (int)game_board.at((i + i_dx) < 0 ? 0 : (i + i_dx)).at((pt_i + j_dx) < 0 ? 0 : (pt_i + j_dx));
                            if (!(t_ch > 47 && t_ch < 58) && !(t_ch == 46)){
                                valid_number = true;
                            } 

                            if (t_ch == 42){
                                gears[std::make_pair((i + i_dx),(pt_i + j_dx))].insert(std::stoi(local_num));
                            }
                        }
                    }
                    pt_i++;
                }

                if (valid_number){
                    auto t = std::stoi(local_num);
                    game_total += t;
                    valid_number = false;
                }
                local_num = "";
            }
        }
    }

    // Gears calculation
    for (auto && [_, nums] : gears){
        int gt_s = 1;
        if (nums.size() > 1){
            for (auto num : nums){
                gt_s *= num;
            }
            gears_total+= gt_s;
        }
    }

    std::cout << std::format("{}\n{}", game_total, gears_total) << std::endl;

}

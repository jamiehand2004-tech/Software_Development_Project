#include "../Header_Files/team_reader.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::cerr;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string RESET = "\033[0m";

// Function to load squads from a file
// Expects file format where each squad is represented by a text line,
// followed by a line with an integer option count, then that many option lines,
// and a separator line "----". Returns an empty vector on error.
vector<Squad> loadSquad(const string & filename) {
    vector<Squad> squads;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << RED << "Error opening file: " << filename << endl << RESET;
        return squads; // Return empty vector on failure
    }

    while (true){
        Squad squad;
        if (!getline(file, squad.text)) {
            break; // End of file or error
        }

        int optionsCount;
        if (!(file >> optionsCount)) {
            cerr << RED << "Error reading options count for squad: " << squad.text << endl << RESET;
            break; // Error reading options count
        }
        file.ignore(); // Ignore the rest of the line

        if (optionsCount<=0) break;


        squad.options.clear();
        for (int i = 0; i < optionsCount; ++i) {
            string option;
            if (!getline(file, option)) {
                cerr << RED << "Error reading option " << i + 1 << " for squad: " << squad.text << endl << RESET;
                break; // Error reading option
            }
            squad.options.push_back(option);
        }

        string separator;
        if (!getline(file, separator) || separator != "----") {
            cerr << RED << "Error reading separator after squad: " << squad.text << endl << RESET;
            break; // Error reading separator
        }

        squads.push_back(squad);
    }
    return squads;
}
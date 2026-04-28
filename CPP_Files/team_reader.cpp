// Include the Squad declarations and function prototype being implemented here.
#include "../Header_Files/team_reader.h"
// Include iostream for error output.
#include <iostream>
// Include fstream for file input.
#include <fstream>
// Include vector because the function returns a vector of squads.
#include <vector>

// Bring commonly used standard-library names into local scope.
using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::cerr;

// ANSI escape sequence used for red error text.
const string RED = "\033[31m";
// ANSI escape sequence used for green success text.
const string GREEN = "\033[32m";
// ANSI escape sequence used to restore the console colour.
const string RESET = "\033[0m";

// Load all squads from a text file into a vector.
vector<Squad> loadSquad(const string & filename) {
    // Store every squad successfully read from the file.
    vector<Squad> squads;
    // Open the named file for input.
    ifstream file(filename);

    // If the file cannot be opened, report the problem and return an empty result.
    if (!file.is_open()) {
        cerr << RED << "Error opening file: " << filename << endl << RESET;
        return squads;
    }

    // Keep reading squads until the file ends or a format error occurs.
    while (true) {
        // Prepare one squad object for the next record.
        Squad squad;
        // Read the squad name line.
        if (!getline(file, squad.text)) {
            // Stop when no more squad names can be read.
            break;
        }

        // Store how many option lines belong to this squad.
        int optionsCount;
        // Read the option count value from the next line.
        if (!(file >> optionsCount)) {
            // Report a malformed option count and stop parsing.
            cerr << RED << "Error reading options count for squad: " << squad.text << endl << RESET;
            break;
        }
        // Discard the trailing newline after the numeric count.
        file.ignore();

        // Reject non-positive option counts as invalid input.
        if (optionsCount <= 0) {
            break;
        }

        // Clear the options vector before filling it.
        squad.options.clear();
        // Read each option line one by one.
        for (int i = 0; i < optionsCount; ++i) {
            // Store the text of the current option.
            string option;
            // Read the option text line.
            if (!getline(file, option)) {
                // Report that the option line was missing or malformed.
                cerr << RED << "Error reading option " << i + 1 << " for squad: " << squad.text << endl << RESET;
                break;
            }
            // Append the successfully read option to the squad.
            squad.options.push_back(option);
        }

        // Store the separator line that should end this record.
        string separator;
        // Verify that the record ends with the expected separator.
        if (!getline(file, separator) || separator != "----") {
            // Report a malformed separator and stop parsing.
            cerr << RED << "Error reading separator after squad: " << squad.text << endl << RESET;
            break;
        }

        // Add the successfully parsed squad to the result vector.
        squads.push_back(squad);
    }
    // Return every squad that was successfully read.
    return squads;
}
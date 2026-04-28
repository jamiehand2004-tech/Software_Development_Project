// Prevent duplicate inclusion of the squad reader declarations.
#ifndef TEAM_READER_H
#define TEAM_READER_H

// Provide stream declarations used by the reader implementation.
#include <iostream>
// Provide std::string for squad names and options.
#include <string>
// Provide std::vector for storing squad options.
#include <vector>

// Bring std::string into local scope for shorter declarations.
using std::string;
// Bring std::vector into local scope for shorter declarations.
using std::vector;

// Represent one squad loaded from a file.
struct Squad {
    // Store the squad name or main text label.
    string text;
    // Store the options associated with the squad.
    vector<string> options;
};

// Load all squads from the named file.
vector<Squad> loadSquad(const string & filename);

// End the include guard started at the top of the file.
#endif
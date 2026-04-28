// Include the TeamSystem declarations being implemented here.
#include "../Header_Files/team_system.h"

// Include STL algorithms for std::sort and std::find_if.
#include <algorithm>
// Include fstream for saving teams to disk.
#include <fstream>
// Include iostream for user prompts and error messages.
#include <iostream>
// Include limits for safe input-buffer clearing.
#include <limits>
// Include ios for append mode constants.
#include <ios>

// Bring commonly used standard-library names into local scope.
using std::string;
using std::vector;
using std::ofstream;
using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::ios;

// ANSI escape sequence used for red error text.
const string RED = "\033[31m";
// ANSI escape sequence used for green success text.
const string GREEN = "\033[32m";
// ANSI escape sequence used to restore the console colour.
const string RESET = "\033[0m";

// Sort the internal team list alphabetically by squad text.
void TeamSystem::sortTeamsByName() {
    // Use std::sort with a lambda that compares the squad names.
    std::sort(teams.begin(), teams.end(),
        [](const Squad & left, const Squad & right) {
            return left.text < right.text;
        });
}

// Load every team from a file into the internal container.
void TeamSystem::loadFromFile(const string & filename) {
    // Remove any teams already stored before loading fresh data.
    teams.clear();
    // Read each squad from disk and insert it through addTeam().
    for (const Squad & team : loadSquad(filename)) {
        addTeam(team);
    }
}

// Save the current teams to a file.
void TeamSystem::saveToFile(const string & filename) {

    // Open the named file for output.
    std::ofstream file(filename);
    // If the file cannot be opened, print an error and stop.
    if (!file.is_open()) {
        std::cerr << RED << "Error opening file for writing: " << filename << std::endl << RESET;
        return;
    }

    // Write each stored team in the simple text format used by the project.
    for (const auto& team : teams) {
        // Write the team name.
        file << team.text << std::endl;
        // Write the number of option lines.
        file << team.options.size() << std::endl;
        // Write each option line.
        for (const auto& option : team.options) {
            file << option << std::endl;
        }
        // Write the record separator.
        file << "----" << std::endl;
    }
}

// Add one team to the system, validating the request first.
void TeamSystem::addTeam(const Squad & team) {
    // Reject empty team names with a custom exception.
    if (team.text.empty()) {
        throw TeamSystemException("Team name cannot be empty.");
    }

    // Reject duplicate team names with a custom exception.
    if (findTeam(team.text) != nullptr) {
        throw TeamSystemException("Team already exists: " + team.text);
    }

    // Append the new team to the container.
    teams.push_back(team);
    // Keep the internal container sorted after insertion.
    sortTeamsByName();
}

// Find a mutable team by name.
Squad* TeamSystem::findTeam(const string & teamName) {
    // Search for the first squad with a matching name.
    auto it = std::find_if(teams.begin(), teams.end(),
        [&teamName](const Squad &team) {
            return team.text == teamName;
        });

    // Return nullptr if no matching team exists.
    if (it == teams.end()) {
        return nullptr;
    }

    // Return a pointer to the matching squad.
    return &(*it);
}

// Find a const team by name.
const Squad* TeamSystem::findTeam(const string & teamName) const {
    // Search for the first squad with a matching name.
    auto it = std::find_if(teams.begin(), teams.end(),
        [&teamName](const Squad &team) {
            return team.text == teamName;
        });

    // Return nullptr if no matching team exists.
    if (it == teams.end()) {
        return nullptr;
    }

    // Return a pointer to the matching squad.
    return &(*it);
}

// Interactively create a team and append it to a file.
void TeamSystem::addingTeam(const string & filename) {
    // Open the destination file in append mode.
    ofstream file(filename, ios::app);
    // If the file cannot be opened, print an error and stop.
    if (!file.is_open()) {
        cerr << RED << "Error opening file for appending: " << filename << endl << RESET;
        return;
    }

    // Prepare a new squad object to fill from user input.
    Squad newTeam;

    // Prompt for the team name.
    cout << "Enter the team name: ";
    // Read the team name line.
    getline(cin, newTeam.text);

    // Store how many option lines the user wants to add.
    int optionsCount;
    // Prompt for the number of options.
    cout << "Enter the number of options for the team: ";
    // Read the numeric option count.
    cin >> optionsCount;
    // Clear the leftover newline from the input buffer.
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Read each option line from the user.
    for (int i = 0; i < optionsCount; ++i) {
        // Store the current option text.
        string option;
        // Prompt for the option text.
        cout << "Enter option " << i + 1 << ": ";
        // Read the option text line.
        getline(cin, option);
        // Append the option to the new team.
        newTeam.options.push_back(option);
    }

    // Validate and add the team to the in-memory container.
    addTeam(newTeam);

    // Write the team name to disk.
    file << newTeam.text << endl;
    // Write the number of options to disk.
    file << newTeam.options.size() << endl;
    // Write each option line to disk.
    for (const string & option : newTeam.options) {
        file << option << endl;
    }
    // Write the separator line that ends this record.
    file << "----" << endl;
}
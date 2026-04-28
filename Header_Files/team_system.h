// Prevent duplicate inclusion of the team-system declarations.
#ifndef TEAM_SYSTEM_H
#define TEAM_SYSTEM_H

// Provide stream declarations used by the implementation.
#include <iostream>
// Provide std::runtime_error for the custom exception type.
#include <stdexcept>
// Provide std::string for team names and messages.
#include <string>
// Provide std::vector for squad storage.
#include <vector>

// Include the Squad type and load helper used by TeamSystem.
#include "../Header_Files/team_reader.h"

// Bring std::string into local scope for shorter declarations.
using std::string;
// Bring std::vector into local scope for shorter declarations.
using std::vector;

// Define a custom exception for invalid team-system operations.
class TeamSystemException : public std::runtime_error {
public:
    // Construct the exception with a descriptive message.
    explicit TeamSystemException(const string & message)
        : std::runtime_error(message) {}
};

// Define the TeamSystem class that manages multiple squads.
class TeamSystem {
private:

    // Store all loaded or created teams.
    vector<Squad> teams;

    // Sort the stored teams alphabetically by name.
    void sortTeamsByName();

public:

    // Use the compiler-generated default constructor.
    TeamSystem() = default;

    // Load teams from a file into the internal container.
    void loadFromFile(const string & filename);
    // Save teams from the internal container to a file.
    void saveToFile(const string & filename);
    // Add one team to the system.
    void addTeam(const Squad & teamName);
    // Interactively add a team and append it to a file.
    void addingTeam(const string & teamName);
    // Find a mutable team by name.
    Squad* findTeam(const string & teamName);
    // Find a const team by name.
    const Squad* findTeam(const string & teamName) const;
    // Return a const reference to the stored teams.
    const vector<Squad>& getTeams() const { return teams; }
    // Return the number of stored teams.
    int getTeamCount() const { return static_cast<int>(teams.size()); }
};

// End the include guard started at the top of the file.
#endif
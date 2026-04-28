// Captain: lightweight wrapper representing a team's captain and helpers.
#ifndef CAPTAIN_H
#define CAPTAIN_H

// Provide stream types used by inline getters and display helpers.
#include <iostream>
// Provide std::string for captain names and function parameters.
#include <string>

// Bring commonly used standard-library names into this header's scope.
using std::string;
using std::cout;
using std::endl;

// Forward declarations avoid including full class definitions here.
class Team;
class Hero;

class Captain {

private:

    // Store the captain's display name.
    std::string captainName;
    // Remember which team this captain wrapper is associated with.
    Team* team;
    // Track how many captain wrappers have been created in a given context.
    int captainCount = 0;

public:
    // Build a captain with default placeholder values.
    Captain();
    // Build a captain with a supplied name, team pointer, and optional count.
    Captain(const string &name, Team* t, int count = 1);

    // Return the stored captain name.
    string getCaptainName() const { return captainName; }
    // Return the team pointer currently associated with the captain.
    Team* getTeam() const { return team; }
    // Return the stored captain count value.
    int getCaptainCount() const { return captainCount; }

    // Replace the stored captain name.
    void setCaptainName(const string &n) { captainName = n; }
    // Replace the associated team pointer.
    void setTeam(Team* t) { team = t; }
    // Replace the stored captain count value.
    void setCaptainCount(int count) { captainCount = count; }

    // Report whether more than one captain has been created.
    bool isMultipleCaptains();
    // Print the captain and team summary to the console.
    void displayCaptainInfo();
    // Assign a hero and team as captain data.
    void assignCaptain(Hero hero, Team* team);
};

#endif
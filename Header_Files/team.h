// Describe the Team type, which stores and manages a group of heroes.

// Prevent duplicate inclusion of this header.
#ifndef TEAM_H
#define TEAM_H

// Provide standard stream declarations for save and load functions.
#include <iostream>
// Provide std::string for team names and hero lookup names.
#include <string>
// Provide std::vector for hero storage.
#include <vector>

// Include Hero because Team stores heroes directly by value.
#include "../Header_Files/hero.h"

// Bring std::string into local scope for shorter declarations.
using std::string;
// Bring std::vector into local scope for shorter declarations.
using std::vector;

// Define the Team class used by the application and menu system.
class Team {

private:
    // Store the team's display name.
    string teamName;
    // Store the heroes that belong to this team.
    vector<Hero> teamHeroes;
    // Store the current number of heroes.
    int heroCount = 0;
    // Limit the maximum number of heroes allowed on one team.
    const static int MAX_HEROES = 10;
    // Store a team count value kept by the existing design.
    int teamCount = 0;

    // Keep heroCount aligned with the current vector size.
    void syncHeroCount() { heroCount = static_cast<int>(teamHeroes.size()); }

public:

    // Return the stored team name.
    string getTeamName() const { return teamName; }
    // Return a mutable pointer to the first hero, or nullptr if the team is empty.
    Hero* getHeroes() { return teamHeroes.empty() ? nullptr : teamHeroes.data(); }
    // Return a const pointer to the first hero, or nullptr if the team is empty.
    const Hero* getHeroes() const { return teamHeroes.empty() ? nullptr : teamHeroes.data(); }
    // Return the current hero count.
    int getHeroCount() const { return heroCount; }

    // Replace the team name.
    void setTeamName(string tn) { teamName = tn; }
    // Replace the stored heroes from a raw hero array.
    void setHeroes(Hero* h);
    // Replace the stored hero count value directly.
    void setHeroCount(int cnt) { heroCount = cnt; }

    // Add one hero to the team.
    void addHero(Hero h);

    // Display a short summary of the team.
    void displayTeamInfo() const;
    // Display a detailed summary of every hero in the team.
    void displayFullTeamInfo() const;
    // Display the captain information for the team.
    void displayCaptainInfo() const;
    // Find a mutable hero by name.
    Hero* findHero(const string &heroName);
    // Find a const hero by name.
    const Hero* findHero(const string &heroName) const;
    // Find the mutable hero currently marked as captain.
    Hero* findCaptain();
    // Find the const hero currently marked as captain.
    const Hero* findCaptain() const;

    // Remove a hero from the team by name.
    bool removeHeroByName(const string &heroName);
    // Remove captain status from a named hero.
    bool removeCaptainStatusFromHero(const string &heroName);
    // Sort the heroes alphabetically.
    void sortHeroesAlphabetically();
    // Compare teams alphabetically by team name.
    bool operator<(const Team& other) const { return teamName < other.teamName; }

    // Save the team to an output stream.
    void save(std::ostream &os) const;
    // Load the team from an input stream.
    bool load(std::istream &is);

    // Construct an empty team.
    Team();
    // Construct a team with a supplied name.
    Team(string tn);
    // Construct a team with a supplied name, hero array, and count.
    Team(string tn, Hero* h, int cnt);
};

// End the include guard started at the top of the file.
#endif
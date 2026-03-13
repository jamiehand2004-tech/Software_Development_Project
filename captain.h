#ifndef CAPTAIN_H
#define CAPTAIN_H

#include <iostream>
#include <string>

// Forward declarations to avoid circular dependencies
class Team;
class Hero;

class Captain {

private:

    std::string captainName;
    Team* team;
    int captainCount = 0;

public:
// Constructors
    Captain();
    Captain(const std::string &name, Team* t, int count = 1);

// Getters
    std::string getCaptainName() const { return captainName; }
    Team* getTeam() const { return team; }
    int getCaptainCount() const { return captainCount; }

// Setters
    void setCaptainName(const std::string &n) { captainName = n; }
    void setTeam(Team* t) { team = t; }
    void setCaptainCount(int count) { captainCount = count; }

// General functions    
    bool isMultipleCaptains();
    void displayCaptainInfo();
    void assignCaptain(Hero hero, Team* team);
};

#endif
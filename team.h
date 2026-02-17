/*  Header file for the Team class, which represents a team of heroes in a Hero-Agency-Management project. 
    The Team class includes member variables for the team name,
    an array of Hero objects,
    and the count of heroes in the team. 
    It also includes member functions to set and get these variables,
    as well as functions to add a hero to the team
    display information about the team and its captain.
*/


#pragma once
#include <iostream>
#include <string>
#include "hero.h"
#include "captain.h"

using namespace std;

class Team {// Team class definition

private:// Private member variables

    string teamName;// Name of the team
    Hero* heroes;// Pointer to an array of Hero objects
    int heroCount;// Number of heroes in the team
    const static int MAX_HEROES = 10;// Maximum number of heroes allowed in a team
    int teamCount = 0;// Static variable to keep track of the number of teams created
    Hero teamHeroes[MAX_HEROES];// Array to store heroes in the team

public:// Public member functions

    Team();// Default constructor
    Team(string tn);// Constructor that takes a team name
    Team(string tn, Hero* h, int cnt);// Constructor that takes a team name, an array of heroes, and the count of heroes
    Team(string tn, const static int maxH, Hero* h, int cnt);// Constructor that takes a team name, maximum number of heroes, an array of heroes, and the count of heroes

    void setTeamName(string tn) {teamName = tn;} // Setter for team name
    string getTeamName() {return teamName;} // Getter for team name

    void setHeroes(Hero* h) {heroes = h;} // Setter for heroes array
    Hero* getHeroes() {return heroes;} // Getter for heroes array

    void setHeroCount(int cnt) {heroCount = cnt;} // Setter for hero count
    int getHeroCount() {return heroCount;}  // Getter for hero count

    void addHero(Hero h); // Function to add a hero to the team
    void displayTeamInfo(); // Function to display information about the team
    void displayCaptainInfo(); // Function to display information about the captain of the team
    
};

Team::Team() { // Default constructor implementation

    teamName = "Unknown Team";  // Default team name
    heroCount = 0;  // Initialize hero count to 0
    heroes = new Hero[10]; // Assuming a maximum of 10 heroes per team

};


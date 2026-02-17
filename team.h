#pragma once
#include <iostream>
#include <string>
#include "hero.h"
#include "captain.h"

using namespace std;

class Team {

private:

    string teamName;
    Hero* heroes;
    int heroCount;
    const static int MAX_HEROES = 10;
    int teamCount = 0;
    Hero teamHeroes[MAX_HEROES];

public:
    Team();
    Team(string name);
    void addHero(Hero h);
    void displayTeamInfo();
    
};

Team::Team() {
    teamName = "Unknown Team";
    heroCount = 0;
    heroes = new Hero[10]; // Assuming a maximum of 10 heroes per team
}
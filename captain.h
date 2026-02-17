#pragma once

#include <iostream>
#include <string>
#include "hero.h"
#include "team.h"

using namespace std;

class Captain {

private:
    string captainName;
    Team* team;
    int captainCount = 0;
public:
    Captain();
    Captain(string name, Team* t);
    void setCaptainName(string n) { captainName = n;}
    string getCaptainName(){return captainName;}
    void setTeam(Team* t) {team = t;}
    Team* getTeam(){return team;}
    void displayCaptainInfo();
    
};

Captain::Captain() {
    captainName = "Unknown Captain";
    team = nullptr;
    captainCount++;
};
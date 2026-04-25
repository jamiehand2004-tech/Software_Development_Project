#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include "team.h"

using std::string;
using std::vector;

// NEW CODE: helper functions for the main menu so the fixes stay separate from your existing classes.
void showMainMenu();
void listTeamsFromMenu(const vector<Team>& teams);
bool addHeroToTeamFromMenu(vector<Team>& teams);
bool createTeamFromMenu(vector<Team>& teams);
bool deleteTeamFromMenu(vector<Team>& teams);
bool deleteHeroFromTeamFromMenu(vector<Team>& teams);

#endif
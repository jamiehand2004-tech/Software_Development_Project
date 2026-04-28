// Prevent duplicate inclusion of the menu declarations.
#ifndef MENU_H
#define MENU_H

// Provide std::vector for collections of teams.
#include <vector>
// Provide std::string for prompt and name handling.
#include <string>

// Include Team because the menu helpers operate directly on team objects.
#include "team.h"

// Bring std::string into local scope for shorter declarations.
using std::string;
// Bring std::vector into local scope for shorter declarations.
using std::vector;

// Show the top-level main menu options.
void showMainMenu();
// Show the submenu for team management actions.
void showTeamManagementMenu();
// Show the submenu for hero management actions.
void showHeroManagementMenu();

// List teams and allow the user to inspect one of them.
void listTeamsFromMenu(const vector<Team>& teams);

// Create a new team from interactive menu input.
bool createTeamFromMenu(vector<Team>& teams);
// Rename an existing team from interactive menu input.
bool renameTeamFromMenu(vector<Team>& teams);
// Delete a selected team from interactive menu input.
bool deleteTeamFromMenu(vector<Team>& teams);
// Sort the team list alphabetically.
bool sortTeamsFromMenu(vector<Team>& teams);

// Add a hero to a selected team.
bool addHeroToTeamFromMenu(vector<Team>& teams);
// Delete a hero from a selected team.
bool deleteHeroFromTeamFromMenu(vector<Team>& teams);
// Remove captain status from a selected hero.
bool removeCaptainFromHeroFromMenu(vector<Team>& teams);
// Sort heroes within one selected team.
bool sortHeroesInTeamFromMenu(vector<Team>& teams);
// Display the full details of one selected team.
void viewFullTeamInfoFromMenu(const vector<Team>& teams);

// Open the project README from the menu system.
void openReadMeFromMenu();

// End the include guard started at the top of the file.
#endif

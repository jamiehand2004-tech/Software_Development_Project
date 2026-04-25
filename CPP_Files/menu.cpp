#include "../Header_Files/menu.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <cstddef>
#include <windows.h>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
//code to display red text
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string RESET = "\033[0m";

// NEW CODE: prints the menu in one place so it is easier to maintain.
void showMainMenu() {
    cout << "\nMenu:\n"
         << " (1) List teams\n"
         << " (2) Add hero to team\n"
         << " (3) Save state\n"
         << " (4) Load state\n"
         << " (5) Exit\n"
         << " (6) Create Team\n"
         << " (7) Delete Team\n"
         << " (8) Delete Hero From Team\n"
         << "-> ";
}

// NEW CODE: list only team number and team name, then let the user choose one team to view.
void listTeamsFromMenu(const std::vector<Team>& teams) {
    if (teams.empty()) {
        cout << "No teams available.\n";
        return;
    }

    cout << "==============================" << endl;
    cout << "        AVAILABLE TEAMS       " << endl;
    cout << "==============================" << endl;

    for (std::size_t i = 0; i < teams.size(); ++i) {
        cout << "[" << (i + 1) << "] " << teams[i].getTeamName() << endl;
    }

    cout << "[0] Return" << endl;
    cout << "------------------------------" << endl;

    std::size_t displayedIndex = 0;
    cout << "Enter team number to view: ";

    if (!(cin >> displayedIndex)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Invalid input.\n" << RESET;
        return;
    }

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (displayedIndex == 0) {
        return;
    }

    if (displayedIndex > teams.size()) {
        cout << RED << "Invalid team number.\n" << RESET;
        return;
    }

    const Team& selectedTeam = teams[displayedIndex - 1];

    cout << "\n==============================" << endl;
    cout << "        TEAM DETAILS          " << endl;
    cout << "==============================" << endl;

    // NEW CODE: show the selected team's full details only.
    selectedTeam.displayFullTeamInfo();
    cout << "------------------------------" << endl;
    selectedTeam.displayCaptainInfo();
    cout << "==============================" << endl;
}

// NEW CODE: keeps team selection consistent with the numbers shown in the list menu.
bool addHeroToTeamFromMenu(std::vector<Team>& teams) {
    if (teams.empty()) {
        cout << "No teams available. Create a team first.\n";
        return false;
    }

    cout << "==============================" << endl;
    cout << "        AVAILABLE TEAMS       " << endl;
    cout << "==============================" << endl;

    for (std::size_t i = 0; i < teams.size(); ++i) {
        cout << "[" << (i + 1) << "] " << teams[i].getTeamName() << endl;
    }

    std::size_t displayedIndex = 0;
    cout << "Enter team number: ";
    if (!(cin >> displayedIndex)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Invalid input.\n" << RESET;
        return false;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (displayedIndex == 0 || displayedIndex > teams.size()) {
        cout << RED << "Invalid team number.\n" << RESET;
        return false;
    }

    std::size_t realIndex = displayedIndex - 1;

    std::string name;
    int health = 0;
    int attack = 0;
    std::string weakness;
    char isCap = 'n';

    cout << "Hero name: ";
    getline(cin, name);

    cout << "Health: ";
    if (!(cin >> health)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Invalid health value.\n" << RESET;
        return false;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Attack: ";
    if (!(cin >> attack)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Invalid attack value.\n" << RESET;
        return false;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Weakness: ";
    getline(cin, weakness);

    cout << "Is captain? (y/n): ";
    cin >> isCap;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Hero h(name, health, attack, weakness, (isCap == 'y' || isCap == 'Y'), true);
    teams[realIndex].addHero(h);
    cout << GREEN << "Hero added.\n" << RESET;
    return true;
}

// NEW CODE: implements menu option 6 without changing the Team class itself.
bool createTeamFromMenu(std::vector<Team>& teams) {
    std::string teamName;

    cout << "Enter team name: ";
    getline(cin, teamName);

    if (teamName.empty()) {
        cout << "Team name cannot be empty.\n";
        return false;
    }

    for (std::size_t i = 0; i < teams.size(); ++i) {
        if (teams[i].getTeamName() == teamName) {
            cout << "A team with that name already exists.\n";
            return false;
        }
    }

    Team newTeam(teamName);
    teams.push_back(newTeam);
    cout << GREEN << "Team created successfully.\n" << RESET;
    return true;
}

// NEW CODE: deletes a team using the same displayed numbering as the list menu.
bool deleteTeamFromMenu(std::vector<Team>& teams) {
    if (teams.empty()) {
        cout << "No teams available.\n";
        return false;
    }
    cout <<"enter exit to not delete a team.\n";
    cout << "==============================" << endl;
    cout << "        AVAILABLE TEAMS       " << endl;
    cout << "==============================" << endl;

    for (std::size_t i = 0; i < teams.size(); ++i) {
        cout << "[" << (i + 1) << "] " << teams[i].getTeamName() << endl;
    }

    std::size_t displayedIndex = 0;
    cout << "Enter team number to delete: ";
    if (!(cin >> displayedIndex)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Invalid input.\n" << RESET;
        return false;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (displayedIndex == 0 || displayedIndex > teams.size()) {
        cout << RED << "Invalid team number.\n" << RESET;
        return false;
    }

    const std::string deletedName = teams[displayedIndex - 1].getTeamName();
    teams.erase(teams.begin() + (displayedIndex - 1));
    cout << GREEN << "Deleted team: " << deletedName << endl << RESET;
    return true;
}

// NEW CODE: deletes a hero from a chosen team by hero name.
bool deleteHeroFromTeamFromMenu(std::vector<Team>& teams) {
    if (teams.empty()) {
        cout << "No teams available.\n";
        return false;
    }

    cout << "==============================" << endl;
    cout << "        AVAILABLE TEAMS       " << endl;
    cout << "==============================" << endl;

    for (std::size_t i = 0; i < teams.size(); ++i) {
        cout << "[" << (i + 1) << "] " << teams[i].getTeamName() << endl;
    }

    std::size_t displayedIndex = 0;
    cout << "Enter team number: ";
    if (!(cin >> displayedIndex)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << RED << "Invalid input.\n" << RESET;
        return false;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (displayedIndex == 0 || displayedIndex > teams.size()) {
        cout << RED << "Invalid team number.\n" << RESET;
        return false;
    }

    Team &selectedTeam = teams[displayedIndex - 1];

    if (selectedTeam.getHeroCount() == 0) {
        cout << "That team has no heroes to delete.\n";
        return false;
    }

    cout << "Heroes in " << selectedTeam.getTeamName() << ":\n";
    const Hero* heroes = selectedTeam.getHeroes();

    for (int i = 0; i < selectedTeam.getHeroCount(); ++i) {
        cout << " - " << heroes[i].getHeroName() << endl;
    }

    std::string heroName;
    cout << "Enter hero name to delete: ";
    getline(cin, heroName);

    if (heroName.empty()) {
        cout << RED << "Hero name cannot be empty.\n" << RESET;
        return false;
    }

    if (!selectedTeam.removeHeroByName(heroName)) {
        cout << RED << "Hero not found in that team.\n" << RESET;
        return false;
    }

    cout << GREEN << "Hero deleted from team.\n" << RESET;
    return true;
}
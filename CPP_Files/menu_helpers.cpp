#include "../Header_Files/menu_helpers.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <cstddef>

using std::cin;
using std::cout;
using std::endl;
using std::getline;

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

// NEW CODE: fixed team listing so it starts at the first team and avoids copying Team objects.
void listTeamsFromMenu(const std::vector<Team>& teams) {
    if (teams.empty()) {
        cout << "No teams available.\n";
        return;
    }

    for (std::size_t i = 0; i < teams.size(); ++i) {
        cout << "-- Team [" << (i + 1) << "] --" << endl;

        // NEW CODE: use a const reference instead of copying the Team object.
        const Team& teamRef = teams[i];
        teamRef.displayTeamInfo();
        teamRef.displayCaptainInfo();
    }
}

// NEW CODE: keeps team selection consistent with the numbers shown in the list menu.
bool addHeroToTeamFromMenu(std::vector<Team>& teams) {
    if (teams.empty()) {
        cout << "No teams available. Create a team first.\n";
        return false;
    }

    listTeamsFromMenu(teams);

    std::size_t displayedIndex = 0;
    cout << "Enter team number: ";
    if (!(cin >> displayedIndex)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return false;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (displayedIndex == 0 || displayedIndex > teams.size()) {
        cout << "Invalid team number.\n";
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
        cout << "Invalid health value.\n";
        return false;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "Attack: ";
    if (!(cin >> attack)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid attack value.\n";
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
    cout << "Hero added.\n";
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
    cout << "Team created successfully.\n";
    return true;
}

// NEW CODE: deletes a team using the same displayed numbering as the list menu.
bool deleteTeamFromMenu(std::vector<Team>& teams) {
    if (teams.empty()) {
        cout << "No teams available.\n";
        return false;
    }

    listTeamsFromMenu(teams);

    std::size_t displayedIndex = 0;
    cout << "Enter team number to delete: ";
    if (!(cin >> displayedIndex)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return false;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (displayedIndex == 0 || displayedIndex > teams.size()) {
        cout << "Invalid team number.\n";
        return false;
    }

    const std::string deletedName = teams[displayedIndex - 1].getTeamName();
    teams.erase(teams.begin() + (displayedIndex - 1));
    cout << "Deleted team: " << deletedName << endl;
    return true;
}

// NEW CODE: deletes a hero from a chosen team by hero name.
bool deleteHeroFromTeamFromMenu(std::vector<Team>& teams) {
    if (teams.empty()) {
        cout << "No teams available.\n";
        return false;
    }

    listTeamsFromMenu(teams);

    std::size_t displayedIndex = 0;
    cout << "Enter team number: ";
    if (!(cin >> displayedIndex)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return false;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (displayedIndex == 0 || displayedIndex > teams.size()) {
        cout << "Invalid team number.\n";
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
        cout << "Hero name cannot be empty.\n";
        return false;
    }

    if (!selectedTeam.removeHeroByName(heroName)) {
        cout << "Hero not found in that team.\n";
        return false;
    }

    cout << "Hero deleted from team.\n";
    return true;
}
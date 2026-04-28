// Include the menu declarations being implemented here.
#include "../Header_Files/menu.h"

// Include iostream for prompts and status output.
#include <iostream>
// Include limits for safe input-buffer clearing.
#include <limits>
// Include string for names, prompts, and messages.
#include <string>
// Include vector because many helpers take team vectors by reference.
#include <vector>
// Include cstddef for std::size_t.
#include <cstddef>
// Include algorithm for sorting teams.
#include <algorithm>
// Include fstream for compatibility with the existing dependency structure.
#include <fstream>
// Include cstdlib for std::system on non-Windows platforms.
#include <cstdlib>

// Use Windows-specific APIs only when building on Windows.
#ifdef _WIN32
// Prevent Windows headers from defining min/max macros.
#ifndef NOMINMAX
#define NOMINMAX
#endif
// Include core Windows declarations.
#include <windows.h>
// Include ShellExecute declarations for opening the README.
#include <shellapi.h>
#endif

// Bring commonly used standard-library names into local scope.
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

// ANSI escape sequence used for red error text.
const string RED = "\033[31m";
// ANSI escape sequence used for green success text.
const string GREEN = "\033[32m";
// ANSI escape sequence used to restore the console colour.
const string RESET = "\033[0m";
// ANSI escape sequence used for cyan menu headings.
const string CYAN = "\033[36m";

// Print the top-level main menu.
void showMainMenu() {
    // Print each main menu option on its own line.
    cout << "\n" << CYAN << "========== MAIN MENU ==========" << RESET << endl
         << " (1) View Teams" << endl
         << " (2) Team Management" << endl
         << " (3) Hero Management" << endl
         << " (4) Save State" << endl
         << " (5) Load State" << endl
         << " (6) Help" << endl
         << " (7) Exit" << endl
         << "-> ";
}

// Print the team-management submenu.
void showTeamManagementMenu() {
    // Print each team-management option on its own line.
    cout << "\n" << CYAN << "====== TEAM MANAGEMENT ======" << RESET << endl
         << " (1) Create Team" << endl
         << " (2) Rename Team" << endl
         << " (3) Delete Team" << endl
         << " (4) Sort Teams A-Z" << endl
         << " (5) Return" << endl
         << "-> ";
}

// Print the hero-management submenu.
void showHeroManagementMenu() {
    // Print each hero-management option on its own line.
    cout << "\n" << CYAN << "====== HERO MANAGEMENT ======" << RESET << endl
         << " (1) Add Hero To Team" << endl
         << " (2) Delete Hero From Team" << endl
         << " (3) Remove Captain Status" << endl
         << " (4) Sort Heroes In Team A-Z" << endl
         << " (5) View Full Team Info" << endl
         << " (6) Return" << endl
         << "-> ";
}

// Print a numbered list of team names.
static void printTeamNameList(const std::vector<Team>& teams) {
    // Print one numbered line for each team in the vector.
    for (std::size_t i = 0; i < teams.size(); ++i) {
        cout << "[" << (i + 1) << "] " << teams[i].getTeamName() << endl;
    }
}

// Prompt the user to select one team index from a displayed list.
static bool selectTeamIndex(const std::vector<Team>& teams, std::size_t& selectedIndex, const string& promptText) {
    // Reject the request when no teams are available.
    if (teams.empty()) {
        cout << RED << "No teams available." << endl << RESET;
        return false;
    }

    // Print a heading for the team list.
    cout << "==============================" << endl;
    // Print the title line.
    cout << "        AVAILABLE TEAMS       " << endl;
    // Print a closing heading line.
    cout << "==============================" << endl;
    // Print the numbered team names.
    printTeamNameList(teams);
    // Print the return option.
    cout << "[0] Return" << endl;
    // Print a footer line.
    cout << "------------------------------" << endl;

    // Store the displayed index entered by the user.
    std::size_t displayedIndex = 0;
    // Print the caller-supplied prompt text.
    cout << promptText;

    // Validate that the user entered a number.
    if (!(cin >> displayedIndex)) {
        // Clear the stream error state.
        cin.clear();
        // Discard the invalid input line.
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        // Report the invalid input.
        cout << RED << "Invalid input." << endl << RESET;
        // Report failure to the caller.
        return false;
    }

    // Discard the newline after the numeric choice.
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    // Treat zero as a request to return without selecting a team.
    if (displayedIndex == 0) {
        return false;
    }

    // Reject out-of-range team numbers.
    if (displayedIndex > teams.size()) {
        cout << RED << "Invalid team number." << endl << RESET;
        return false;
    }

    // Convert the displayed 1-based number to a 0-based vector index.
    selectedIndex = displayedIndex - 1;
    // Report success to the caller.
    return true;
}

// Let the user select one team and display its summary.
void listTeamsFromMenu(const std::vector<Team>& teams) {
    // Store the selected vector index.
    std::size_t selectedIndex = 0;

    // Stop if the user does not select a valid team.
    if (!selectTeamIndex(teams, selectedIndex, "Enter team number to view: ")) {
        return;
    }

    // Bind a const reference to the chosen team.
    const Team& selectedTeam = teams[selectedIndex];

    // Print a heading for the team detail section.
    cout << "\n==============================" << endl;
    // Print the section title.
    cout << "        TEAM DETAILS          " << endl;
    // Print a closing heading line.
    cout << "==============================" << endl;
    // Print the selected team's summary.
    selectedTeam.displayTeamInfo();
    // Print the selected team's captain summary.
    selectedTeam.displayCaptainInfo();
    // Print a footer line.
    cout << "==============================" << endl;
}

// Prompt the user for a new hero and add it to a selected team.
bool addHeroToTeamFromMenu(std::vector<Team>& teams) {
    // Store the selected team index.
    std::size_t realIndex = 0;

    // Stop if the user does not select a valid team.
    if (!selectTeamIndex(teams, realIndex, "Enter team number: ")) {
        return false;
    }

    // Store the entered hero name.
    std::string name;
    // Store the entered health value.
    int health = 0;
    // Store the entered attack value.
    int attack = 0;
    // Store the entered weakness text.
    std::string weakness;
    // Store whether the hero should start as captain.
    char isCap = 'n';

    // Prompt for the hero name.
    cout << "Hero name: ";
    // Read the hero name.
    getline(cin, name);

    // Reject empty hero names.
    if (name.empty()) {
        cout << RED << "Hero name cannot be empty." << endl << RESET;
        return false;
    }

    // Prompt for the health value.
    cout << "Health: ";
    // Validate that the user entered a valid integer.
    if (!(cin >> health)) {
        cin.clear();
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        cout << RED << "Invalid health value." << endl << RESET;
        return false;
    }
    // Discard the newline after the numeric input.
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    // Prompt for the attack value.
    cout << "Attack: ";
    // Validate that the user entered a valid integer.
    if (!(cin >> attack)) {
        cin.clear();
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        cout << RED << "Invalid attack value." << endl << RESET;
        return false;
    }
    // Discard the newline after the numeric input.
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    // Prompt for the weakness text.
    cout << "Weakness: ";
    // Read the weakness text.
    getline(cin, weakness);

    // Prompt for captain status.
    cout << "Is captain? (y/n): ";
    // Read the captain-status response.
    cin >> isCap;
    // Discard the newline after the character input.
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    // Build the hero object from the entered values.
    Hero h(name, health, attack, weakness, (isCap == 'y' || isCap == 'Y'), true);
    // Add the new hero to the selected team.
    teams[realIndex].addHero(h);
    // Report success to the user.
    cout << GREEN << "Hero added." << endl << RESET;
    // Report success to the caller.
    return true;
}

// Prompt the user for a new team name and create the team.
bool createTeamFromMenu(std::vector<Team>& teams) {
    // Store the entered team name.
    std::string teamName;

    // Prompt for the team name.
    cout << "Enter team name: ";
    // Read the team name.
    getline(cin, teamName);

    // Reject empty team names.
    if (teamName.empty()) {
        cout << RED << "Team name cannot be empty." << endl << RESET;
        return false;
    }

    // Reject duplicate team names.
    for (std::size_t i = 0; i < teams.size(); ++i) {
        if (teams[i].getTeamName() == teamName) {
            cout << RED << "A team with that name already exists." << endl << RESET;
            return false;
        }
    }

    // Create the new team object.
    Team newTeam(teamName);
    // Append the new team to the vector.
    teams.push_back(newTeam);
    // Report success to the user.
    cout << GREEN << "Team created successfully." << endl << RESET;
    // Report success to the caller.
    return true;
}

// Prompt the user to rename an existing team.
bool renameTeamFromMenu(std::vector<Team>& teams) {
    // Store the selected team index.
    std::size_t teamIndex = 0;

    // Stop if the user does not select a valid team.
    if (!selectTeamIndex(teams, teamIndex, "Enter team number to rename: ")) {
        return false;
    }

    // Store the new team name.
    string newName;
    // Prompt for the new name.
    cout << "Enter new team name: ";
    // Read the new name.
    getline(cin, newName);

    // Reject empty team names.
    if (newName.empty()) {
        cout << RED << "Team name cannot be empty." << endl << RESET;
        return false;
    }

    // Reject duplicate names belonging to another team.
    for (std::size_t i = 0; i < teams.size(); ++i) {
        if (i != teamIndex && teams[i].getTeamName() == newName) {
            cout << RED << "A team with that name already exists." << endl << RESET;
            return false;
        }
    }

    // Apply the new name to the selected team.
    teams[teamIndex].setTeamName(newName);
    // Report success to the user.
    cout << GREEN << "Team renamed successfully." << endl << RESET;
    // Report success to the caller.
    return true;
}

// Delete a selected team from the vector.
bool deleteTeamFromMenu(std::vector<Team>& teams) {
    // Store the selected team index.
    std::size_t teamIndex = 0;

    // Stop if the user does not select a valid team.
    if (!selectTeamIndex(teams, teamIndex, "Enter team number to delete: ")) {
        return false;
    }

    // Store the name of the team being deleted for confirmation output.
    const std::string deletedName = teams[teamIndex].getTeamName();
    // Erase the selected team from the vector.
    teams.erase(teams.begin() + teamIndex);
    // Report success to the user.
    cout << GREEN << "Deleted team: " << deletedName << endl << RESET;
    // Report success to the caller.
    return true;
}

// Sort the teams alphabetically.
bool sortTeamsFromMenu(std::vector<Team>& teams) {
    // Reject the request when there are no teams to sort.
    if (teams.empty()) {
        cout << RED << "No teams available." << endl << RESET;
        return false;
    }

    // Sort the vector using Team::operator<.
    std::sort(teams.begin(), teams.end());
    // Report success to the user.
    cout << GREEN << "Teams sorted alphabetically." << endl << RESET;
    // Report success to the caller.
    return true;
}

// Delete a hero from a selected team by name.
bool deleteHeroFromTeamFromMenu(std::vector<Team>& teams) {
    // Store the selected team index.
    std::size_t teamIndex = 0;

    // Stop if the user does not select a valid team.
    if (!selectTeamIndex(teams, teamIndex, "Enter team number: ")) {
        return false;
    }

    // Bind a mutable reference to the selected team.
    Team &selectedTeam = teams[teamIndex];

    // Reject the request when the team has no heroes.
    if (selectedTeam.getHeroCount() == 0) {
        cout << RED << "That team has no heroes to delete." << endl << RESET;
        return false;
    }

    // Print a heading for the hero list.
    cout << "Heroes in " << selectedTeam.getTeamName() << ":" << endl;
    // Get a pointer to the team's hero storage.
    const Hero* heroes = selectedTeam.getHeroes();

    // Print each hero name currently in the team.
    for (int i = 0; i < selectedTeam.getHeroCount(); ++i) {
        cout << " - " << heroes[i].getHeroName() << endl;
    }

    // Store the hero name entered by the user.
    std::string heroName;
    // Prompt for the hero name.
    cout << "Enter hero name to delete: ";
    // Read the hero name.
    getline(cin, heroName);

    // Reject empty hero names.
    if (heroName.empty()) {
        cout << RED << "Hero name cannot be empty." << endl << RESET;
        return false;
    }

    // Attempt to remove the hero and reject missing names.
    if (!selectedTeam.removeHeroByName(heroName)) {
        cout << RED << "Hero not found in that team." << endl << RESET;
        return false;
    }

    // Report success to the user.
    cout << GREEN << "Hero deleted from team." << endl << RESET;
    // Report success to the caller.
    return true;
}

// Remove captain status from a selected hero.
bool removeCaptainFromHeroFromMenu(std::vector<Team>& teams) {
    // Store the selected team index.
    std::size_t teamIndex = 0;

    // Stop if the user does not select a valid team.
    if (!selectTeamIndex(teams, teamIndex, "Enter team number: ")) {
        return false;
    }

    // Bind a mutable reference to the selected team.
    Team &selectedTeam = teams[teamIndex];

    // Reject the request when the team has no heroes.
    if (selectedTeam.getHeroCount() == 0) {
        cout << RED << "That team has no heroes." << endl << RESET;
        return false;
    }

    // Print a heading for the hero list.
    cout << "Heroes in " << selectedTeam.getTeamName() << ":" << endl;
    // Get a pointer to the team's hero storage.
    const Hero* heroes = selectedTeam.getHeroes();

    // Print every hero and mark the current captain.
    for (int i = 0; i < selectedTeam.getHeroCount(); ++i) {
        cout << " - " << heroes[i].getHeroName();
        if (heroes[i].getCaptainStatus()) {
            cout << " (Captain)";
        }
        cout << endl;
    }

    // Store the hero name entered by the user.
    std::string heroName;
    // Prompt for the hero name.
    cout << "Enter hero name to remove captain status from: ";
    // Read the hero name.
    getline(cin, heroName);

    // Reject empty hero names.
    if (heroName.empty()) {
        cout << RED << "Hero name cannot be empty." << endl << RESET;
        return false;
    }

    // Find the requested hero in the selected team.
    Hero* hero = selectedTeam.findHero(heroName);
    // Reject names that do not exist in the selected team.
    if (hero == nullptr) {
        cout << RED << "Hero not found in that team." << endl << RESET;
        return false;
    }

    // Reject heroes that are not currently captains.
    if (!hero->getCaptainStatus()) {
        cout << RED << "That hero is not currently a captain." << endl << RESET;
        return false;
    }

    // Remove the captain flag from the named hero.
    selectedTeam.removeCaptainStatusFromHero(heroName);
    // Report success to the user.
    cout << GREEN << "Captain status removed." << endl << RESET;
    // Report success to the caller.
    return true;
}

// Sort the heroes in one selected team alphabetically.
bool sortHeroesInTeamFromMenu(std::vector<Team>& teams) {
    // Store the selected team index.
    std::size_t teamIndex = 0;

    // Stop if the user does not select a valid team.
    if (!selectTeamIndex(teams, teamIndex, "Enter team number: ")) {
        return false;
    }

    // Reject the request when the selected team has no heroes.
    if (teams[teamIndex].getHeroCount() == 0) {
        cout << RED << "That team has no heroes to sort." << endl << RESET;
        return false;
    }

    // Sort the selected team's heroes alphabetically.
    teams[teamIndex].sortHeroesAlphabetically();
    // Report success to the user.
    cout << GREEN << "Heroes sorted alphabetically." << endl << RESET;
    // Report success to the caller.
    return true;
}

// Display the full details for one selected team.
void viewFullTeamInfoFromMenu(const std::vector<Team>& teams) {
    // Store the selected team index.
    std::size_t teamIndex = 0;

    // Stop if the user does not select a valid team.
    if (!selectTeamIndex(teams, teamIndex, "Enter team number to view: ")) {
        return;
    }

    // Print a heading for the full team detail section.
    cout << "\n==============================" << endl;
    // Print the title line.
    cout << "       FULL TEAM DETAILS      " << endl;
    // Print a closing heading line.
    cout << "==============================" << endl;
    // Print the selected team's full detail view.
    teams[teamIndex].displayFullTeamInfo();
    // Print a footer line.
    cout << "==============================" << endl;
}

// Open the project README from the menu system.
void openReadMeFromMenu() {
#ifdef _WIN32
    // Ask Windows to open the README in Notepad.
    HINSTANCE result = ShellExecuteA(
        NULL,
        "open",
        "notepad.exe",
        "..\\README.md",
        NULL,
        SW_SHOWNORMAL
    );

    // Report success when ShellExecute returns a value greater than 32.
    if ((INT_PTR)result > 32) {
        cout << GREEN << "Success: README opened." << RESET << endl;
    }
    else {
        // Report failure when ShellExecute returns an error code.
        cout << RED << "Error: README could not be opened." << RESET << endl;
    }
#elif __APPLE__
    // Ask macOS to open the README with the default application.
    const int result = std::system("open ../README.md");

    // Report success when the command returns zero.
    if (result == 0) {
        cout << GREEN << "Success: README opened." << RESET << endl;
    }
    else {
        // Report failure when the command returns a nonzero status.
        cout << RED << "Error: README could not be opened." << RESET << endl;
    }
#else
    // Ask Linux to open the README with the default application.
    const int result = std::system("xdg-open ../README.md >/dev/null 2>&1");

    // Report success when the command returns zero.
    if (result == 0) {
        cout << GREEN << "Success: README opened." << RESET << endl;
    }
    else {
        // Report failure when the command returns a nonzero status.
        cout << RED << "Error: README could not be opened." << RESET << endl;
    }
#endif
}

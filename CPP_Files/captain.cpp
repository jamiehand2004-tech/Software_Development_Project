// Include the Captain declarations being implemented here.
#include "../Header_Files/captain.h"
// Include iostream for console output used by the methods below.
#include <iostream>
// Include Team so captain methods can read team state safely.
#include "../Header_Files/team.h"

// ANSI escape sequence used for red warning and error output.
const string RED = "\033[31m";
// ANSI escape sequence used for green success output.
const string GREEN = "\033[32m";
// ANSI escape sequence used to restore the console colour.
const string RESET = "\033[0m";

// Build a captain object with placeholder defaults.
Captain::Captain() {
    // Use a fallback name until a real captain is assigned.
    captainName = "Unknown";
    // Start with no associated team.
    team = nullptr;
    // Start the captain count at zero for the default object.
    captainCount = 0;
}

// Build a captain object from supplied values.
Captain::Captain(const std::string &name, Team* t, int count) {
    // Copy the provided captain name into the object.
    captainName = name;
    // Store the provided team pointer.
    team = t;
    // Store the provided count value.
    captainCount = count;
}

// Check whether the stored count suggests multiple captains exist.
bool Captain::isMultipleCaptains() {
    // If more than one captain is recorded, warn the user.
    if (captainCount > 1) {
        // Print a red warning with the recorded count value.
        std::cout << RED << "Warning: More than one captain created. Captain count: " << captainCount << std::endl << RESET;
        // Report that the condition was detected.
        return true;
    }
    // Otherwise report that the count is acceptable.
    return false;
}

// Print a summary of the captain and its associated team.
void Captain::displayCaptainInfo() {
    // If no team is attached, print an error and stop immediately.
    if (!team) {
        std::cout << RED << "No team assigned to this captain." << std::endl << RESET;
        return;
    }
    // Print the stored captain name.
    std::cout << "Captain Name: " << captainName << std::endl;
    // Print the associated team name.
    std::cout << "Team Name: " << team->getTeamName() << std::endl;
    // Print how many heroes belong to the associated team.
    std::cout << "Heroes in the Team: " << team->getHeroCount() << std::endl;
    // The team's own display function identifies the actual captain hero.
    // Avoid calling getHeroes() directly here because the team may not expose
    // a stable backing array in every implementation.
}

// Placeholder function for future captain-assignment logic.
void Captain::assignCaptain(Hero hero, Team *team)
{
    // The parameters are intentionally unused until assignment logic is added.
    (void)hero;
    (void)team;
}

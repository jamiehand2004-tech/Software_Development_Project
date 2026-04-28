// Include the Team declarations being implemented here.
#include "../Header_Files/team.h"
// Include Hero because the implementation reads hero properties directly.
#include "../Header_Files/hero.h"
// Include Captain for compatibility with the existing dependency graph.
#include "../Header_Files/captain.h"

// Include STL algorithms for sorting and searching operations.
#include <algorithm>

// Bring commonly used standard-library names into local scope.
using std::string;
using std::cout;
using std::endl;

// ANSI escape sequence used for red error text.
const string RED = "\033[31m";
// ANSI escape sequence used for green success text.
const string GREEN = "\033[32m";
// ANSI escape sequence used to restore the console colour.
const string RESET = "\033[0m";

// Construct a team with a supplied name.
Team::Team(string tn)
{
    // Copy the supplied team name.
    teamName = tn;
    // Start with zero heroes recorded.
    heroCount = 0;
}

// Construct an empty team.
Team::Team()
{
    // Start with an empty team name.
    teamName = "";
    // Start with zero heroes recorded.
    heroCount = 0;
}

// Construct a team from a name, hero array, and count.
Team::Team(string tn, Hero *h, int cnt)
{
    // Copy the supplied team name.
    teamName = tn;
    // Store the supplied hero count.
    heroCount = cnt;
    // Copy the supplied heroes into the vector.
    setHeroes(h);
}

// Replace the internal hero vector from a raw hero array.
void Team::setHeroes(Hero *h) {
    // Clear any heroes already stored in the team.
    teamHeroes.clear();

    // Reject null pointers and non-positive counts.
    if (h == nullptr || heroCount <= 0) {
        // Normalize the stored count back to zero.
        heroCount = 0;
        // Stop because there is nothing valid to copy.
        return;
    }

    // Clamp the copy count so it never exceeds the maximum allowed size.
    const int copyCount = heroCount > MAX_HEROES ? MAX_HEROES : heroCount;
    // Copy the raw hero array into the vector.
    teamHeroes.assign(h, h + copyCount);
    // Synchronize heroCount with the resulting vector size.
    syncHeroCount();
}

// Add one hero to the team when there is space available.
void Team::addHero(Hero h) {
    // Only append the hero if the maximum size has not been reached.
    if (heroCount < MAX_HEROES) {
        // Store the hero in the vector.
        teamHeroes.push_back(h);
        // Synchronize heroCount with the updated vector size.
        syncHeroCount();
    } else {
        // Otherwise print a warning that the team is already full.
        cout << RED << "Cannot add more heroes to the team. Maximum limit reached." << endl << RESET;
    }
}

// Print a short summary of the team.
void Team::displayTeamInfo() const {
    // Print the team name.
    cout << "Team Name: " << teamName << endl;
    // Print the current number of heroes.
    cout << "Number of Heroes: " << heroCount << endl;
    // Print a separator line.
    cout << "------------------------------" << endl;
    // Print a heading for the hero list.
    cout << "Heroes in the Team:" << endl;
    // Print each stored hero name.
    for (const Hero &hero : teamHeroes) {
        cout << "- " << hero.getHeroName() << endl;
    }
}

// Print the captain information for the team.
void Team::displayCaptainInfo() const {
    // Print a heading for the captain section.
    cout << "Captain of the Team: " << endl;
    // Search for the hero currently marked as captain.
    const Hero *captain = findCaptain();
    // If a captain exists, print the captain's name and stop.
    if (captain != nullptr) {
        cout << "- " << captain->getHeroName() << endl;
        return;
    }
    // Otherwise report that no captain is assigned.
    cout << RED << "No captain assigned to this team." << endl << RESET;
}

// Print a full detailed summary of the team.
void Team::displayFullTeamInfo() const {
    // Print the team name.
    cout << "Team Name: " << teamName << endl;
    // Print the current number of heroes.
    cout << "Number of Heroes: " << heroCount << endl;
    // Print a separator line.
    cout << "------------------------------" << endl;
    // Print a heading for the detail section.
    cout << "Heroes in the Team:" << endl;
    // Print the table header line.
    cout << "Hero Name | Health | Attack | Weakness | Captain Status |" << endl;
    // Print one detail line for every stored hero.
    for (const Hero &hero : teamHeroes) {
        cout << "- " << hero.getHeroName() << "|"
             << hero.getHealth() << "|"
             << hero.getAttack() << "|"
             << hero.getWeakness() << "|"
             << (hero.getCaptainStatus() ? "1" : "0") << "|"
             << endl;
    }
}

// Find a mutable hero in the team by name.
Hero* Team::findHero(const string &heroName) {
    // Search for the first hero whose name matches the requested name.
    auto it = std::find_if(teamHeroes.begin(), teamHeroes.end(),
        [&heroName](const Hero &hero) {
            return hero.getHeroName() == heroName;
        });

    // Return nullptr when no matching hero exists.
    if (it == teamHeroes.end()) {
        return nullptr;
    }

    // Return a pointer to the matching hero.
    return &(*it);
}

// Find a const hero in the team by name.
const Hero* Team::findHero(const string &heroName) const {
    // Search for the first hero whose name matches the requested name.
    auto it = std::find_if(teamHeroes.begin(), teamHeroes.end(),
        [&heroName](const Hero &hero) {
            return hero.getHeroName() == heroName;
        });

    // Return nullptr when no matching hero exists.
    if (it == teamHeroes.end()) {
        return nullptr;
    }

    // Return a pointer to the matching hero.
    return &(*it);
}

// Find the mutable hero currently marked as captain.
Hero* Team::findCaptain() {
    // Search for the first hero whose captain flag is true.
    auto it = std::find_if(teamHeroes.begin(), teamHeroes.end(),
        [](const Hero &hero) {
            return hero.getCaptainStatus();
        });

    // Return nullptr when no captain exists.
    if (it == teamHeroes.end()) {
        return nullptr;
    }

    // Return a pointer to the captain hero.
    return &(*it);
}

// Find the const hero currently marked as captain.
const Hero* Team::findCaptain() const {
    // Search for the first hero whose captain flag is true.
    auto it = std::find_if(teamHeroes.begin(), teamHeroes.end(),
        [](const Hero &hero) {
            return hero.getCaptainStatus();
        });

    // Return nullptr when no captain exists.
    if (it == teamHeroes.end()) {
        return nullptr;
    }

    // Return a pointer to the captain hero.
    return &(*it);
}

// Remove a hero from the team by matching the hero name.
bool Team::removeHeroByName(const string &heroName) {
    // Search for the first hero whose name matches the requested name.
    auto it = std::find_if(teamHeroes.begin(), teamHeroes.end(),
        [&heroName](const Hero &hero) {
            return hero.getHeroName() == heroName;
        });

    // Report failure when the hero is not present.
    if (it == teamHeroes.end()) {
        return false;
    }

    // Erase the matching hero from the vector.
    teamHeroes.erase(it);
    // Synchronize heroCount with the updated vector size.
    syncHeroCount();
    // Report success to the caller.
    return true;
}

// Remove captain status from a named hero when possible.
bool Team::removeCaptainStatusFromHero(const string &heroName) {
    // Find the named hero first.
    Hero* hero = findHero(heroName);

    // Report failure if the named hero does not exist.
    if (hero == nullptr) {
        return false;
    }

    // Report failure if the hero is not currently a captain.
    if (!hero->getCaptainStatus()) {
        return false;
    }

    // Clear the hero's captain flag.
    hero->setCaptainStatus(false);
    // Report success to the caller.
    return true;
}

// Sort the heroes alphabetically by name.
void Team::sortHeroesAlphabetically() {
    // Use Hero::operator< to sort the vector.
    std::sort(teamHeroes.begin(), teamHeroes.end());
}

// Save the team to an output stream.
void Team::save(std::ostream &os) const {
    // Write the team name on the first line.
    os << teamName << std::endl;
    // Write the number of stored heroes on the second line.
    os << teamHeroes.size() << std::endl;
    // Write each hero in a pipe-delimited record format.
    for (const Hero &h : teamHeroes) {
        os << h.getHeroName() << "|"
           << h.getHealth() << "|"
           << h.getAttack() << "|"
           << h.getWeakness() << "|"
           << (h.getCaptainStatus() ? 1 : 0) << "|"
           << (h.getAlive() ? 1 : 0) << std::endl;
    }
    // Write the separator line that ends the record.
    os << "----" << std::endl;
}

// Load a team from an input stream.
bool Team::load(std::istream &is) {
    // Clear any heroes already stored in the team.
    teamHeroes.clear();
    // Reset the hero count before parsing fresh data.
    heroCount = 0;

    // Read the team name; fail if the line is missing.
    if (!std::getline(is, teamName)) return false;
    // Store the next line, which should contain the hero count.
    std::string line;
    // Read the hero-count line; fail if it is missing.
    if (!std::getline(is, line)) return false;
    // Store the declared number of heroes from the file.
    int declaredHeroCount = 0;
    // Convert the hero-count text to an integer.
    try {
        declaredHeroCount = std::stoi(line);
    } catch (...) {
        // Reset the hero count on parse failure.
        heroCount = 0;
        // Report that the load operation failed.
        return false;
    }

    // Read each serialized hero record.
    for (int i = 0; i < declaredHeroCount; ++i) {
        // Read the next hero line; fail if it is missing.
        if (!std::getline(is, line)) return false;
        // Prepare position markers used while splitting the line.
        size_t p = 0, q;
        // Read the hero name field.
        q = line.find('|', p); if (q == std::string::npos) return false; std::string name = line.substr(p, q - p); p = q + 1;
        // Read the health field.
        q = line.find('|', p); if (q == std::string::npos) return false; int health = std::stoi(line.substr(p, q - p)); p = q + 1;
        // Read the attack field.
        q = line.find('|', p); if (q == std::string::npos) return false; int attack = std::stoi(line.substr(p, q - p)); p = q + 1;
        // Read the weakness field.
        q = line.find('|', p); if (q == std::string::npos) return false; std::string weakness = line.substr(p, q - p); p = q + 1;
        // Read the captain-status field.
        q = line.find('|', p); if (q == std::string::npos) return false; bool cap = (line.substr(p, q - p) != "0"); p = q + 1;
        // Read the alive-status field from the remainder of the line.
        bool alive = (line.substr(p) != "0");
        // Reconstruct the hero object from the parsed fields.
        Hero h(name, health, attack, weakness, cap, alive);
        // Only store the hero if the team has not exceeded the maximum size.
        if (static_cast<int>(teamHeroes.size()) < MAX_HEROES) {
            teamHeroes.push_back(h);
        }
    }
    // Synchronize heroCount with the loaded vector size.
    syncHeroCount();

    // Read the separator line that should follow the hero records.
    std::string sep;
    // Fail if the separator line is missing.
    if (!std::getline(is, sep)) return false;
    // Succeed only when the separator line matches the expected format.
    return sep == "----";
}


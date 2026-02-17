#include "captain.h"
#include "team.h"
using namespace std;

Captain::Captain() {
    captainName = "Unknown Captain";
    team = nullptr;
    captainCount++;
};
bool Captain::isMultipleCaptains() {
    if (captainCount > 1) {
        cout << "Warning: More than one captain created. Captain count: " << captainCount << endl;
        return true;
    }
    return false;
}

Captain::Captain(string name, Team* t) {
    captainName = name;
    team = t;
    captainCount++;
};

void Captain::displayCaptainInfo() {
    cout << "Captain Name: " << captainName << endl;
    cout << "Team Name: " << team->getTeamName() << endl;
    cout << "Heroes in the Team: " << team->getHeroCount() << endl;
    cout << "Captain's Hero Status: " << (team->getHeroes()[0].getCaptainStatus() ? "Yes" : "No") << endl; // Assuming the captain is the first hero in the team array
};


#include "captain.h"
#include "team.h"


Captain::Captain(string name, Team* t) {
    captainName = name;
    team = t;
    captainCount++;
};

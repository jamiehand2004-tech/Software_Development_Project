#include "hero.h"
#include "captain.h"
#include "team.h"

Hero::Hero(string n) {
    heroName = n;
    health = 100.0;
    attack = 10;
    weakness = "None";
    captainStatus = false;
    isAlive = true;
    heroCount++;
};

Hero::Hero(string n, float h) {
    heroName = n;
    health = h;
    attack = 10;
    weakness = "None";
    captainStatus = false;
    isAlive = true;
    heroCount++;
};

Hero::Hero(string n, float h, int a) {
    heroName = n;
    health = h;
    attack = a;
    weakness = "None";
    captainStatus = false;
    isAlive = true;
    heroCount++;
};

Hero::Hero(string n, float h, int a, string w) {
    heroName = n;
    health = h;
    attack = a;
    weakness = w;
    captainStatus = false;
    isAlive = true;
    heroCount++;
};

Hero::Hero(string n, float h, int a, string w, bool s) {
    heroName = n;
    health = h;
    attack = a;
    weakness = w;
    captainStatus = s;
    isAlive = true;
    heroCount++;
};

Hero::Hero(string n, float h, int a, string w, bool s, bool stat) {
    heroName = n;
    health = h;
    attack = a;
    weakness = w;
    captainStatus = s;
    isAlive = stat;
    heroCount++;
};
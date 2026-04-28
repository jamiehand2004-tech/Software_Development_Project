// Describe the Hero type, which represents an individual character in the game.

// Prevent this header from being included more than once in the same translation unit.
#ifndef HERO_H
#define HERO_H

// Provide std::vector if collections of heroes are needed by other code.
#include <vector>
// Provide standard stream declarations used throughout the project.
#include <iostream>
// Provide std::string for hero names and weaknesses.
#include <string>

// Bring std::string into the local header scope for shorter declarations.
using std::string;
// Bring std::vector into the local header scope for consistency with the project style.
using std::vector;

// Define the Hero class used by teams and menu operations.
class Hero {

private:

    // Store the hero's display name.
    string heroName;
    // Store the hero's health value.
    int health;
    // Store the hero's attack value.
    int attack;
    // Store the hero's weakness text.
    string weakness;
    // Store a count value used by the existing constructors.
    int heroCount;
    // Record whether this hero is currently marked as a captain.
    bool captainStatus;
    // Record whether this hero is alive.
    bool isAlive;

public:

    // Return the stored hero name.
    string getHeroName() const { return heroName; }
    // Return the stored health value.
    int getHealth() const { return health; }
    // Return the stored attack value.
    int getAttack() const { return attack; }
    // Return the stored weakness text.
    string getWeakness() const { return weakness; }
    // Return the current captain flag.
    bool getCaptainStatus() const { return captainStatus; }
    // Return the alive/dead flag.
    bool getAlive() const { return isAlive; }

    // Replace the stored hero name.
    void setHeroName(string n) { heroName = n; }
    // Replace the stored health value.
    void setHealth(int h) { health = h; }
    // Replace the stored attack value.
    void setAttack(int a) { attack = a; }
    // Replace the stored weakness text.
    void setWeakness(string w) { weakness = w; }
    // Replace the current captain flag.
    void setCaptainStatus(bool s) { captainStatus = s; }
    // Replace the alive/dead flag.
    void setAlive(bool alive) { isAlive = alive; }

    // Allow heroes to be sorted alphabetically by name with STL algorithms.
    bool operator<(const Hero& other) const { return heroName < other.heroName; }

    // Construct a hero with default values.
    Hero();
    // Construct a hero with only a name.
    Hero(string n);
    // Construct a hero with a name and health value.
    Hero(string n, int h);
    // Construct a hero with a name, health, and attack value.
    Hero(string n, int h, int a);
    // Construct a hero with a name, health, attack, and weakness.
    Hero(string n, int h, int a, string w);
    // Construct a hero and explicitly set the captain flag.
    Hero(string n, int h, int a, string w, bool s);
    // Construct a hero and explicitly set both captain and alive flags.
    Hero(string n, int h, int a, string w, bool s, bool stat);
};

// End the include guard started at the top of the file.
#endif
// Include the Hero declarations that these constructors implement.
#include "../Header_Files/hero.h"
// Include Captain for compatibility with the existing project dependency graph.
#include "../Header_Files/captain.h"
// Include Team for compatibility with the existing project dependency graph.
#include "../Header_Files/team.h"

// Construct a hero with safe default values.
Hero::Hero()
{
    // Start with no name assigned.
    heroName = "";
    // Start with zero health.
    health = 0;
    // Start with zero attack.
    attack = 0;
    // Start with no weakness text.
    weakness = "";
    // Start with captain status disabled.
    captainStatus = false;
    // Start with the hero marked alive.
    isAlive = true;
}

// Construct a hero when only the name is known.
Hero::Hero(string n)
{
    // Copy the supplied name.
    heroName = n;
    // Default health to zero.
    health = 0;
    // Default attack to zero.
    attack = 0;
    // Default weakness to an empty string.
    weakness = "";
    // Default captain status to false.
    captainStatus = false;
    // Default alive status to true.
    isAlive = true;
}

// Construct a hero when the name and health are known.
Hero::Hero(string n, int h)
{
    // Copy the supplied name.
    heroName = n;
    // Copy the supplied health value.
    health = h;
    // Default attack to zero.
    attack = 0;
    // Default weakness to an empty string.
    weakness = "";
    // Default captain status to false.
    captainStatus = false;
    // Default alive status to true.
    isAlive = true;
}

// Construct a hero when the name, health, and attack are known.
Hero::Hero(string n, int h, int a)
{
    // Copy the supplied name.
    heroName = n;
    // Copy the supplied health value.
    health = h;
    // Copy the supplied attack value.
    attack = a;
    // Default weakness to an empty string.
    weakness = "";
    // Default captain status to false.
    captainStatus = false;
    // Default alive status to true.
    isAlive = true;
}

// Construct a hero when the name, health, attack, and weakness are known.
Hero::Hero(string n, int h, int a, string w)
{
    // Copy the supplied name.
    heroName = n;
    // Copy the supplied health value.
    health = h;
    // Copy the supplied attack value.
    attack = a;
    // Copy the supplied weakness text.
    weakness = w;
    // Default captain status to false.
    captainStatus = false;
    // Default alive status to true.
    isAlive = true;
    // Increment the stored count value used by the current design.
    heroCount++;
}

// Construct a hero and explicitly set the captain flag.
Hero::Hero(string n, int h, int a, string w, bool s)
{
    // Copy the supplied name.
    heroName = n;
    // Copy the supplied health value.
    health = h;
    // Copy the supplied attack value.
    attack = a;
    // Copy the supplied weakness text.
    weakness = w;
    // Copy the supplied captain flag.
    captainStatus = s;
    // Default alive status to true.
    isAlive = true;
    // Increment the stored count value used by the current design.
    heroCount++;
}

// Construct a hero and explicitly set both the captain and alive flags.
Hero::Hero(string n, int h, int a, string w, bool s, bool stat)
{
    // Copy the supplied name.
    heroName = n;
    // Copy the supplied health value.
    health = h;
    // Copy the supplied attack value.
    attack = a;
    // Copy the supplied weakness text.
    weakness = w;
    // Copy the supplied captain flag.
    captainStatus = s;
    // Copy the supplied alive flag.
    isAlive = stat;
    // Increment the stored count value used by the current design.
    heroCount++;
}

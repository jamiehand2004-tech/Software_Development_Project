/*  
    Main file for the Hero-Agency-Management project,
    which demonstrates the creation and management of heroes, teams, and captains.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../Header_Files/hero.h"
#include "../Header_Files/team.h"
#include "../Header_Files/captain.h"
#include "../Header_Files/user_system.h"
#include "../Header_Files/menu.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::cin;
using std::getline;
using std::ofstream;
using std::ifstream;
using std::ios;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string RESET = "\033[0m";
const string CYAN = "\033[36m";

// Main function to demonstrate the functionality of the Hero-Agency-Management system
int main() {
    cout << GREEN << "PROGRAM START" << endl << RESET;

    // Create heroes
    Hero hero1("Superman", 100, 50, "Kryptonite");
    Hero hero2("Batman", 80, 30, "Himself");
    Hero hero3("Wonder Woman ", 90, 40, "Ropes");
    Hero hero4("Flash", 70, 35, "Cold");
    Hero hero5("Green Lantern", 85, 45, "Yellow");
    Hero hero6("Aquaman", 75, 25, "Dehydration");
    Hero hero7("Ichigo" , 95, 55, "Plot");
    Hero hero8("Goku", 120, 60, "Powerscalers");
    Hero hero9("Naruto", 85, 40, "Sasuke");
    Hero hero10("Luffy", 80, 45, "The Sea");
    Hero hero11("Frieren", 90.0, 50, "Wakey Wakey");
    Hero hero12("Kiora", 85, 40, "The Heart");
    Hero hero13("Saitama", 100, 100, "Boredom");
    Hero hero14("Captain Underpants", 80, 40, "Snapping fingers");
    Hero hero15("Invincible", 90, 50, "Trains");
    Hero hero16("Joker", 70, 30, "The IRS");
    Hero hero17("Spider-man", 75, 40, "The Writer");
    Hero hero18("Uriel", 100, 100, "None");
    Hero hero19("Kratos", 150, 150, "Rage");
    Hero hero20("Icarus", 60, 40, "The Sun");
    
    // Create a team and add heroes to it
    Team justiceLeague("Justice League");
    hero1.setCaptainStatus(true);
    justiceLeague.addHero(hero1);
    justiceLeague.addHero(hero2);
    justiceLeague.addHero(hero3);
    justiceLeague.addHero(hero4);
    justiceLeague.addHero(hero5);
    justiceLeague.addHero(hero6);

    // Create another team and add heroes to it
    Team animeHeroes("Anime Heroes");
    hero10.setCaptainStatus(true);
    animeHeroes.addHero(hero7);     
    animeHeroes.addHero(hero8);
    animeHeroes.addHero(hero9);
    animeHeroes.addHero(hero10);
    animeHeroes.addHero(hero11);
    animeHeroes.addHero(hero12);
    animeHeroes.addHero(hero13);

    // Create captains (store name and team pointer)
    Captain JLcaptain("Superman", &justiceLeague);
    Captain animeCaptain("Luffy", &animeHeroes);

    // put teams in a container for save/load and interactive modification
    vector<Team> teams;
    teams.push_back(justiceLeague);
    teams.push_back(animeHeroes);

    UserSystem userSys;

    // NEW CODE: require login or registration before the main menu opens.
    bool loggedIn = false;
    while (!loggedIn) {
        int startChoice = 0;

        cout << "\nLogin Menu:\n (1) Login\n (2) Register\n (3) Exit\n-> ";

        if (!(cin >> startChoice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');

        if (startChoice == 1) {
            string username;
            string password;

            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);

            if (userSys.loginUser(username, password)) {
                cout << CYAN << "Logged in as user: " << userSys.getCurrentUser() << endl << RESET;
                loggedIn = true;
            }
            else {
                cout << RED << "Login failed. Try again." << endl << RESET;
            }
        }

        else if (startChoice == 2) {
            string username;
            string password;

            cout << "Choose username: ";
            getline(cin, username);
            cout << "Choose password: ";
            getline(cin, password);

            if (username.empty() || password.empty()) {
                cout << RED << "Username and password cannot be empty." << endl << RESET;
            }
            else if (userSys.registerUser(username, password, "user")) {
                cout << GREEN << "User registered successfully. You can now log in." << endl << RESET;
            }
            else {
                cout << RED << "That username already exists." << endl << RESET;
            }
        }

        else if (startChoice == 3) {
            return 0;
        }
    }

    // Simple CLI loop
    bool running = true;

    while (running) {

        // NEW CODE: show the currently logged-in user.
        cout <<CYAN<< "\nCurrent User: " << userSys.getCurrentUser()<< RESET;

        showMainMenu();

        int choice = 0;
        if (!(cin >> choice)) 
        { 
            cin.clear();
            cin.ignore(10000, '\n');
            continue; 
        }

        cin.ignore(10000, '\n');

        if (choice == 1) {
            listTeamsFromMenu(teams);
        } 

        else if (choice == 2) 
        {
            addHeroToTeamFromMenu(teams);
        } 

        else if (choice == 3) 
        {
            string fname;
            cout << "Save filename: ";
            getline(cin, fname);

            if (fname.empty()) fname = "teams_state.txt";

            ofstream ofs(fname);
            for (const auto &t : teams) {
                t.save(ofs);
            }
            ofs.close();
            cout << "Saved to " << fname << endl;
        } 

        else if (choice == 4) 
        {
            string fname;
            cout << "Load filename: ";
            getline(cin, fname);

            if (fname.empty()) fname = "teams_state.txt";

            ifstream ifs(fname);
            if (!ifs.is_open()) {
                cout << "Cannot open file\n";
                continue;
            }

            teams.clear();
            while (ifs.peek() != EOF) {
                Team t;
                if (!t.load(ifs)) break;
                teams.push_back(t);
            }
            ifs.close();
            cout << "Loaded " << teams.size() << " teams from " << fname << endl;
        } 

        else if (choice == 5) 
        {
            userSys.logoutUser();
            running = false;
        }
        
        else if (choice == 6)
        {
            string teamName;
            bool duplicateTeam = false;

            cout << "Enter team name: ";
            getline(cin, teamName);

            if (teamName.empty()) {
                cout << "Team name cannot be empty." << endl;
                continue;
            }

            for (size_t i = 0; i < teams.size(); ++i) {
                if (teams[i].getTeamName() == teamName) {
                    duplicateTeam = true;
                    break;
                }
            }

            if (duplicateTeam) {
                cout << RED << "A team with that name already exists." << endl << RESET;
                continue;
            }

            Team newTeam(teamName);
            teams.push_back(newTeam);
            cout << GREEN << "Team created successfully." << endl << RESET;
        }

        else if (choice == 7)
        {
            deleteTeamFromMenu(teams);
        }

        else if (choice == 8)
        {
            deleteHeroFromTeamFromMenu(teams);
        }

        else if (choice == 9)
        {
            // NEW CODE: display all teams with the full attributes of each hero.
            if (teams.empty()) {
                cout << "No teams available.\n";
                continue;
            }

            for (size_t i = 0; i < teams.size(); ++i) {
                cout << "-- Team [" << (i + 1) << "] --" << endl;
                teams[i].displayFullTeamInfo();
                cout << "------------------------------" << endl;
            }
        }

    }
    return 0;
}
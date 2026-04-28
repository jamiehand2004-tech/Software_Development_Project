// Describe the application's top-level setup and menu loop implementation.

// Include iostream for console input and output.
#include <iostream>
// Include string for user input and filenames.
#include <string>
// Include vector for storing teams in memory.
#include <vector>
// Include fstream for saving and loading state files.
#include <fstream>

// Include Hero because the main function creates the predefined hero roster.
#include "../Header_Files/hero.h"
// Include Team because the main function creates and stores teams.
#include "../Header_Files/team.h"
// Include Captain because the main function creates captain wrapper objects.
#include "../Header_Files/captain.h"
// Include UserSystem because the main function manages login and registration.
#include "../Header_Files/user_system.h"
// Include the menu helpers used to display and route menu actions.
#include "../Header_Files/menu.h"

// Bring frequently used standard-library names into local scope.
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::cin;
using std::getline;
using std::ofstream;
using std::ifstream;
using std::ios;

// ANSI escape sequence used for red error text.
const string RED = "\033[31m";
// ANSI escape sequence used for green success text.
const string GREEN = "\033[32m";
// ANSI escape sequence used to restore the console colour.
const string RESET = "\033[0m";
// ANSI escape sequence used for cyan headings and status text.
const string CYAN = "\033[36m";

// Run the Hero Agency application.
int main() {
    // Print a visible marker that the program has started.
    cout << GREEN << "PROGRAM START" << endl << RESET;

    // Create the predefined hero roster used by the demo application.
    Hero hero1("Superman", 100, 50, "Kryptonite");
    Hero hero2("Batman", 80, 30, "Himself");
    Hero hero3("Wonder Woman ", 90, 40, "Ropes");
    Hero hero4("Flash", 70, 35, "Cold");
    Hero hero5("Green Lantern", 85, 45, "Yellow");
    Hero hero6("Aquaman", 75, 25, "Dehydration");
    Hero hero7("Ichigo", 95, 55, "Plot");
    Hero hero8("Goku", 120, 60, "Powerscalers");
    Hero hero9("Naruto", 85, 40, "Sasuke");
    Hero hero10("Luffy", 80, 45, "The Sea");
    Hero hero11("Frieren", 90, 50, "Wakey Wakey");
    Hero hero12("Kiora", 85, 40, "The Heart");
    Hero hero13("Saitama", 100, 100, "Boredom");
    Hero hero14("Captain Underpants", 80, 40, "Snapping fingers");
    Hero hero15("Invincible", 90, 50, "Trains");
    Hero hero16("Joker", 70, 30, "The IRS");
    Hero hero17("Spider-man", 75, 40, "The Writer");
    Hero hero18("Uriel", 100, 100, "None");
    Hero hero19("Kratos", 150, 150, "Rage");
    Hero hero20("Icarus", 60, 40, "The Sun");

    // Create the first predefined team.
    Team justiceLeague("Justice League");

    // Mark Superman as the captain before copying him into the team.
    hero1.setCaptainStatus(true);
    // Add the predefined Justice League heroes.
    justiceLeague.addHero(hero1);
    justiceLeague.addHero(hero2);
    justiceLeague.addHero(hero3);
    justiceLeague.addHero(hero4);
    justiceLeague.addHero(hero5);
    justiceLeague.addHero(hero6);

    // Create the second predefined team.
    Team animeHeroes("Anime Heroes");

    // Mark Luffy as the captain before copying him into the team.
    hero10.setCaptainStatus(true);
    // Add the predefined Anime Heroes roster.
    animeHeroes.addHero(hero7);
    animeHeroes.addHero(hero8);
    animeHeroes.addHero(hero9);
    animeHeroes.addHero(hero10);
    animeHeroes.addHero(hero11);
    animeHeroes.addHero(hero12);
    animeHeroes.addHero(hero13);

    // Create captain wrapper objects linked to the two predefined teams.
    Captain JLcaptain("Superman", &justiceLeague);
    Captain animeCaptain("Luffy", &animeHeroes);

    // Suppress unused-variable warnings for the captain wrapper objects.
    (void)JLcaptain;
    (void)animeCaptain;

    // Store the predefined teams in a vector used by save/load and menus.
    vector<Team> teams;
    // Add the Justice League team to the vector.
    teams.push_back(justiceLeague);
    // Add the Anime Heroes team to the vector.
    teams.push_back(animeHeroes);

    // Create the user system used for registration, login, and logout.
    UserSystem userSys;

    // Track whether a user has completed login or registration flow successfully.
    bool loggedIn = false;
    // Keep showing the login menu until a user logs in or exits.
    while (!loggedIn) {
        // Store the user's login-menu choice.
        int startChoice = 0;

        // Print the login menu.
        cout << "\nLogin Menu:\n (1) Login\n (2) Register\n (3) Exit\n-> ";

        // Validate that the user entered an integer choice.
        if (!(cin >> startChoice)) {
            // Clear the stream error state.
            cin.clear();
            // Discard the invalid input line.
            cin.ignore(10000, '\n');
            // Restart the login loop.
            continue;
        }

        // Discard the newline after the numeric choice.
        cin.ignore(10000, '\n');

        // Handle the login option.
        if (startChoice == 1) {
            // Store the entered username.
            string username;
            // Store the entered password.
            string password;

            // Prompt for the username.
            cout << "Username: ";
            // Read the username.
            getline(cin, username);
            // Prompt for the password.
            cout << "Password: ";
            // Read the password.
            getline(cin, password);

            // Attempt to log the user in.
            if (userSys.loginUser(username, password)) {
                // Print the logged-in username.
                cout << CYAN << "Logged in as user: " << userSys.getCurrentUser() << endl << RESET;
                // Mark the user as logged in so the outer loop can end.
                loggedIn = true;
            }
            else {
                // Report that the login attempt failed.
                cout << RED << "Login failed. Try again." << endl << RESET;
            }
        }

        // Handle the registration option.
        else if (startChoice == 2) {
            // Store the username to register.
            string username;
            // Store the password to register.
            string password;

            // Prompt for a new username.
            cout << "Choose username: ";
            // Read the username.
            getline(cin, username);
            // Prompt for a new password.
            cout << "Choose password: ";
            // Read the password.
            getline(cin, password);

            // Reject blank usernames or passwords.
            if (username.empty() || password.empty()) {
                cout << RED << "Username and password cannot be empty." << endl << RESET;
            }
            // Attempt to register the user with the default role of user.
            else if (userSys.registerUser(username, password, "user")) {
                cout << GREEN << "User registered successfully. You can now log in." << endl << RESET;
            }
            else {
                // Report that the username already exists.
                cout << RED << "That username already exists." << endl << RESET;
            }
        }

        // Handle the immediate exit option.
        else if (startChoice == 3) {
            // Exit the whole program successfully.
            return 0;
        }
    }

    // Track whether the main application loop should continue running.
    bool running = true;

    // Keep showing the main menu until the user chooses to exit.
    while (running) {
        // Print the currently logged-in user.
        cout << CYAN << "\nCurrent User: " << userSys.getCurrentUser() << RESET << endl;
        // Print the main menu options.
        showMainMenu();

        // Store the user's top-level menu choice.
        int choice = 0;
        // Validate that the user entered an integer choice.
        if (!(cin >> choice)) {
            // Clear the stream error state.
            cin.clear();
            // Discard the invalid input line.
            cin.ignore(10000, '\n');
            // Restart the loop and show the menu again.
            continue;
        }

        // Discard the newline after the numeric choice.
        cin.ignore(10000, '\n');

        // Route choice 1 to the team-list view.
        if (choice == 1) {
            listTeamsFromMenu(teams);
        }

        // Route choice 2 to the team-management submenu.
        else if (choice == 2) {
            // Track whether the team submenu should keep running.
            bool teamMenuRunning = true;

            // Keep showing the team submenu until the user returns.
            while (teamMenuRunning) {
                // Print the team submenu options.
                showTeamManagementMenu();

                // Store the team submenu choice.
                int teamChoice = 0;
                // Validate that the user entered an integer choice.
                if (!(cin >> teamChoice)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }

                // Discard the newline after the numeric choice.
                cin.ignore(10000, '\n');

                // Create a new team.
                if (teamChoice == 1) {
                    createTeamFromMenu(teams);
                }
                // Rename an existing team.
                else if (teamChoice == 2) {
                    renameTeamFromMenu(teams);
                }
                // Delete an existing team.
                else if (teamChoice == 3) {
                    deleteTeamFromMenu(teams);
                }
                // Sort the teams alphabetically.
                else if (teamChoice == 4) {
                    sortTeamsFromMenu(teams);
                }
                // Return to the main menu.
                else if (teamChoice == 5) {
                    teamMenuRunning = false;
                }
            }
        }

        // Route choice 3 to the hero-management submenu.
        else if (choice == 3) {
            // Track whether the hero submenu should keep running.
            bool heroMenuRunning = true;

            // Keep showing the hero submenu until the user returns.
            while (heroMenuRunning) {
                // Print the hero submenu options.
                showHeroManagementMenu();

                // Store the hero submenu choice.
                int heroChoice = 0;
                // Validate that the user entered an integer choice.
                if (!(cin >> heroChoice)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }

                // Discard the newline after the numeric choice.
                cin.ignore(10000, '\n');

                // Add a hero to one team.
                if (heroChoice == 1) {
                    addHeroToTeamFromMenu(teams);
                }
                // Delete a hero from one team.
                else if (heroChoice == 2) {
                    deleteHeroFromTeamFromMenu(teams);
                }
                // Remove captain status from a hero.
                else if (heroChoice == 3) {
                    removeCaptainFromHeroFromMenu(teams);
                }
                // Sort heroes inside a selected team.
                else if (heroChoice == 4) {
                    sortHeroesInTeamFromMenu(teams);
                }
                // Show the full details of one selected team.
                else if (heroChoice == 5) {
                    viewFullTeamInfoFromMenu(teams);
                }
                // Return to the main menu.
                else if (heroChoice == 6) {
                    heroMenuRunning = false;
                }
            }
        }

        // Route choice 4 to the save-state operation.
        else if (choice == 4) {
            // Store the filename entered by the user.
            string fname;
            // Prompt for the save filename.
            cout << "Save filename: ";
            // Read the filename line.
            getline(cin, fname);

            // Use the default save filename when the input is blank.
            if (fname.empty()) fname = "teams_state.txt";

            // Open the destination file for output.
            ofstream ofs(fname);
            // Save each team to the chosen file.
            for (const auto &t : teams) {
                t.save(ofs);
            }
            // Close the output file explicitly.
            ofs.close();
            // Report that the save operation completed.
            cout << GREEN << "Saved to " << fname << endl << RESET;
        }

        // Route choice 5 to the load-state operation.
        else if (choice == 5) {
            // Store the filename entered by the user.
            string fname;
            // Prompt for the load filename.
            cout << "Load filename: ";
            // Read the filename line.
            getline(cin, fname);

            // Use the default load filename when the input is blank.
            if (fname.empty()) fname = "teams_state.txt";

            // Open the source file for input.
            ifstream ifs(fname);
            // If the file cannot be opened, report the error and continue.
            if (!ifs.is_open()) {
                cout << RED << "Cannot open file." << endl << RESET;
                continue;
            }

            // Remove any teams already stored in memory.
            teams.clear();
            // Keep loading teams until EOF or a parsing failure occurs.
            while (ifs.peek() != EOF) {
                // Prepare one temporary team object.
                Team t;
                // Stop if the next team cannot be loaded successfully.
                if (!t.load(ifs)) break;
                // Store the successfully loaded team in memory.
                teams.push_back(t);
            }
            // Close the input file explicitly.
            ifs.close();
            // Report how many teams were loaded.
            cout << GREEN << "Loaded " << teams.size() << " teams from " << fname << endl << RESET;
        }

        // Route choice 6 to the README/help action.
        else if (choice == 6) {
            openReadMeFromMenu();
        }

        // Route choice 7 to logout and application shutdown.
        else if (choice == 7) {
            // Clear the current login session.
            userSys.logoutUser();
            // End the main loop.
            running = false;
        }
    }

    // Return a success exit code to the operating system.
    return 0;
}

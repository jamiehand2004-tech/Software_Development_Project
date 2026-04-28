// Include the UserSystem declarations being implemented here.
#include "../Header_Files/user_system.h"
// Include Hero for compatibility with the existing dependency structure.
#include "../Header_Files/hero.h"
// Include Team for compatibility with the existing dependency structure.
#include "../Header_Files/team.h"
// Include Captain for compatibility with the existing dependency structure.
#include "../Header_Files/captain.h"

// Include iostream for console-related names used in project style.
#include <iostream>
// Include string for username, password, and role handling.
#include <string>
// Include vector for consistency with the project style.
#include <vector>
// Include fstream for reading and writing the user file.
#include <fstream>
// Include algorithm for consistency with the project style.
#include <algorithm>

// Bring commonly used standard-library names into local scope.
using std::count;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::vector;

// Construct the user system and immediately load saved users.
UserSystem::UserSystem() {
    // Populate the internal user map from disk.
    loadUsers();
}

// Load users from users.txt into the internal map.
void UserSystem::loadUsers() {

    // Open the user database file.
    ifstream file("users.txt");
    // If it does not exist yet, create an empty file and stop.
    if (!file.is_open()) {
        ofstream createFile("users.txt");
        createFile.close();
        return;
    }

    // Clear any users currently stored in memory.
    users.clear();
    // Read user records until extraction fails.
    while (file) {
        // Store one temporary user record from the file.
        User u;
        // Read username, password, and role from the file.
        if (!(file >> u.username >> u.password >> u.role)) break;
        // Ignore empty usernames and store valid records by username key.
        if (!u.username.empty())
            users[u.username] = u;
    }
    // Close the file explicitly.
    file.close();
}

// Save all users from the internal map back to users.txt.
void UserSystem::saveUsers() {
    // Open the user database file for writing.
    ofstream file("users.txt");
    // Write each stored user record on its own line.
    for (auto & pair : users) {
        file << pair.second.username << " "
             << pair.second.password << " "
             << pair.second.role << endl;
    }
    // Close the file explicitly.
    file.close();
}

// Register a new user if the username is available.
bool UserSystem::registerUser(const string & username, const string password, const string role) {
    // Reject duplicate usernames.
    if (users.count(username)) {
        return false;
    }
    // Store the new user record in the map.
    users[username] = {username, password, role, 0};
    // Persist the updated user database to disk.
    saveUsers();
    // Report success to the caller.
    return true;
}

// Attempt to log a user in with the supplied credentials.
bool UserSystem::loginUser(const string & username, const string & password) {
    // Verify that the user exists and the password matches.
    if (users.count(username) && users[username].password == password) {
        // Record the logged-in username.
        currentUser = username;
        // Report success to the caller.
        return true;
    }
    // Report failure to the caller.
    return false;
}

// Clear the current login state.
void UserSystem::logoutUser() {
    // Remove the current username from the session state.
    currentUser.clear();
}

// Check whether the current user has the admin role.
bool UserSystem::isAdmin() {
    // Inspect every stored user record.
    for (const auto& user : users) {
        // Return true when the logged-in user has the admin role.
        if (user.first == currentUser && user.second.role == "admin") {
            return true;
        }
    }
    // Return false when no matching admin record is found.
    return false;
}

// Return the role of the currently logged-in user.
string UserSystem::getCurrentUserRole() {
    // If no user is logged in, return an empty string.
    if (currentUser.empty()) return string();
    // If the user exists in the map, return the stored role.
    if (users.count(currentUser)) return users[currentUser].role;
    // Otherwise return an empty string.
    return string();
}
// Prevent duplicate inclusion of the user-system declarations.
#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

// Provide stream declarations used by the implementation.
#include <iostream>
// Provide std::string for usernames, passwords, and roles.
#include <string>
// Provide std::map for storing users by username.
#include <map>
// Provide std::vector for consistency with the project style.
#include <vector>

// Bring std::string into local scope for shorter declarations.
using std::string;
// Bring std::vector into local scope for shorter declarations.
using std::vector;
// Bring stream-related names into local scope for consistency with the project style.
using std::cout;
using std::endl;
using std::ofstream;
using std::ios;
using std::cerr;
using std::cin;
using std::pair;
using std::map;

// Represent one stored user record.
struct User {
    // Store the username used to log in.
    string username;
    // Store the password as plain text in the current implementation.
    string password;
    // Store the role, such as admin or user.
    string role;
    // Store a count value kept by the existing design.
    int userCount;
};

// Manage registration, login, logout, and role lookups.
class UserSystem {

private:

    // Map usernames to their corresponding stored user records.
    map<string, User> users;
    // Remember which user is currently logged in.
    string currentUser;

public:

    // Construct a user system and immediately load saved users.
    UserSystem();
    // Load user data from disk.
    void loadUsers();
    // Save user data back to disk.
    void saveUsers();

    // Register a new user account.
    bool registerUser(const string & username, const string password, const string role);
    // Attempt to log a user in.
    bool loginUser(const string & username, const string & password);
    // Log the current user out.
    void logoutUser();
    // Check whether the current user has the admin role.
    bool isAdmin();

    // Return the currently logged-in username.
    string getCurrentUser() { return currentUser; }
    // Return the role string for the current user.
    string getCurrentUserRole();
};

// End the include guard started at the top of the file.
#endif


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "account.h"


UserDatabase::UserDatabase() {
    loadUsersFromFile(); 
}

bool UserDatabase::registerUser(const string& username, const string& password) {
    if (users.find(username) == NULL) {
        users.insert(username, password);
        saveUsersToFile(); // Save user information after registration
        return true; // Registration successful
    }
    return false; // Username already exists
}

bool UserDatabase::loginUser(const string& username, const string& password) {
    string* storedPassword = users.find(username);
    if (storedPassword != NULL && *storedPassword == password) {
        cout << "Login successful. Welcome, " << username << "!" << endl;
        return true;
    }
    cout << "Invalid username or password." << endl;
    return false;
}

void UserDatabase::saveUsersToFile() {
    users.saveToFile(userFilename);
}

void UserDatabase::loadUsersFromFile() {
    users.loadFromFile(userFilename);
}



User::User() : username(""), password("") {} // Default constructor

User::User(const string& username, const string& password)
    : username(username), password(password) {}

const string& User::getUsername() const {
    return username;
}

bool User::validatePassword(const string& inputPassword) const {
    return password == inputPassword;
}

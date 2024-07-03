#include "database.h"
using namespace std;

class UserDatabase {
private:
    HashTable users;
    const string userFilename = "users.txt";

public:
    UserDatabase();

    bool registerUser(const string& username, const string& password);

    bool loginUser(const string& username, const string& password);

    void saveUsersToFile();

    void loadUsersFromFile();
};


class User {
private:
    string username;
    string password;

public:
    User();
    User(const string& username, const string& password);
    const string& getUsername() const;
    bool validatePassword(const string& inputPassword) const;
};

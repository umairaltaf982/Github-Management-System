#include <iostream>
#include <string>
#include "account.h"
#include "repository.h"
//#include "database.h"

#define MAXSIZE 100

using namespace std;

int main() {
    UserDatabase userDB;
    RepositoryManager repoManager;
    Graph socialGraph;
    User loggedInUsers[50];
    int loggedInUsersCount = 0;


    int choice;
    do {
        cout << "\n1. Register\n";
        cout << "2. Login\n";
        cout << "3. Create Repository\n";
        cout << "4. Display Repositories\n";
        cout << "5. Delete Repository\n";
        cout << "6. Fork Repository\n";
        cout << "7. Add Commit\n";
        cout << "8. View Repository Stats\n";
        cout << "9. Follow User\n";
        cout << "10. Unfollow User\n";
        cout << "11. Display Followed Users\n";
        cout << "12. Add File to Repository\n";
        cout << "13. Delete File from Repository\n";
        cout << "14. Add README to Repository\n";  // Option to add README
        cout << "15. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cin.ignore();
            cout << "Enter username for registration: ";
            string regUsername;
            getline(cin, regUsername);
            cout << "Enter password for registration: ";
            string regPassword;
            getline(cin, regPassword);
            if (userDB.registerUser(regUsername, regPassword)) {
                cout << "Registration successful." << endl;
            }
            else {
                cout << "Username already exists." << endl;
            }
            break;
        }
        case 2: {
            cin.ignore();
            cout << "Enter username for login: ";
            string loginUsername;
            getline(cin, loginUsername);
            cout << "Enter password for login: ";
            string loginPassword;
            getline(cin, loginPassword);
            if (userDB.loginUser(loginUsername, loginPassword)) {
                if (loggedInUsersCount < 50) {
                    loggedInUsers[loggedInUsersCount++] = User(loginUsername, loginPassword);
                    cout << "Login successful. Welcome, " << loginUsername << "!" << endl;
                }
                else {
                    cout << "Error: Maximum number of logged in users reached." << endl;
                }
            }
            else {
                cout << "Invalid username or password." << endl;
            }
            break;
        }
        case 3: {
            if (loggedInUsersCount == 0) {
                cout << "Please login first to create a repository." << endl;
            }
            else {
                cin.ignore();
                cout << "Enter repository name: ";
                string repoName;
                getline(cin, repoName);
                cout << "Enter repository description: ";
                string repoDescription;
                getline(cin, repoDescription);
                bool isPublic;
                cout << "Set visibility (1 for Public, 0 for Private): ";
                cin >> isPublic;
                repoManager.createRepository(repoName, repoDescription, isPublic);
                cout << "Repository created successfully!" << endl;
            }
            break;
        }
        case 4: {
            cout << "All Repositories:" << endl;
            repoManager.displayRepositories();
            break;
        }
        case 5: {
            if (loggedInUsersCount == 0) {
                cout << "Please login first to delete a repository." << endl;
            }
            else {
                cin.ignore();
                cout << "Enter the name of the repository you want to delete: ";
                string repoToDelete;
                getline(cin, repoToDelete);
                repoManager.deleteRepository(repoToDelete);
                cout << "Repository deleted successfully!" << endl;
            }
            break;
        }
        case 6: {
            if (loggedInUsersCount == 0) {
                cout << "Please login first to fork a repository." << endl;
            }
            else {
                cin.ignore();
                cout << "Enter the name of the repository you want to fork: ";
                string sourceRepo;
                getline(cin, sourceRepo);
                cout << "Enter the name of your forked repository: ";
                string destinationRepo;
                getline(cin, destinationRepo);
                cout << "Enter the description for your forked repository: ";
                string description;
                getline(cin, description);
                repoManager.forkRepository(sourceRepo, destinationRepo, description);
                cout << "Repository forked successfully!" << endl;
            }
            break;
        }
        case 7: {
            if (loggedInUsersCount == 0) {
                cout << "Please login first to add a commit." << endl;
            }
            else {
                cin.ignore();
                cout << "Enter the name of the repository: ";
                string repoName;
                getline(cin, repoName);
                cout << "Enter commit message: ";
                string commitMessage;
                getline(cin, commitMessage);
                cout << "Enter changed_files changed (separated by space): ";
                string filesChanged;
                getline(cin, filesChanged);
                string changedFiles[100];
                int change_file_counter = 0;
                int pos = 0;
                while ((pos = filesChanged.find(" ")) != string::npos) {
                    changedFiles[change_file_counter] = filesChanged.substr(0, pos);
                    filesChanged.erase(0, pos + 1);
                }
                changedFiles[change_file_counter] = filesChanged; // Add the last file
                repoManager.addCommit(repoName, commitMessage, changedFiles, change_file_counter);
                cout << "Commit added successfully!" << endl;
            }
            break;
        }
        case 8: {
            cin.ignore();
            cout << "Enter the name of the repository: ";
            string repoName;
            getline(cin, repoName);
            repoManager.viewRepositoryStats(repoName);
            break;
        }
        case 9: {
            if (loggedInUsersCount == 0) {
                cout << "Please login first to follow users." << endl;
            }
            else {
                cin.ignore();
                cout << "Enter the username of the user you want to follow: ";
                string followUsername;
                getline(cin, followUsername);
                int follower = loggedInUsersCount - 1;
                int followee = 0; // Assuming the user to follow is at index 0 for demonstration
                socialGraph.followUser(follower, followee);
                cout << "You are now following user " << followUsername << "." << endl;
            }
            break;
        }
        case 10: {
            if (loggedInUsersCount == 0) {
                cout << "Please login first to unfollow users." << endl;
            }
            else {
                cout << "Enter the username of the user you want to unfollow: ";
                string unfollowUsername;
                getline(cin, unfollowUsername);
                int follower = loggedInUsersCount - 1;
                int followee = 0; // Assuming the user to unfollow is at index 0 for demonstration
                socialGraph.unfollowUser(follower, followee);
                cout << "You have unfollowed user " << unfollowUsername << "." << endl;
            }
            break;
        }
        case 11: {
            if (loggedInUsersCount > 0) {
                cout << "Your followed users:" << endl;
                socialGraph.displayFollowedUsers(loggedInUsersCount - 1);
            }
            else {
                cout << "No users are logged in." << endl;
            }
            break;
        }
        case 12: {
            if (loggedInUsersCount == 0) {
                cout << "Please login first to add a file to a repository." << endl;
            }
            else {
                cin.ignore();
                cout << "Enter the name of the repository: ";
                string repoName;
                getline(cin, repoName);
                cout << "Enter the name of the file to add: ";
                string fileName;
                getline(cin, fileName);
                repoManager.addFile(repoName, fileName);
            }
            break;
        }
        case 13: {
            if (loggedInUsersCount == 0) {
                cout << "Please login first to delete a file from a repository." << endl;
            }
            else {
                cin.ignore();
                cout << "Enter the name of the repository: ";
                string repoName;
                getline(cin, repoName);
                cout << "Enter the name of the file to delete: ";
                string fileName;
                getline(cin, fileName);
                repoManager.deleteFile(repoName, fileName);
            }
            break;
        }
        case 14: {
            if (loggedInUsersCount == 0) {
                cout << "Please login first to add a README to a repository." << endl;
            }
            else {
                cin.ignore();
                cout << "Enter the name of the repository: ";
                string repoName;
                getline(cin, repoName);
                repoManager.addReadmeFile(repoName);
            }
            break;
        }
        case 15:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 15);

    return 0;
}

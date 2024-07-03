
using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 100;

    struct Node {
        string key;
        string value;
        Node* next;

        Node(const string& key, const string& value);
    };

    Node* table[TABLE_SIZE];

    int hash(const string& key);

public:
    HashTable();

    void insert(const string& key, const string& value);

    string* find(const string& key);

    void saveToFile(const string& filename);

    void loadFromFile(const string& filename);
};

class Graph {
private:
    static const int MAX_USERS = 1000;
    bool adjMatrix[MAX_USERS][MAX_USERS];

public:
    Graph();
    void addEdge(int user1, int user2);
    void removeEdge(int user1, int user2);
    void displayFollowedUsers(int user);
    void followUser(int follower, int followee);
    void unfollowUser(int follower, int followee);
};
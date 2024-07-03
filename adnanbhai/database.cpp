#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "database.h"


HashTable::Node::Node(const string& key, const string& value) {
    this->key = key;
    this->value = value;
    this->next = NULL;
}

int HashTable::hash(const string& key) {
    int hashValue = 0;
    for (int i = 0; i < key.length(); ++i) {
        hashValue += key[i];
    }
    return hashValue % TABLE_SIZE;
}

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = NULL;
    }
}

void HashTable::insert(const string& key, const string& value) {
    int index = hash(key);
    Node* newNode = new Node(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

string* HashTable::find(const string& key) {
    int index = hash(key);
    Node* curr = table[index];
    while (curr != NULL) {
        if (curr->key == key) {
            return &(curr->value);
        }
        curr = curr->next;
    }
    return NULL;
}

void HashTable::saveToFile(const string& filename) {
    ofstream file;
    file.open(filename.c_str());
    if (file.is_open()) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* curr = table[i];
            while (curr != NULL) {
                file << curr->key << "," << curr->value << "\n";
                curr = curr->next;
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

void HashTable::loadFromFile(const string& filename) {
    ifstream file;
    file.open(filename.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string key, value;
            getline(ss, key, ',');
            getline(ss, value);
            insert(key, value);
        }
        file.close();
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}



Graph::Graph() {
    for (int i = 0; i < MAX_USERS; ++i) {
        for (int j = 0; j < MAX_USERS; ++j) {
            adjMatrix[i][j] = false;
        }
    }
}

void Graph::addEdge(int user1, int user2) {
    adjMatrix[user1][user2] = true;
    adjMatrix[user2][user1] = true;
}

void Graph::removeEdge(int user1, int user2) {
    adjMatrix[user1][user2] = false;
    adjMatrix[user2][user1] = false;
}

void Graph::displayFollowedUsers(int user) {
    cout << "Users followed by User " << user << ": ";
    for (int i = 0; i < MAX_USERS; ++i) {
        if (adjMatrix[user][i]) {
            cout << i << " ";
        }
    }
    cout << endl;
}

void Graph::followUser(int follower, int followee) {
    adjMatrix[follower][followee] = true;
}

void Graph::unfollowUser(int follower, int followee) {
    adjMatrix[follower][followee] = false;
}

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "repository.h"

RepositoryManager::Commit::Commit() {
    message = "";
    fileCount = 0;
    for (int i = 0; i < MAXSIZE; i++) {
        changed_files[i] = "";
    }
}

RepositoryManager::RepositoryNode::RepositoryNode(const string& name, const string& desc, bool visibility) {
    repositoryName = name;
    description = desc;
    isPublic = visibility;
    files_count = 0;
    commitCount = 0;
    commitFileCount = 0;
    left = NULL;
    right = NULL;
}
void RepositoryManager::deleteTree(RepositoryNode* node) {
    if (node == NULL)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

RepositoryManager::RepositoryManager() : root(NULL) {}

void RepositoryManager::createRepository(const string& name, const string& description, bool isPublic) {
    root = insert(root, name, description, isPublic);
}

RepositoryManager::RepositoryNode*
RepositoryManager::insert(RepositoryNode* node, const string& name, const string& desc, bool isPublic) {
    if (node == NULL)
        return new RepositoryNode(name, desc, isPublic);
    if (name < node->repositoryName)
        node->left = insert(node->left, name, desc, isPublic);
    else if (name > node->repositoryName)
        node->right = insert(node->right, name, desc, isPublic);
    return node;
}

void RepositoryManager::displayRepositories() {
    displayInOrder(root);
}

void RepositoryManager::displayInOrder(RepositoryNode* node) {
    if (node == NULL)
        return;
    displayInOrder(node->left);
    cout << "Repository Name: " << node->repositoryName << endl;
    cout << "Description: " << node->description << endl; // Display description
    cout << "Visibility: " << (node->isPublic ? "Public" : "Private") << endl;
    displayInOrder(node->right);
}

void RepositoryManager::deleteRepository(const string& name) {
    root = deleteNode(root, name);
}

RepositoryManager::RepositoryNode* RepositoryManager::deleteNode(RepositoryNode* node, const string& name) {
    if (node == NULL)
        return NULL;
    if (name < node->repositoryName)
        node->left = deleteNode(node->left, name);
    else if (name > node->repositoryName)
        node->right = deleteNode(node->right, name);
    else {
        if (node->left == NULL) {
            RepositoryNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL) {
            RepositoryNode* temp = node->left;
            delete node;
            return temp;
        }
        RepositoryNode* temp = minValueNode(node->right);
        node->repositoryName = temp->repositoryName;
        node->right = deleteNode(node->right, temp->repositoryName);
    }
    return node;
}

RepositoryManager::RepositoryNode* RepositoryManager::minValueNode(RepositoryNode* node) {
    RepositoryNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

void
RepositoryManager::forkRepository(const string& sourceRepo, const string& destinationRepo, const string& description) {
    RepositoryNode* source = search(root, sourceRepo);
    if (source != NULL) {
        root = insert(root, destinationRepo, description, source->isPublic);
        // Copy files array
        for (int i = 0; i < source->files_count; ++i) {
            root->files[i] = source->files[i];
        }
        root->files_count = source->files_count;
        // Copy commitHistory array
        for (int i = 0; i < MAXSIZE; ++i) {
            root->commitHistory[i] = source->commitHistory[i];
        }
    }
    else {
        cout << "Source repository not found." << endl;
    }
}

//void
//RepositoryManager::addCommit(const string &repoName, const string &commitMessage, const string changedFiles[MAXSIZE],
//                             int numberOfFiles) {
//    RepositoryNode *repo = search(root, repoName);
//    if (repo != NULL) {
//        if (repo->commitCount < MAXSIZE) {
//            repo->commitHistory[repo->commitCount].message = commitMessage;
//            for (int i = 0; i < numberOfFiles; ++i) {
//                if (repo->commitHistory[repo->commitCount].fileCount < MAXSIZE) {
//                    repo->commitHistory[repo->commitCount].changed_files[repo->commitHistory[repo->commitCount].fileCount] = changedFiles[i];
//                    repo->commitHistory[repo->commitCount].fileCount++;
//                } else {
//                    cout << "Error: Maximum number of files in a commit reached." << endl;
//                    break;
//                }
//            }
//            repo->commitCount++;
//            cout << "Commit added successfully!" << endl;
//        } else {
//            cout << "Error: Maximum number of commits reached." << endl;
//        }
//    } else {
//        cout << "Repository not found." << endl;
//    }
//}

void RepositoryManager::addCommit(const string& repoName, const string& commitMessage, const string changedFiles[MAXSIZE],
    int numberOfFiles) {
    RepositoryNode* repo = search(root, repoName);
    if (repo != NULL) {
        if (repo->commitCount < MAXSIZE) {
            repo->commitHistory[repo->commitCount].message = commitMessage;
            for (int i = 0; i < numberOfFiles; ++i) {
                if (repo->commitHistory[repo->commitCount].fileCount < MAXSIZE) {
                    repo->commitHistory[repo->commitCount].changed_files[repo->commitHistory[repo->commitCount].fileCount] = changedFiles[i];
                    repo->commitFiles[repo->commitFileCount++] = changedFiles[i]; // Add the file to commitFiles
                    repo->commitHistory[repo->commitCount].fileCount++;
                }
                else {
                    cout << "Error: Maximum number of files in a commit reached." << endl;
                    break;
                }
            }
            repo->commitCount++;
            cout << "Commit added successfully!" << endl;
        }
        else {
            cout << "Error: Maximum number of commits reached." << endl;
        }
    }
    else {
        cout << "Repository not found." << endl;
    }
}

void RepositoryManager::viewRepositoryStats(const string& repoName) {
    RepositoryManager::RepositoryNode* repo = search(root, repoName);
    if (repo != NULL) {
        cout << "Repository Name: " << repo->repositoryName << endl;
        cout << "Visibility: " << (repo->isPublic ? "Public" : "Private") << endl;
        cout << "Files: ";
        for (int i = 0; i < repo->files_count; ++i) {
            cout << repo->files[i];
            if (i < repo->files_count - 1) {
                cout << ", ";
            }
        }
        cout << endl;
        cout << "Commit History: " << endl;
        for (int i = 0; i < repo->commitCount; ++i) {
            cout << "Commit Message: " << repo->commitHistory[i].message << ", Files Changed: ";
            for (int j = 0; j < repo->commitHistory[i].fileCount; ++j) {
                cout << repo->commitHistory[i].changed_files[j];
                if (j < repo->commitHistory[i].fileCount - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
    else {
        cout << "Repository not found." << endl;
    }
}

RepositoryManager::RepositoryNode* RepositoryManager::search(RepositoryNode* node, const string& name) {
    if (node == NULL || node->repositoryName == name)
        return node;
    if (name < node->repositoryName)
        return search(node->left, name);
    return search(node->right, name);
}

void RepositoryManager::addFile(const string& repoName, const string& fileName) {
    RepositoryNode* repo = search(root, repoName);
    if (repo != NULL) {
        repo->files[repo->files_count++] = fileName;
        // Ask for data to save in the file
        ofstream file(fileName);
        if (file.is_open()) {
            string data;
            cout << "Enter data to save in the file (press Enter twice to finish):" << endl;
            while (getline(cin, data) && !data.empty()) {
                file << data << endl;
            }
            file.close();
            cout << "File created and data saved successfully!" << endl;
        }
        else {
            cout << "Error: Unable to create file." << endl;
        }
    }
    else {
        cout << "Repository not found." << endl;
    }
}

void RepositoryManager::deleteFile(const string& repoName, const string& fileName) {
    RepositoryNode* repo = search(root, repoName);
    if (repo != NULL) {
        bool found = false;
        string updatedFiles[MAXSIZE];
        int updated_file_count = 0;
        int i = 0;
        for (; i < repo->files_count; ++i) {
            if (repo->files[i] != fileName) {
                updatedFiles[updated_file_count++] = repo->files[i];
            }
            else {
                found = true; // File found and removed
            }
        }
        if (found) {
            for (i; i < repo->files_count; i++) {
                updatedFiles[updated_file_count++] = repo->files[i];
            }
            repo->files_count = updated_file_count;
            for (int j = 0; j < repo->files_count; ++j) {
                repo->files[j] = updatedFiles[j];
            }
            cout << "File deleted from the repository." << endl;
        }
        else {
            cout << "File not found in repository." << endl;
        }
    }
    else {
        cout << "Repository not found." << endl;
    }
}

void RepositoryManager::addReadmeFile(const string& repoName) {
    RepositoryNode* repo = search(root, repoName);
    if (repo != NULL) {
        string readmeFileName = repoName + "_README.md";
        ofstream readmeFile(readmeFileName);
        if (readmeFile.is_open()) {
            cout << "Enter README content (press Enter twice to finish):" << endl;
            string content;
            while (getline(cin, content) && !content.empty()) {
                readmeFile << content << endl;
            }
            readmeFile.close();
            cout << "README file added successfully!" << endl;
        }
        else {
            cout << "Error: Unable to create README file." << endl;
        }
    }
    else {
        cout << "Repository not found." << endl;
    }
}
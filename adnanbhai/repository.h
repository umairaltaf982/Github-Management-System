using namespace std;

#define MAXSIZE 1000

class RepositoryManager {
private:
    struct Commit {
        string message;
        int fileCount;
        string changed_files[MAXSIZE];

        Commit();
    };

    struct RepositoryNode {
        string repositoryName;
        string description;
        bool isPublic;
        string files[MAXSIZE];
        int files_count;
        Commit commitHistory[MAXSIZE];
        int commitCount;
        string commitFiles[MAXSIZE];
        int commitFileCount;
        RepositoryNode* left;
        RepositoryNode* right;

        RepositoryNode(const string& name, const string& desc, bool visibility);
    };

    RepositoryNode* root;

    void deleteTree(RepositoryNode* node);

public:
    RepositoryManager();

    void createRepository(const string& name, const string& description, bool isPublic);

    RepositoryNode* insert(RepositoryNode* node, const string& name, const string& desc, bool isPublic);

    void displayRepositories();

    void displayInOrder(RepositoryNode* node);

    void deleteRepository(const string& name);

    RepositoryNode* deleteNode(RepositoryNode* node, const string& name);

    RepositoryNode* minValueNode(RepositoryNode* node);

    void forkRepository(const string& sourceRepo, const string& destinationRepo, const string& description);

    void addCommit(const string& repoName, const string& commitMessage, const string changedFiles[MAXSIZE], int numberOfFiles);
    void viewRepositoryStats(const string& repoName);
    RepositoryNode* search(RepositoryNode* node, const string& name);
    void addFile(const string& repoName, const string& fileName);
    void deleteFile(const string& repoName, const string& fileName);
    void addReadmeFile(const string& repoName);
};
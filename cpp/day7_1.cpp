#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class FileSystemEntry {
    int size;
    unordered_map<string, FileSystemEntry*> children;

public:
    FileSystemEntry() : size(-1) {}
    FileSystemEntry(int size): size(size) {}

    int get_size() {
        if (this->size == -1) {
            int size = 0;
            for (auto p: this->children) {
                size += p.second->get_size();
            }
            this->size = size;
        }
        return size;
    }

    // void print() {
    //     this->print(0);
    // }

    // void print(int indent) {
    //     for (auto p: this->children) {
    //         for (int i = 0; i < indent; i++) {
    //             cout << "  ";
    //         }
    //         cout << p.first;
    //         if (p.second->get_size() < 100000) cout << " " << p.second->get_size();
    //         cout << endl;
    //         p.second->print(indent+1);
    //     }
    // }

    bool folder() {
        return this->children.size() > 0;
    }

    // Sum of sizes of folders contained in this folder that are smaller than 100000
    int score() {
        if (!this->folder()) return 0;

        int score = 0;
        for (auto p: this->children) {
            score += p.second->score();
            if (p.second->get_size() < 100000 && p.second->folder()) score += p.second->get_size();
        }
        return score;

    }
    // Adds an entry if it didn't exist
    void add_entry(string name, FileSystemEntry *entry) {
        if (this->children.count(name)) this->children[name]->size = entry->size;
        else this->children[name] = entry;
    }

    FileSystemEntry *child(string name) {
        return this->children[name];
    }
};


int main() {
    FileSystemEntry root;
    vector<FileSystemEntry*> path;
    FileSystemEntry *current_dir = &root;

    string line;
    char name[255];
    int size;
    while(getline(cin, line)) {
        if (line == "$ cd /") {
            // cout << "Back to root | " << line << endl;
            path = {&root};
            current_dir = &root;
        } else if (line == "$ cd ..") {
            // cout << "Back up      | " << line << endl;
            path.pop_back();
            current_dir = path[path.size()-1];
        } else if (sscanf(line.c_str(), "$ cd %s", name)) {
            // cout << "Forward      | " << line << endl;
            FileSystemEntry *folder = new FileSystemEntry();
            current_dir->add_entry(string(name), folder);
            current_dir = current_dir->child(string(name));
            path.push_back(current_dir);
        } else if (sscanf(line.c_str(), "%d %s", &size, name)) {
            // cout << "File         | " << line << endl;
            FileSystemEntry *file = new FileSystemEntry(size);
            current_dir->add_entry(string(name), file);
        }
        // else {
        //     cout << "------------ | " << line << endl;
        // }
    }

    // root.print();
    cout << root.score() << endl;

    return 0;
}
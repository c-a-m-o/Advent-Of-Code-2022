#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
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

    // Adds an entry if it didn't exist
    void add_entry(string name, FileSystemEntry *entry) {
        if (this->children.count(name)) this->children[name]->size = entry->size;
        else this->children[name] = entry;
    }

    FileSystemEntry *child(string name) {
        return this->children[name];
    }

    vector<int> folder_sizes() {
        if (!this->folder()) return vector<int>();
        
        vector<int> res{this->get_size()};
        for (auto p: this->children) {
            vector<int> tmp = p.second->folder_sizes();
            res.insert(res.end(), tmp.begin(), tmp.end());
        }
        return res;
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
    
    vector<int> folder_sizes = root.folder_sizes();
    sort(folder_sizes.begin(), folder_sizes.end());

    cout << *lower_bound(folder_sizes.begin(), folder_sizes.end(), root.get_size() - 40000000) << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Operand {
public:
    virtual int value(int old);
};

class Old : Operand {
    virtual int value(int old) {
        return old;
    }
};

class Constant : Operand {
    int val;
public:
    Constant(string value) {
        this->val = stoi(value);
    }

    virtual int value(int old) {
        return this->val;
    }
};

class Operation {
protected:
    Operand* left;
    Operand* right;
public:
    Operation(Operand* left, Operand* right): left(left), right(right) {}
    virtual int compute(int old);  
};

class Add: Operation {
public:
    Add(Operand* left, Operand* right) : Operation(left, right) {}
    virtual int compute(int old) {
        return this->left->value(old) + this->right->value(old);
    }
};

class Multiply: Operation {
public:
    Multiply(Operand* left, Operand* right) : Operation(left, right) {}
    virtual int compute(int old) {
        return this->left->value(old) * this->right->value(old);
    }
};

class Monkey {
private:
    vector<int> items;
    Operation* op;
    int mod;
    int true_id;
    int false_id;
    int items_processed;
public:
    Monkey(vector<int> items, Operation* op, int mod, int true_id, int false_id) :
        items(items), op(op), mod(mod), true_id(true_id), false_id(false_id), items_processed(0) {}
    void process(vector<Monkey>& monkeys) {
        for (int item : this->items) {
            int new_item = this->op->compute(item) / 3;
            int monkey_id = (new_item % this->mod) ? this->false_id : this->true_id;
            monkeys[monkey_id].items.push_back(new_item);
            this->items_processed++;
        }
        this->items = {};
    }
    int processed() {
        return this->items_processed;
    }

    void print_items() {
        for (auto x: this->items) {
            cout << x << " ";
        }
        cout << endl;
    }
};

int main() {
    string dump;
    char cdump;
    int monkey_id;

    vector<Monkey> monkeys;
    // For each monkey
    while (cin >> dump >> monkey_id >> dump >> cdump) {
        string line;
        // Starting items
        vector<int> items;
        getline(cin, line);
        stringstream sstream(line);
        sstream >> dump >> dump;
        int item;
        while (sstream >> item) {
            items.push_back(item);
            sstream >> cdump;
        }
        // Operation
        string left, op, right;
        cin >> dump >> dump >> dump >> left >> op >> right >> cdump;
        Operand* oleft = left == "old" ? (Operand*) new Old() : (Operand*) new Constant(left);
        Operand* oright = right == "old" ? (Operand*) new Old() : (Operand*) new Constant(right);
        Operation* operation = op == "+" ? (Operation*) new Add(oleft, oright) : (Operation*) new Multiply(oleft, oright);


        // Test
        int mod;
        cin >> dump >> dump >> dump >> mod;
        // True
        int true_id;
        cin >> dump >> dump >> dump >> dump >> dump >> true_id;
        // False
        int false_id;
        cin >> dump >> dump >> dump >> dump >> dump >> false_id;

        monkeys.emplace_back(items, operation, mod, true_id, false_id);
    }
    for (int i = 0; i < 20; i++) {
        for (auto &m: monkeys) m.process(monkeys);
        // for (auto &m : monkeys) m.print_items();
    }

    vector<int> processed_counts(monkeys.size());
    for(int i = 0; i < monkeys.size(); i++) {processed_counts[i] = monkeys[i].processed();};

    nth_element(processed_counts.begin(), processed_counts.end() - 2, processed_counts.end());

    cout << processed_counts[processed_counts.size() - 1] * processed_counts[processed_counts.size() - 2] << endl;

    return 0;
}
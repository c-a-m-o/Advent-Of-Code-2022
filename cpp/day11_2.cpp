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
    int id;
    vector<vector<int>> remainders;
    Operation* op;
    int mod;
    int true_id;
    int false_id;
    int items_processed;
public:
    Monkey(int id, Operation* op, int mod, int true_id, int false_id) :
        id(id), op(op), mod(mod), true_id(true_id), false_id(false_id), items_processed(0) {}

    void init(vector<Monkey>& monkeys, vector<int> values) {
        for (int x: values) {
            vector<int> rem;
            for (auto &m : monkeys) rem.push_back(x % m.mod);
            this->remainders.push_back(rem);
        }
    }

    void process(vector<Monkey>& monkeys) {
        for (auto item : this->remainders) {
            vector<int> new_rem = vector<int>(monkeys.size());
            for (int i = 0; i < monkeys.size(); i++) new_rem[i] = this->op->compute(item[i]) % monkeys[i].mod;

            int monkey_id = (new_rem[this->id]) ? this->false_id : this->true_id;
            monkeys[monkey_id].remainders.push_back(new_rem);
            this->items_processed++;
        }
        this->remainders = {};
    }
    int processed() {
        return this->items_processed;
    }

    // void print_items() {
    //     for (auto x: this->items) {
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }
};

int main() {
    string dump;
    char cdump;
    int monkey_id;

    vector<Monkey> monkeys;
    vector<vector<int>> starting_items;
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
        starting_items.push_back(items);
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

        monkeys.emplace_back(monkey_id, operation, mod, true_id, false_id);
    }

    for (int i = 0; i < monkeys.size(); i++) monkeys[i].init(monkeys, starting_items[i]);
    for (int i = 0; i < 10000; i++) {
        if (i == 20 || i == 1000) {
            for (auto m: monkeys) std::cout << m.processed() << " ";
            std::cout << endl;
        }
        for (auto &m: monkeys) m.process(monkeys);

        
        // for (auto &m : monkeys) m.print_items();
    }

    vector<int> processed_counts(monkeys.size());
    for(int i = 0; i < monkeys.size(); i++) {processed_counts[i] = monkeys[i].processed();};

    std::nth_element(processed_counts.begin(), processed_counts.end() - 2, processed_counts.end());

    std::cout << (long long) processed_counts[processed_counts.size() - 1] * (long long) processed_counts[processed_counts.size() - 2] << endl;
    for (auto x: processed_counts) std::cout << x << " ";
    std::cout << endl;
    return 0;
}
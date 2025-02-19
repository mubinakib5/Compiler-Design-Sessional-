#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

unordered_map<char, vector<string>> grammar;

bool canDerive(string target) {
    queue<string> q;
    set<string> visited;

    q.push("S");  // Start with the initial symbol

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        // If the current string matches the target, return true
        if (current == target) return true;

        // If the current state has already been checked, continue
        if (visited.count(current)) continue;
        visited.insert(current);

        // Try replacing non-terminals in the string
        for (int i = 0; i < current.length(); i++) {
            if (grammar.find(current[i]) != grammar.end()) {
                for (const string &rule : grammar[current[i]]) {
                    string newString = current.substr(0, i) + rule + current.substr(i + 1);

                    // Avoid unnecessary expansions
                    if (newString.length() <= target.length() + 2) {
                        q.push(newString);
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    int n;
    cin >> n;
    grammar.clear();

    for (int i = 0; i < n; i++) {
        char nonTerminal;
        string production;
        cin >> nonTerminal >> production;

        if (production == "NULL") production = "";  // Handle NULL productions properly
        grammar[nonTerminal].push_back(production);
    }

    string inputString;
    cin >> inputString;

    if (canDerive(inputString)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Rejected" << endl;
    }

    return 0;
}

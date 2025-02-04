#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const vector<char> punctuation = {',', '{', '}', ';', '>'};
const vector<char> operators = {'+', '-', '*', '='};

void solve() {
    ifstream inputFile("input.txt");
    char ch;
    string s = "";
    while (inputFile.get(ch)) {
        s += ch;
    }

    inputFile.close();
    vector<char> ansPunctuation;
    vector<char> ansOperator;
    vector<string> ansNumber, ansKeyword;
    vector<pair<string, int>> ansVariable;
    string clean;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] >= '0' and s[i] <= '9') {
            string here = "";
            while ((i < (int)s.size()) and ((s[i] >= '0' and s[i] <= '9') or s[i] == '.')) {
                here += s[i];
                i++;
            }
            ansNumber.push_back(here);
        } else
            clean += s[i];
    }

    for (int i = 0; i < (int)clean.size(); ++i) {
        if (find(operators.begin(), operators.end(), clean[i]) != operators.end()) {
            ansOperator.push_back(clean[i]);
            clean[i] = '>';
        }
    }

    vector<string> ansFunction;
    for (int i = 0; i < (int)clean.size(); ++i) {
        if (i + 1 < (int)clean.size() and clean[i] == '(') {
            int j = i - 1;
            string var = "";
            while (j >= 0 and (clean[j] != ' ') and (clean[j] != '\n')) {
                if (find(punctuation.begin(), punctuation.end(), clean[j]) != punctuation.end()) break;
                var += clean[j];
                clean[j] = ' ';
                --j;
            }
            if (!var.empty()) {
                reverse(var.begin(), var.end());
                if (var != "for" && var != "while" && var != "if" && var != "else") {
                    ansFunction.push_back(var + "()");
                }
            }
        }
    }

    for (auto i : ansFunction) {
        cout << "< function, " << i << "> " << endl;
    }
    cout << "\n";

    for (int i = 0; i < (int)clean.size(); ++i) {
        if (clean[i] == '(' or clean[i] == ')') clean[i] = ' ';
    }
    int varCnt = 1;
    vector<string> occurred;
    for (int i = 0; i < (int)clean.size(); ++i) {
        if (find(punctuation.begin(), punctuation.end(), clean[i]) != punctuation.end()) {
            ansPunctuation.push_back(clean[i]);
            int j = i;
            string var = "";
            while (j >= 0 and (clean[j] != ' ') and (clean[j] != '\n')) {
                var += clean[j];
                clean[j] = ' ';
                j--;
            }

            if (!var.empty()) {
                reverse(var.begin(), var.end());
                string pris = "";
                for (auto l : var) {
                    if (find(punctuation.begin(), punctuation.end(), l) == punctuation.end()) {
                        pris += l;
                    }
                }

                if (find(occurred.begin(), occurred.end(), pris) == occurred.end() and ((int)pris.size() > 0)) ansVariable.push_back({pris, varCnt++});
                occurred.push_back(pris);
            }
        }
    }
    for (int i = 0; i < (int)clean.size(); ++i) {
        string var = "";
        while ((i < (int)clean.size()) and (clean[i] != ' ') and (clean[i] != '\n')) {
            var += clean[i];
            i++;
        }
        // cerr << var << endl;
        // No explicit keyword check required.
    }

    for (auto [u, v] : ansVariable) {
        cout << ("< ") << v << (", id >") << endl;
    }

    for (auto [u, v] : ansVariable) {
        cout << v << " -> " << u << endl;
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //    cin >> t;
    while (t--) solve();
}

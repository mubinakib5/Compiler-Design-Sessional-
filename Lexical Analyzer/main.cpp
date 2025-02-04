#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

const int MAX = 1900000;

// Check if a character is a special character
bool isSpecialCharacter(char ch) {
    return !isalnum(ch) && ch != '.' && ch != '_';
}

// Check if a string is a keyword
bool isKeyword(const string &s) {
    set<string> keywords = {"int", "float", "double", "char", "string", "bool", "if", "else", "for", "while","elseif", "do", "return", "break", "continue", "switch", "case", "default", "void", "main", "false", "true"};
    return keywords.find(s) != keywords.end();
}

// Check if a string is an operator
bool isOperator(const string &s) {
    set<string> operators = {"+", "-", "*", "/", "%", "=","==","+=","-=","*=","/=","<",">","<=",">=","&&","||","!","!=","<<",">>", "|", "&"};
    return operators.find(s) != operators.end();
}

// Check if a string is a valid number
bool isNumber(const string &s) {
    bool decimal = false;
    for (char ch : s) {
        if (!isdigit(ch)) {
            if (ch == '.' && !decimal) {
                decimal = true;
            } else {
                return false;
            }
        }
    }
    return true;
}

// Check if a string is a valid identifier (variable)
bool isIdentifier(const string &s) {
    if (isdigit(s[0])) return false;
    for (char ch : s) {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return true;
}

// Check if a string is a function
bool isFunction(const string &s) {
    return s.back() == '(' && s.size() > 1;
}

int main() {
	FILE *ptr;
	ptr = fopen("input.txt", "r");
    char arr[MAX];

    map<string, set<string>> categorizedTokens;

    string currentToken;
    int i;
    ptr = fopen("input.txt", "r");

    while (fgets(arr, MAX, ptr))
	{
     for (i = 0; arr[i] != '\0'; i++)
		{
        char ch = arr[i];

        if (isSpecialCharacter(ch) || isspace(ch)) {
            if(ch == '='){
                if(arr[i+1] == '='){
                    string specialToken(1, ch);
                    specialToken += arr[i+1];
                    categorizedTokens["operators"].insert(specialToken);
                    i++;
                }
                else{
                    string specialToken(1, ch);
                    categorizedTokens["operators"].insert(specialToken);
                }
            }
            if(ch == '>'){
                 if(arr[i+1] == '>'){
                    string specialToken(1, ch);
                    specialToken += arr[i+1];
                    categorizedTokens["operators"].insert(specialToken);
                    i++;
                }
                else{
                    string specialToken(1, ch);
                    categorizedTokens["operators"].insert(specialToken);
                }
            }
            if(ch == '<'){
                 if(arr[i+1] == '<'){
                    string specialToken(1, ch);
                    specialToken += arr[i+1];
                    categorizedTokens["operators"].insert(specialToken);
                    i++;
                }
                else{
                    string specialToken(1, ch);
                    categorizedTokens["operators"].insert(specialToken);
                }
            }
            if(ch == '>' || ch == '<' || ch == '%' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '!') {
                if(arr[i+1] == '='){
                    string specialToken(1, ch);
                    specialToken += arr[i+1];
                    categorizedTokens["operators"].insert(specialToken);
                    i++;
                }
                else{
                    string specialToken(1, ch);
                    categorizedTokens["operators"].insert(specialToken);
                }
            }
            if(ch == '&'){
                if(arr[i+1] == '&'){
                    string specialToken(1, ch);
                    specialToken += arr[i+1];
                    categorizedTokens["operators"].insert(specialToken);
                    i++;
                }
            }
            if(ch == '|'){
                if(arr[i+1] == '|'){
                    string specialToken(1, ch);
                    specialToken += arr[i+1];
                    categorizedTokens["operators"].insert(specialToken);
                    i++;
                }
            }
            if(ch == '(') {
                string function;
                for (size_t j = i - 1; j >= 0; --j) {
                    if (isspace(arr[j]) || isSpecialCharacter(arr[j]) || arr[j] == '(') {
                        break;
                    }
                    function = arr[j] + function;
                }
                function = function + "(";
                if (isFunction(function)) {
                    categorizedTokens["functions"].insert(function + ")");
                }
            }

            if (!currentToken.empty()) {
                if (isKeyword(currentToken)) {
                    categorizedTokens["keywords"].insert(currentToken);
                } else if (isNumber(currentToken)) {
                    categorizedTokens["numbers"].insert(currentToken);
                } else if (isIdentifier(currentToken)) {
                    categorizedTokens["variables"].insert(currentToken);
                }
                currentToken.clear();
            }

            // Handle special character as a separate token
            if (isSpecialCharacter(ch) && ch != ' ') {
                string specialToken(1, ch);
                if (isOperator(specialToken)) {
                    categorizedTokens["operators"].insert(specialToken);
                } else {
                    categorizedTokens["others"].insert(specialToken);
                }
            }
        } else {
            currentToken += ch;
        }
    }

    // Check if the last token is valid
    if (!currentToken.empty()) {
        if (isKeyword(currentToken)) {
            categorizedTokens["keywords"].insert(currentToken);
        } else if (isNumber(currentToken)) {
            categorizedTokens["numbers"].insert(currentToken);
        } else if (isIdentifier(currentToken)) {
            categorizedTokens["variables"].insert(currentToken);
        }
    }

    }
    fclose(ptr);
    set<string> functions = categorizedTokens["functions"];
    for (const string &function : functions) {
        string functionName = function.substr(0, function.find('('));
        categorizedTokens["keywords"].erase(functionName);
        categorizedTokens["variables"].erase(functionName);
    }

    for (const auto &[category, items] : categorizedTokens) {
        cout << category << ": ";
        for (const string &item : items) {
            if(item == "\n")
                continue;
            cout << item << " ";
        }
        if (!items.empty()) {
            cout << "\b";
        }
        cout << endl;
    }


    return 0;
}

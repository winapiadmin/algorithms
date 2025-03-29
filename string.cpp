#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to reverse a string
string reverseString(const string &s) {
    return string(s.rbegin(), s.rend());
}

// Function to check if a string is a palindrome
bool isPalindrome(const string &s) {
    int i = 0, j = s.size() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

// Helper function for KMP: Computes the longest prefix suffix (LPS) array
void computeLPS(const string &pattern, vector<int> &lps) {
    int length = 0;
    int i = 1;
    lps[0] = 0;
    while (i < pattern.size()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search algorithm to find all occurrences of pattern in text
vector<int> KMPSearch(const string &text, const string &pattern) {
    vector<int> occurrences;
    if (pattern.empty())
        return occurrences;
    int n = text.size();
    int m = pattern.size();
    vector<int> lps(m);
    computeLPS(pattern, lps);
    int i = 0, j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == m) {
            occurrences.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return occurrences;
}

int main() {
    int option;
    cout << "Select string algorithm:\n";
    cout << "1. Reverse String\n";
    cout << "2. Check Palindrome\n";
    cout << "3. KMP Pattern Search\n";
    cout << "Enter option number: ";
    cin >> option;
    cin.ignore(); // consume newline character

    if (option == 1) {
        string input;
        cout << "Enter string: ";
        getline(cin, input);
        cout << "Reversed string: " << reverseString(input) << "\n";
    } else if (option == 2) {
        string input;
        cout << "Enter string: ";
        getline(cin, input);
        cout << (isPalindrome(input) ? "The string is a palindrome." : "The string is not a palindrome.") << "\n";
    } else if (option == 3) {
        string text, pattern;
        cout << "Enter text: ";
        getline(cin, text);
        cout << "Enter pattern: ";
        getline(cin, pattern);
        vector<int> occ = KMPSearch(text, pattern);
        if (occ.empty())
            cout << "Pattern not found in the text.\n";
        else {
            cout << "Pattern found at position(s): ";
            for (int pos : occ)
                cout << pos << " ";
            cout << "\n";
        }
    } else {
        cout << "Invalid option.\n";
    }
    
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const string ALPHABET_25 = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

string normalize_letters(const string& text) {
    string result = "";
    for (char ch : text) {
        if (isalpha(ch)) {
            char upper_ch = toupper(ch);
            if (upper_ch == 'J') {
                result += 'I';
            } else {
                result += upper_ch;
            }
        }
    }
    return result;
}

struct KeySquare {
    char square[5][5];
    unordered_map<char, pair<int, int>> pos;
};

KeySquare build_key_square(const string& key) {
    string norm_key = normalize_letters(key);
    unordered_set<char> seen;
    string key_stream = "";

    for (char ch : norm_key) {
        if (ALPHABET_25.find(ch) != string::npos && seen.find(ch) == seen.end()) {
            seen.insert(ch);
            key_stream += ch;
        }
    }

    for (char ch : ALPHABET_25) {
        if (seen.find(ch) == seen.end()) {
            seen.insert(ch);
            key_stream += ch;
        }
    }

    KeySquare ks;
    int idx = 0;
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            ks.square[r][c] = key_stream[idx];
            ks.pos[key_stream[idx]] = {r, c};
            idx++;
        }
    }
    return ks;
}

vector<pair<char, char>> prepare_plaintext(const string& plaintext) {
    string text = normalize_letters(plaintext);
    vector<pair<char, char>> pairs;
    
    int i = 0;
    while (i < text.length()) {
        char a = text[i];
        char b = (i + 1 < text.length()) ? text[i + 1] : 'X';

        if (a == b) {
            pairs.push_back({a, 'X'});
            i += 1; 
        } else {
            pairs.push_back({a, b});
            i += 2; 
        }
    }
    return pairs;
}

string encrypt_playfair(const string& plaintext, const string& key) {
    KeySquare ks = build_key_square(key);
    vector<pair<char, char>> pairs = prepare_plaintext(plaintext);
    string out = "";

    for (auto p : pairs) {
        char a = p.first;
        char b = p.second;

        int ra = ks.pos[a].first;
        int ca = ks.pos[a].second;
        int rb = ks.pos[b].first;
        int cb = ks.pos[b].second;

        if (ra == rb) {
            out += ks.square[ra][(ca + 1) % 5];
            out += ks.square[rb][(cb + 1) % 5];
        } else if (ca == cb) {
            out += ks.square[(ra + 1) % 5][ca];
            out += ks.square[(rb + 1) % 5][cb];
        } else {
            out += ks.square[ra][cb];
            out += ks.square[rb][ca];
        }
    }
    return out;
}

int main() {
    string key, plaintext;
    
    cout << "Nhap khoa (key): ";
    getline(cin, key); 
    
    cout << "Nhap ban ro (plaintext): ";
    getline(cin, plaintext);

    string ciphertext = encrypt_playfair(plaintext, key);
    cout << "Ciphertext: " << ciphertext << endl;

    return 0;
}
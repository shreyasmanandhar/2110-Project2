// Utils.cpp
// Purpose: shared string and file-loading helpers.
// Author: Member B (shared)

#include "Utils.h"
#include <cctype>
#include <iostream>

using namespace std;

// trim whitespace incl. \r
string trim(const string& s) {
    const char* ws = " \t\r\n\v\f";
    size_t start = s.find_first_not_of(ws);
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(ws);
    return s.substr(start, end - start + 1);
}

// lowercase copy
string toLower(const string& s) {
    string out = s;
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = static_cast<char>(tolower(static_cast<unsigned char>(out[i])));
    return out;
}

// uppercase copy
string toUpper(const string& s) {
    string out = s;
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = static_cast<char>(toupper(static_cast<unsigned char>(out[i])));
    return out;
}

// case-insensitive compare
bool equalsIgnoreCase(const string& a, const string& b) {
    return toLower(a) == toLower(b);
}

// blank or comment line
bool isSkippable(const string& line) {
    string t = trim(line);
    return t.empty() || t[0] == '#';
}

// split + trim fields
vector<string> splitFields(const string& line, char delim) {
    vector<string> fields;
    string cur;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == delim) {
            fields.push_back(trim(cur));
            cur.clear();
        } else {
            cur += line[i];
        }
    }
    fields.push_back(trim(cur));
    return fields;
}

// load warning
void printWarning(const string& file, int lineNum, const string& reason) {
    cout << "Warning: " << file << ", line " << lineNum << ": " << reason << "\n";
}

// load summary
void printLoadSummary(const string& file, int accepted, int rejected,
                      const string& extra) {
    cout << file << ": " << accepted << " accepted, " << rejected << " rejected"
              << extra << "\n";
}

// missing file
void printOpenError(const string& file) {
    cout << "Error: cannot open file " << file << " (treated as empty)\n";
}

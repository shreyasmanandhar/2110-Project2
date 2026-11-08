//Utils.h
//Purpose: shared string and file-loading helpers.
//Author: Member B (shared)
//Member A --- use these in the facilities loader
//Member C --- use these in the departments loader

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

//trim space, tab, \r, \n from both ends
std::string trim(const std::string& s);

//ASCII lowercase copy
std::string toLower(const std::string& s);

//ASCII uppercase copy
//Member A --- use for facility ID normalization
std::string toUpper(const std::string& s);

//case-insensitive compare
//Member C --- use for department name matching
bool equalsIgnoreCase(const std::string& a, const std::string& b);

//true if blank or first non-whitespace char is '#'
bool isSkippable(const std::string& line);

//split on delim, trim each field, keep empty fields
std::vector<std::string> splitFields(const std::string& line, char delim = '|');

//"Warning: file, line N: reason"
void printWarning(const std::string& file, int lineNum, const std::string& reason);

//"file: X accepted, Y rejected" + optional extra text
//Member A --- pass hash diagnostic as extra, e.g. " (capacity 11, entries 10, collisions 3)"
void printLoadSummary(const std::string& file, int accepted, int rejected, const std::string& extra = "");

//"Error: cannot open file"
void printOpenError(const std::string& file);

#endif

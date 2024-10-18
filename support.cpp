#include "support.h"

string ITrim(const string& s) {
    int start = 0;
    while (start < s.length() && s[start] == ' ') {
        start++;
    }
    string result;
    for (int i = start; i < s.length(); i++) {
        result += s[i];
    }
    return result;
}

string rTrim(const string& s) {
    int end = s.length() - 1;
    while (end >= 0 && s[end] == ' ') {
        end--;
    }
    string result;
    for (int i = 0; i <= end; i++) {
        result += s[i];
    }
    return result;
}

string trim(const string& s) {
    string result;
    bool inSpace = false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {
            result += s[i];
            inSpace = false;
        } else if (!inSpace) {
            result += s[i];
            inSpace = true;
        }
    }
    return ITrim(result);
}

string nameStr(const string& s) {
    string trimmed = trim(s);
    string result;
    bool capitalizeNext = true;
    for (int i = 0; i < trimmed.length(); i++) {
        if (trimmed[i] == ' ') {
            result += ' ';
            capitalizeNext = true;
        } else {
            if (capitalizeNext) {
                result += (trimmed[i] >= 'a' && trimmed[i] <= 'z') ? (trimmed[i] - 32) : trimmed[i];
                capitalizeNext = false;
            } else {
                result += (trimmed[i] >= 'A' && trimmed[i] <= 'Z') ? (trimmed[i] + 32) : trimmed[i];
            }
        }
    }
    return result;
}
string doubleToString(double n) {
    ostringstream oss;
    oss << fixed << static_cast<long long>(n);  
    return oss.str();
}
string formatMoney(double n) {
    string result = doubleToString(n);
    size_t length = result.length();
    int insertPosition = length - 3;
    while (insertPosition > 0) {   
        result.insert(insertPosition, ".");
        insertPosition -= 3;
    }
    return result;
}
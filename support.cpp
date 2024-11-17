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
const char mau[10][8] = { "khong ","mot ","hai ","ba ","bon ","nam ","sau ", "bay ", "tam ","chin " };
void get(int vt, int c[], ostringstream& oss)
{
   if (vt == 8) return;
    switch (vt)
    {
    case 2: oss << "trieu ";
        break;
    case 5:
        if (!((c[vt] == 0) && (c[vt - 1] == 0) && (c[vt - 2] == 0)))
            oss << "nghin ";
        break;
    case 3: case 6:
    	if(c[vt]!=0 || c[vt+1]!=0 || c[vt+2]!=0)
            oss << "tram ";
        break;
    case 4: case 7: case 1:
        if (c[vt] != 0)
            oss << "muoi ";
        else
        {
            if (c[vt + 1] != 0)
                oss << "le ";
        }
        break;
    }
}
void read_number(double d, ostringstream& oss) {
    long n = static_cast<long>(d);
    if (n == 0) {
        oss << "không";
        return;
    }
    int c[10];
    for (int i = 1; i <= 8; i++)
        c[i] = 0;

    int i = 8;
    while (n != 0) {
        c[i] = n % 10;
        n = n / 10;
        i--;
    }
    int vtd = 9;
    for (int i = 1; i <= 8; i++) {
        if (c[i] != 0) {
            vtd = i;
            break;
        }
    }
    if (vtd == 9) {
        oss << "khong";
        return;
    }
    for (int i = vtd; i <= 8; i++) {
        switch (c[i]) {
            case 1: case 2: case 3: case 4: case 6: case 7: case 8: case 9:
                if (!((c[i] == 1) && ((i == 7) || (i == 1) || (i == 4))))
                    oss << mau[c[i]];
                get(i, c, oss);
                break;
            case 5:
                if (i == 8 || i == 5 || i == 2)
                    oss << "lam ";
                else
                    oss << mau[c[i]];
                get(i, c, oss);
                break;
            case 0:
                if (((i == 6) || (i == 3)) && ((c[i + 2] != 0) || ((c[i + 1] != 0))))
                    oss << mau[c[i]];
                get(i, c, oss);
                break;
        }
    }
}
int stringToInt(std::string str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;  
    } else if (str[0] == '+') {
        i = 1;  
    }
    for (; i < str.length(); i++) {
        result = result * 10 + (str[i] - '0');
    }

    return result * sign;
}
string toUpper(const string& input) {
    string result = input;
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] >= 'a' && result[i] <= 'z') {
            result[i] = result[i] - 'a' + 'A'; 
        }
    }
    return result;
}
int isCharacter(const string& input) {
    for (char c : input) {
        if (!isalpha(c)) {
            return 0;
        }
    }
    return 1;
}
bool isPhoneNumber(const string& input){
    if (input.length() != 10 || input[0] != '0') {
        return false;
    }
    for (int i = 1; i < input.length(); ++i) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}
bool isDate(const string& input){
    if (input.length() != 10) {
        return false;
    }
    if (input[2] != '/' || input[5] != '/') {
        return false;
    }
    for (int i = 0; i < input.length(); ++i) {
        if (i == 2 || i == 5) {
            continue;
        }
        if (!isdigit(input[i])) {
            return false;
        }
    }
    int day = stoi(input.substr(0, 2));
    int month = stoi(input.substr(3, 2));
    int year = stoi(input.substr(6, 4));
    return checkDate(day, month, year);
}
bool isSex(const string& input){
    if (input == "1" || input == "0") {
        return true;
    }
    return false;

}
bool parseDate(const string& dateStr, int& day, int& month, int& year) {
    stringstream ss(dateStr);
    char delimiter;
    if (ss >> day >> delimiter >> month >> delimiter >> year) {
        return checkDate(day, month, year);
    }
    return false;
}
bool checkDate(int day, int month, int year) {
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeap) {
            daysInMonth[1] = 29;
        }
    }
    return day <= daysInMonth[month - 1];
}

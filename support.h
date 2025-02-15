#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <sstream>
#include <vector>
using namespace std;

string ITrim(const string& s);
string rTrim(const string& s);
string trim(const string& s);
string nameStr(const string& s);
string doubleToString(double n);
string formatMoney(double n);
void get(int vt, int c[], ostringstream& oss);
void read_number(double d, ostringstream& oss);
int stringToInt(std::string str);
string toUpper(const string& input);
int isCharacter(const string& input);
bool isPhoneNumber(const string& input);
bool isDate(string input);
bool isSex(const string& input);
bool parseDate(const string& dateStr, int& day, int& month, int& year);
bool checkDate(int day, int month, int year) ;
#endif

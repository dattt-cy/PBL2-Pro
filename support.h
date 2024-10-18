#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <sstream>
using namespace std;

string ITrim(const string& s);
string rTrim(const string& s);
string trim(const string& s);
string nameStr(const string& s);
string doubleToString(double n);
string formatMoney(double n);
void get(int vt, int c[], ostringstream& oss);
void read_number(double d, ostringstream& oss);

#endif
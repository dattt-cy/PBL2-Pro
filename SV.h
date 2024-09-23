#pragma once
#include <string>
#include <iostream>
using namespace std;
class SV{
    private:
        int MSSV;
        string Name;
        double DTB;
        double DRL;
    public:
        SV(int = 0, string = "" , double = 0.0, double = 0.0);
        SV(const SV&);
        ~SV();
        void ShowSV();
        int GetMSSV()const;
        void SetMSSV(int);   
        string GetName();  
        void SetName(const string&); 
        double GetDTB();
        void SetDTB(double);        
        double GetDRL();
        void SetDRL(double); 

};
#include "SV.h"

SV::SV(int m, string n, double dtb, double drl)
: MSSV(m), Name(n), DTB(dtb), DRL(drl)
{

}
SV::SV(const SV& p)
{
    this->MSSV = p.MSSV;
    this->Name = p.Name;
    this->DTB = p.DTB;  
    this->DRL = p.DRL;
}
SV::~SV(){}
void SV::ShowSV()
{
    cout << this->MSSV << " " << this->Name << " " << this->DTB << " " << this->DRL << endl;
}
int SV::GetMSSV()const  {
    return MSSV;
}

void SV::SetMSSV(int m) {
    MSSV = m;
}
string SV::GetName(){
    return Name;
}
void SV::SetName(const string& n) {
    Name = n;
}
double SV::GetDTB(){
    return DTB;
}
void SV::SetDTB(double dtb) {
    DTB = dtb;
}
double SV::GetDRL(){
    return DRL;
}
void SV::SetDRL(double drl) {
    DRL = drl;
}
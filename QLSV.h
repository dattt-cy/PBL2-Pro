#include "SV.h"
#include <algorithm>
#include <iostream>

class QLSV {
public:
    QLSV();
    ~QLSV();
    void Show();
    void Add(SV sv);
    void AddRange(SV* svArray, int n);
    int IndexOf(const SV& sv);
    void RemoveAt(int index);
    void Remove(const SV& sv);
    void Sort();
    void Update(int mssv);
    int Get_Count();

private:
    SV* p;
    int Count;
};
#include "QLSV.h"
#include <iostream>
#include <string>
using namespace std;

QLSV::QLSV() {
    this->p = nullptr;
    this->Count = 0;
}

QLSV::~QLSV() {
    if (p != nullptr) {
        delete[] this->p;
    }
}

void QLSV::Show() {
    for (int i = 0; i < Count; i++) {
        (*(p + i)).ShowSV();
    }
}

void QLSV::Add(SV sv) {
    SV* temp = new SV[Count + 1];
    for (int i = 0; i < Count; ++i) {
        temp[i] = p[i];
    }
    temp[Count] = sv;
    delete[] p;
    p = temp;
    ++Count;
}

void QLSV::AddRange(SV* svArray, int n) {
    SV* temp = new SV[Count + n];
    for (int i = 0; i < Count; ++i) {
        temp[i] = p[i];
    }
    for (int i = 0; i < n; ++i) {
        temp[Count + i] = svArray[i];
    }
    delete[] p;
    p = temp;
    Count += n;
}

int QLSV::IndexOf(const SV& sv) {
    for (int i = 0; i < Count; ++i) {
        if (p[i].GetMSSV() == sv.GetMSSV()) {
            return i;
        }
    }
    return -1;
}

void QLSV::RemoveAt(int index) {
    if (index < 0 || index >= Count) return;

    SV* temp = new SV[Count - 1];
    for (int i = 0, j = 0; i < Count; ++i) {
        if (i != index) {
            temp[j++] = p[i];
        }
    }
    delete[] p;
    p = temp;
    --Count;
    if (Count == 0) {
        p = nullptr;
    }
}

void QLSV::Remove(const SV& sv) {
    int index = IndexOf(sv);
    if (index != -1) {
        RemoveAt(index);
    }
}

void QLSV::Sort() {
    std::sort(p, p + Count, [](const SV& a, const SV& b) {
        return a.GetMSSV() < b.GetMSSV();
    });
}

void QLSV::Update(int mssv) {
    for (int i = 0; i < Count; ++i) {
        if (p[i].GetMSSV() == mssv) {
            string name;
            double dtb, drl;
            cout << "Nhap ten moi: ";
            getline(cin, name);
            size_t start = name.find_first_not_of(' ');
            size_t end = name.find_last_not_of(' ');
            if (start != string::npos && end != string::npos) {
                name = name.substr(start, end - start + 1);
            } else {
                name.clear();
            }
            cout << "Nhap DTB moi: ";
            cin >> dtb;
            cout << "Nhap DRL moi: ";
            cin >> drl;
            p[i].SetName(name);
            p[i].SetDTB(dtb);
            p[i].SetDRL(drl);
            return;
        }
    }
}

int QLSV::Get_Count() {
    return Count;
}
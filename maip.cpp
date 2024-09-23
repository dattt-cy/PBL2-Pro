#include "QLSV.h"
#include <iostream>
#include "SV.h"

using namespace std;

int main() {    
    QLSV qlsv;
    SV sv1(1, "Nguyen Van A", 8.0, 9.0);
    SV sv2(2, "Le Thi B", 7.5, 8.5);
    SV sv3(3, "Tran Van C", 9.0, 9.5);
    
    qlsv.Add(sv2);
    qlsv.Add(sv1);
    qlsv.Add(sv3);

    cout << "Danh sach sinh vien: " << endl;
    qlsv.Show();

    qlsv.Sort();
    cout << "\nDanh sach sinh vien sau khi sap xep theo MSSV: " << endl;
    qlsv.Show();

    cout << "\nCap nhat thong tin sinh vien co MSSV = 2:" << endl;
    qlsv.Update(2);
    cout << "\nDanh sach sinh vien sau khi cap nhat: " << endl;
    qlsv.Show();

    cout << "\nXoa sinh vien co MSSV = 1" << endl;
    qlsv.Remove(sv1);
    cout << "\nDanh sach sinh vien sau khi xoa: " << endl;
    qlsv.Show();

    return 0;
}

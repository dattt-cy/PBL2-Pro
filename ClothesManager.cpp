#include "ClothesManager.h"
#include "Male.h"
#include "Female.h"
#include "Children.h" 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

void ClothesManager::addClothes(Clothes* clothes) {
    list.addNode(clothes);
}

void ClothesManager::printAllClothes() const {
    system("cls"); 

    cout << endl;
    cout << "==============================================================SHOP QUAN AO GAU GAU ================================================================\n";
    cout << "                                                           --------------------------                                                              \n";
    cout << "                                                              DANH SACH SAN PHAM                                                                   \n";
    cout << "                                                           --------------------------                                                              \n";

    Node<Clothes*>* current = list.getHead();

    // In tiêu đề bảng
    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;
    cout << "| ID       | Ten san pham              | Thuong hieu       | Gia (VND)     | Size, Mau, So luong                                                   |" << endl;
    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;

    while (current != nullptr) {
        // In thông tin cơ bản của sản phẩm
        cout << "| " << left << setw(8) << current->data->getID() << " | "
             << setw(25) << current->data->getName() << " | "
             << setw(17) << current->data->getBranch() << " | "
             << setw(13) << current->data->getPrice() << " | ";

        stringstream ss;
        Node<Variant*>* variant = current->data->getVariants().getHead();
        bool hasValidVariant = false;

        while (variant != nullptr) {
            if (!variant->data->getSize().empty() &&
                !variant->data->getColor().empty() &&
                variant->data->getQuantity() >= 0) {

                ss << "{" << variant->data->getSize()
                   << ", " << variant->data->getColor()
                   << ", " << variant->data->getQuantity() << "} ";
                hasValidVariant = true;
            }
            variant = variant->next;
        }

        if (hasValidVariant) {
            cout << left << setw(69) << ss.str() << " |" << endl;
        } else {
            cout << left << setw(69) << "<!> HET HANG CHO SAN PHAM NAY" << " |" << endl;
        }

        current = current->next;
    }

    // In dòng cuối cùng của bảng
    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;

    system("pause"); 
}

void ClothesManager::printByType(const string& type) const {
    system("cls"); // Xóa màn hình (Chạy trên Windows)

    // Tiêu đề cho từng thể loại sản phẩm
    string title;
    if (type == "Female") title = "SAN PHAM CHO NU";
    else if (type == "Male") title = "SAN PHAM CHO NAM";
    else if (type == "Children") title = "SAN PHAM CHO TRE EM";
    else title = "LOAI SAN PHAM KHONG HOP LE";

 
    cout << endl;
    cout << "==============================================================SHOP QUAN AO GAU GAU ================================================================\n";
    cout << "                                                           --------------------------                                                              \n";
    cout << "                                                           " <<"     " << title << "                                                              \n";
    cout << "                                                           --------------------------                                                              \n";

    Node<Clothes*>* current = list.getHead();

    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;
    cout << "| ID       | Ten san pham              | Thuong hieu       | Gia (VND)     | Size, Mau, So luong                                                   |" << endl;
    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;

    bool hasItems = false; // Kiểm tra xem có sản phẩm nào được in ra hay không

    while (current != nullptr) {
        // Kiểm tra loại sản phẩm và chỉ in nếu khớp với loại đã chọn
        if ((type == "Female" && dynamic_cast<Female*>(current->data)) ||
            (type == "Male" && dynamic_cast<Male*>(current->data)) ||
            (type == "Children" && dynamic_cast<Children*>(current->data))) {

            // In thông tin cơ bản của sản phẩm
            cout << "| " << left << setw(8) << current->data->getID() << " | "
                 << setw(25) << current->data->getName() << " | "
                 << setw(17) << current->data->getBranch() << " | "
                 << setw(13) << current->data->getPrice() << " | ";

            // In các biến thể trong cùng một dòng
            stringstream ss;
            Node<Variant*>* variant = current->data->getVariants().getHead();
            bool hasValidVariant = false;

            while (variant != nullptr) {
                if (!variant->data->getSize().empty() &&
                    !variant->data->getColor().empty() &&
                    variant->data->getQuantity() > 0) {

                    ss << "{" << variant->data->getSize()
                       << ", " << variant->data->getColor()
                       << ", " << variant->data->getQuantity() << "} ";
                    hasValidVariant = true;
                }
                variant = variant->next;
            }

            if (hasValidVariant) {
                cout << left << setw(69) << ss.str() << " |" << endl;
            } else {
                cout << left << setw(69) << "<!> HET HANG CHO SAN PHAM NAY" << " |" << endl;
            }

        }
        current = current->next;
    }


     cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;

    system("pause"); // Tạm dừng màn hình (Chạy trên Windows)
}


Clothes* ClothesManager::findByID(const string& id) const {
    Node<Clothes*>* current = list.getHead();
    while (current != nullptr) {
        if (current->data->getID() == id) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}
void ClothesManager::readClothesFromFile(const string& filename) {
    ifstream filein(filename);
    if (!filein.is_open()) {
        cerr << "Không thể mở file!" << endl;
        return;
    }
    string line;
    Clothes* item = nullptr;

    while (getline(filein, line)) {
        if (line[0] == 'M') {
            item = new Male("", "", 0.0, "", "", "", 0);
        } else if (line[0] == 'F') {
            item = new Female("", "", 0.0, "", "", "", 0);
        } else if (line[0] == 'C') {
            item = new Children("", "", 0.0, "", "", "", 0);
        }

        if (item != nullptr) {
            stringstream ss(line);
            item->ReadFile(ss);
            addClothes(item);
            Clothes::updateHighestID(item->getID()); 
        }
    }

    filein.close();
}
void ClothesManager::writeClothesToFile(const string& filename) {
    ofstream fileout(filename);
    if (!fileout.is_open()) {
        cerr << "Khong the mo file!" << endl;
        return;
    }
    Node<Clothes*>* current = list.getHead();
    while (current != nullptr) {
        current->data->WriteFile(fileout);
        current = current->next;
    }
    fileout.close();
}
void ClothesManager::addClothesManually() {
    char type;
    cout << "Nhap loai quan ao (M: Male, F: Female, C: Children): ";
    cin >> type;
    cin.ignore(); 

    Clothes* item = nullptr;

    if (type == 'M') {
        item = new Male("", "", 0.0, "", "", "", 0);
    } else if (type == 'F') {
        item = new Female("", "", 0.0, "", "", "", 0);
    } else if (type == 'C') {
        item = new Children("", "", 0.0, "", "", "", 0);
    } else {
        cout << "Loai quan ao khong hop le!" << endl;
        return;
    }

    if (item != nullptr) {
        item->ReadInput();
        addClothes(item);
    }
}


void ClothesManager::Sort_ByID() {
    list.Sort(); 
}
void ClothesManager::removeClothesByID(const string& id) {
    if (list.removeById(id)) {
        cout << "Element with id " << id << " was removed successfully." << endl;
        updateAllIDsFromID(id);
        Clothes::decrementHighestID(id[0]);
    } else {
        cout << "Element with id " << id << " was not found." << endl;
    }
}
void ClothesManager::updateAllIDsFromID(const string& deletedID) {
    char prefix = deletedID[0];  
    int deletedNumber = stoi(deletedID.substr(1));  

    Node<Clothes*>* current = list.getHead();
    while (current != nullptr) {
        string currentID = current->data->getID();
        
        if (currentID[0] == prefix) {
            int currentNumber = stoi(currentID.substr(1));
    
            if (currentNumber > deletedNumber) {
                string newID = prefix + to_string(currentNumber - 1);
                current->data->setID(newID);  
            }
        }

        current = current->next;  
    }
}
void ClothesManager::EditClothesByID(const string& id) {
    Clothes* found = list.findByID(id);
    if(found != nullptr) {
    char continueEdit;
    do {
        string newName;
        double newPrice;
        string newBranch;
        LinkedList<Variant*> newVariants;
        cout << "Nhap ten moi: ";
        cin.ignore();
        getline(cin, newName);
        cout << "Nhap gia moi: ";
        cin >> newPrice;
        cin.ignore();
        cout << "Nhap ten thuong hieu: ";
        getline(cin, newBranch);
        found->clearVariants();
        char addMore;
        do {
            string size, color;
            int quantity;
            cout << "Nhap size: ";
            getline(cin, size);
            cout << "Nhap mau: ";
            getline(cin, color);
            cout << "Nhap so luong: ";
            cin >> quantity;
            cin.ignore();
            newVariants.push_back(new Variant(size, color, quantity));
            cout << "<!> Ban co muon them bien the khac cho san pham nay khong? (y/n): ";
            cin >> addMore;
            cin.ignore();
        } while(addMore == 'y' || addMore == 'Y');
        found->Edit(newName, newPrice, newBranch, newVariants);
        cout << "<!> Ban co muon sua tiep khong? (y/n): ";
        cin >> continueEdit;
        cin.ignore();
    } while(continueEdit == 'y' || continueEdit == 'Y');
    } else {
        cout << "<!> Khong tim thay san pham co ID " << id << endl;

    }
}
void ClothesManager::PrintClothesByID(const string& id) const {
    system("cls"); 

    Node<Clothes*>* current = list.getHead();
    bool found = false;  

    // Tiêu đề shop
    cout << "\n+===================================================SHOP QUAN AO GAU GAU====================================================\n";
    cout << "                                                  *** SAN PHAM DAC BIET ***                                                   \n";

    while (current != nullptr) {
        if (current->data->getID() == id) {
            cout << "+===========================================================================================================================\n";

            cout << "| <!> ID QUAN AO: " << current->data->getID() << endl;
            cout << "| <!> TEN QUAN AO: "<< current->data->getName() << endl;
            cout << "| <!> DEN TU THUONG HIEU: " << current->data->getBranch() << endl;
            cout << "| <!> GIA: " << current->data->getPrice() << " VND" << endl;
            cout << "+---------------------------------------------------------------------------------------------------------------------------\n";

            stringstream ss;
            Node<Variant*>* variant = current->data->getVariants().getHead();
            bool hasValidVariant = false;

            cout << "<!> SIZE, MAU SAC, SO LUONG:\n";

            while (variant != nullptr) {
                if (!variant->data->getSize().empty() &&
                    !variant->data->getColor().empty() &&
                    variant->data->getQuantity() > 0) {

                    ss << "   - {" << variant->data->getSize()
                       << ", " << variant->data->getColor()
                       << ", SL: " << variant->data->getQuantity() << "}\n";
                    hasValidVariant = true;
                }
                variant = variant->next;
            }

            if (hasValidVariant) {
                cout << ss.str();
            } else {
                cout << "   <!> KHONG CO SAN PHAM HOP LE HOAC DA HET HANG\n";
            }

            cout << "+===========================================================================================================================\n";

            found = true;  
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "\n[!] KHONG TIM THAY SAN PHAM VOI ID: " << id << endl;
    }

    system("pause");  
}
void ClothesManager::SearchBySubstring(const string& sub, const string& brand, const string& color, const string& size, const string& type) const {
    system("cls"); 
    Node<Clothes*>* current = list.getHead();
    
    bool found = false;

    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;
    cout << "| ID       | Ten san pham              | Thuong hieu       | Gia (VND)     | Size, Mau, So luong                                                   |" << endl;
    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;

    while (current != nullptr) {
        bool isTypeValid = (type == "All") || 
                           (type == "Male" && dynamic_cast<Male*>(current->data)) ||
                           (type == "Female" && dynamic_cast<Female*>(current->data)) ||
                           (type == "Children" && dynamic_cast<Children*>(current->data));

        bool check = true; // Đổi tên biến từ matches thành check

        // Kiểm tra thương hiệu
        if (!brand.empty() && current->data->getBranch() != brand) {
            check = false;
        }

        // Kiểm tra màu sắc
        if (!color.empty() && !checkColor(current->data, color)) {
            check = false;
        }

        // Kiểm tra kích thước
        if (!size.empty() && !checkSize(current->data, size)) {
            check = false;
        }

        // Kiểm tra tất cả các điều kiện
        if (isTypeValid && current->data->getName().find(sub) != string::npos && check) {
            // In thông tin sản phẩm
            cout << "| " << left << setw(8) << current->data->getID() << " | "
                 << setw(25) << current->data->getName() << " | "
                 << setw(17) << current->data->getBranch() << " | "
                 << setw(13) << current->data->getPrice() << " | ";

            stringstream ss;
            Node<Variant*>* variant = current->data->getVariants().getHead();
            bool hasValidVariant = false;

            while (variant != nullptr) {
                if (!variant->data->getSize().empty() &&
                    !variant->data->getColor().empty() &&
                    variant->data->getQuantity() > 0) {

                    ss << "{" << variant->data->getSize()
                       << ", " << variant->data->getColor()
                       << ", " << variant->data->getQuantity() << "} ";
                    hasValidVariant = true;
                }
                variant = variant->next;
            }

            if (hasValidVariant) {
                cout << left << setw(69) << ss.str() << " |" << endl;
            } else {
                cout << left << setw(69) << "<!> HET HANG CHO SAN PHAM NAY" << " |" << endl;
            }
            found = true; 
        }
        current = current->next;
    }

    if (!found) {
        cout << "|                                                      KHONG TIM THAY SAN PHAM NAO!                                                            |" << endl;
    }

    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;
    system("pause"); 
}

bool ClothesManager::checkColor(Clothes* cloth, const string& color) const {
    Node<Variant*>* variant = cloth->getVariants().getHead();
    while (variant != nullptr) {
        if (variant->data->getColor() == color) {
            return true; // Tìm thấy màu sắc
        }
        variant = variant->next;
    }
    return false; // Không tìm thấy màu sắc
}

bool ClothesManager::checkSize(Clothes* cloth, const string& size) const {
    Node<Variant*>* variant = cloth->getVariants().getHead();
    while (variant != nullptr) {
        if (variant->data->getSize() == size) {
            return true; // Tìm thấy kích thước
        }
        variant = variant->next;
    }
    return false; // Không tìm thấy kích thước
}


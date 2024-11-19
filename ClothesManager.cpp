#include "ClothesManager.h"
#include "Male.h"
#include "Female.h"
#include "Children.h" 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

void ClothesManager::addClothes(Clothes* clothes) {
    list.push_back(clothes);
}

void ClothesManager::printAllClothes() const {
    printByType("4");
}

void ClothesManager::printByType(const string& type) const {
    system("cls"); 

    string title;
    string selectedType;
     int typeInt = atoi(type.c_str()); 
    switch (typeInt) {
        case 2:
            title = "SAN PHAM CHO NU";
            selectedType = "Female";
            break;
        case 1:
            title = "SAN PHAM CHO NAM";
            selectedType = "Male";
            break;
        case 3:
            title = "SAN PHAM CHO TRE EM";
            selectedType = "Children";
            break;
        case 4:
            title = "TAT CA SAN PHAM";
            selectedType = "All";
            break;
        default:
            title = "LOAI SAN PHAM KHONG HOP LE";
            selectedType = "Invalid";
            break;
    }
    cout << endl;
    cout << "==============================================================SHOP QUAN AO GAU GAU ================================================================\n";
    cout << "                                                           --------------------------                                                              \n";
    cout << "                                                           " <<"     " << title << "                                                              \n";
    cout << "                                                           --------------------------                                                              \n";

    Node<Clothes*>* current = list.getHead();

    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;
    cout << "| ID       | Ten san pham              | Thuong hieu       | Gia (VND)     | Size, Mau, So luong                                                   |" << endl;
    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;

    bool hasItems = false; 

    while (current != nullptr) {
         if (selectedType == "All" || 
            (selectedType == "Female" && dynamic_cast<Female*>(current->data)) ||
            (selectedType == "Male" && dynamic_cast<Male*>(current->data)) ||
            (selectedType == "Children" && dynamic_cast<Children*>(current->data))) {
            
            cout << "| " << left << setw(8) << current->data->getID() << " | "
                 << setw(25) << current->data->getName() << " | "
                 << setw(17) << current->data->getBranch() << " | "
                 << setw(13) << fixed << setprecision(0) << formatMoney(current->data->getPrice()) << " | ";

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

    system("pause"); 
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
        if(line.empty()) continue;
        if (line[0] == 'M') {
            item = new Male("", "", 0.0, "", "", "", 0);
        } else if (line[0] == 'F') {
            item = new Female("", "", 0.0, "", "", "", 0);
        } else if (line[0] == 'C') {
            item = new Children("", "", 0.0, "", "", "", 0);
        } else {
            continue;
        }

        if (item != nullptr) {
            stringstream ss(line);
            item->ReadFile(ss);
            addClothes(item);
            Clothes::updateHighestID(item->getID()); 
            item = nullptr;
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
bool ClothesManager::addClothesManually() {
    char type;
    cout << "<*> Nhap loai quan ao (M: Male, F: Female, C: Children): ";
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
        cout << "<!> Loai quan ao khong hop le!" << endl;
        return false;
    }

    if (item != nullptr) {
    if (item->ReadInput()) {
        addClothes(item);
        cout << "<!> Da them quan ao thanh cong." << endl;
        system("pause");
        return true;
    } else {
        delete item;
        system("pause");
    }
}
        return false;
}


void ClothesManager::Sort_ByID() {
    list.Sort(); 
}
bool ClothesManager::removeClothesByID(const string& id) {
    if (list.removeById(id)) {
        updateAllIDsFromID(id);
        Clothes::decrementHighestID(id[0]);
        return true;
    } else {
        return false;
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
bool ClothesManager::EditClothesByID(const string& id) {
    Clothes* found = list.findByID(id);
    if (found != nullptr) {
        cout << "[!] CO THE NHAP 0 BAT KI DE HUY QUA TRINH SUA." << endl;
        cout << "[!] CO THE BO TRONG NHUNG PHAN KHONG CAN CHINH SUA." << endl;
        cout << "--------------------------------------------------------------------------------" << endl;

        int check = 0;
        string newName;
        double newPrice;
        string newBranch;
        LinkedList<Variant*> newVariants;
        Node<Variant*>* current = found->getVariants().getHead();
        while (current != nullptr) {
            Variant* newVariant = new Variant(current->data->getSize(), current->data->getColor(), current->data->getQuantity());
            newVariants.push_back(newVariant);
            current = current->next;
        }

        // Nhập tên quần áo
        while (true) {
            cout << "<!> Nhap ten quan ao (nhap 0 de huy): ";
            getline(cin, newName);
            newName = nameStr(newName);
            if (newName == "0") {
                cout << endl << "<!> QUA TRINH SUA DA BI HUY!" << endl;
                return false;
            }
            if (!newName.empty()) break;
            else {
                newName = found->getName();
                break;
            }
        }

        while (true) {
            string priceStr;
            cout << "<!> Nhap gia: ";
            getline(cin, priceStr);
            if(priceStr == ""){
                priceStr = doubleToString(found->getPrice());
            }
            if (priceStr == "0") {
                cout << endl << "<!> QUA TRINH SUA DA BI HUY!" << endl;
                return false;
            }
            if (isCharacter(priceStr)) {
                cout << "<!> Gia phai la so. Vui long nhap lai." << endl;
                continue;
            }
            newPrice = stoi(priceStr);
            if (newPrice <= 0) {
                cout << "<!> Gia phai la so duong. Vui long nhap lai." << endl;
                continue;
            } else {
                break;
            }
        }
        while (true) {
            cout << "<!> Nhap ten thuong hieu: ";
            getline(cin, newBranch);
            if (newBranch == "0") {
                cout << endl << "<!> QUA TRINH SUA DA BI HUY!" << endl;
                return false;
            }
            newBranch = nameStr(newBranch);
            if (!newBranch.empty()) break;
            else {
                newBranch = found->getBranch();
                break;
            }
        }
        bool check2 = false;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "[!] BO TRONG PHAN NAY NEU BAN KHONG MUON CHINH SUA MAU SAC, SIZE VA SO LUONG: ";
        string select;
        getline(cin, select);
        if (select == "") {
            found->clearVariants();
            check = 1;
        }
        if (check != 1) {
            char addMore;
            set<string> validSizes = {"XS", "S", "M", "L", "XL", "XXL", "XXXL"};
            set<string> validColors = {"Red", "Blue", "Green", "Yellow", "Black", "White", "Purple", "Brown", "Pink", "Beige", "Gray", "Orange"};
            do {
                string size, color;
                int quantity;

                while (true) {
                    cout << "<!> Nhap size (XS, S, M, L, XL, XXL, XXXL): ";
                    getline(cin, size);
                    size = toUpper(size);
                    if (size == "0") {
                        cout << endl << "<!> QUA TRINH SUA DA BI HUY!" << endl;
                        return false;
                    }
                    if (validSizes.find(size) != validSizes.end()) break;
                    cout << "<!> Size khong hop le. Vui long nhap lai." << endl;
                }
                while (true) {
                    cout << "<!> Nhap mau (Red, Blue, Green, Yellow, Black, White, Purple, Brown, Pink, Beige, Gray, Orange): ";
                    getline(cin, color);
                    color = nameStr(color);
                    if (color == "0") {
                        cout << endl << "<!> QUA TRINH SUA DA BI HUY!" << endl;
                        return false;
                    }
                    if (validColors.find(color) != validColors.end()) break;
                    cout << "<!> Mau khong hop le. Vui long nhap lai." << endl;
                }
                while (true) {
                    string quantity2;
                    cout << "<!> Nhap so luong: ";
                    getline(cin, quantity2);
                    if (quantity2 == "0") {
                        cout << endl << "<!> QUA TRINH SUA DA BI HUY!" << endl;
                        return false;
                    }
                    if (isCharacter(quantity2)) {
                        cout << "<!> So luong phai la so. Vui long nhap lai." << endl;
                        continue;
                    }
                    quantity = stoi(quantity2);
                    if (quantity <= 0) {
                        cout << "<!> So luong phai la so duong. Vui long nhap lai." << endl;
                        continue;
                    } else {
                        break;
                    }
                }
                if(check2 == false){
                found->clearVariants();
                newVariants.clear();
                check2 = true;
                }
                newVariants.push_back(new Variant(size, color, quantity));
                cout << "<!> Ban co muon them mau sac, size, so luong khac cho san pham nay khong? (y/n): ";
                cin >> addMore;
                cin.ignore();
            } while (addMore == 'y' || addMore == 'Y');
        }
        found->Edit(newName, newPrice, newBranch, newVariants);
        return true;
    } else {
        cout << "<!> Khong tim thay san pham co ID " << id << endl;
        return false;
    }
}

void ClothesManager::PrintClothesByID(const string& id) const {
    system("cls"); 

    Node<Clothes*>* current = list.getHead();
    bool found = false;  

    cout << "\n+===================================================SHOP QUAN AO GAU GAU====================================================\n";
    cout << "                                                  *** SAN PHAM DAC BIET ***                                                   \n";

    while (current != nullptr) {
        if (current->data->getID() == id) {
            cout << "+===========================================================================================================================\n";
            cout << "| <!> ID QUAN AO: " << current->data->getID() << endl;
            cout << "| <!> TEN QUAN AO: "<< current->data->getName() << endl;
            cout << "| <!> DEN TU THUONG HIEU: " << current->data->getBranch() << endl;
            cout << "| <!> GIA: " << fixed << setprecision(0) << formatMoney(current->data->getPrice())<< " VND" << endl;
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
    string title;
    string selectedType;
    int typeInt = atoi(type.c_str()); 
    switch (typeInt) {
        case 2:
            title = "SAN PHAM CHO NU";
            selectedType = "Female";
            break;
        case 1:
            title = "SAN PHAM CHO NAM";
            selectedType = "Male";
            break;
        case 3:
            title = "SAN PHAM CHO TRE EM";
            selectedType = "Children";
            break;
        case 4:
            title = "TAT CA SAN PHAM";
            selectedType = "All";
            break;
        default:
            title = "LOAI SAN PHAM KHONG HOP LE";
            selectedType = "Invalid";
            break;
    }

    cout << "\n==============================================================SHOP QUAN AO GAU GAU ================================================================\n";
    cout << "                                                           --------------------------                                                              \n";
    cout << "                                                           " <<"     " << title << "                                                              \n";
    cout << "                                                           --------------------------                                                              \n";

    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;
    cout << "| ID       | Ten san pham              | Thuong hieu       | Gia (VND)     | Size, Mau, So luong                                                   |" << endl;
    cout << "+----------+---------------------------+-------------------+---------------+-----------------------------------------------------------------------+" << endl;

    while (current != nullptr) {
        bool isTypeValid = (selectedType == "All" || 
                            (selectedType == "Female" && dynamic_cast<Female*>(current->data)) ||
                            (selectedType == "Male" && dynamic_cast<Male*>(current->data)) ||
                            (selectedType == "Children" && dynamic_cast<Children*>(current->data)));

        bool check = true; 

        if (!brand.empty() && current->data->getBranch() != brand) {
            check = false;
        }
        if (!color.empty() && !checkColor(current->data, color)) {
            check = false;
        }
        if (!size.empty() && !checkSize(current->data, size)) {
            check = false;
        }
        if (isTypeValid && current->data->getName().find(sub) != string::npos && check) {
            cout << "| " << left << setw(8) << current->data->getID() << " | "
                 << setw(25) << current->data->getName() << " | "
                 << setw(17) << current->data->getBranch() << " | "
                 << setw(13) << formatMoney(current->data->getPrice()) << " | ";

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
            found = true; 
        }
        current = current->next;
    }

    if (!found) {
        cout << "|                                                      KHONG TIM THAY SAN PHAM NAO!                                                               |" << endl;
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
double ClothesManager::getPriceByID(const string& itemID) const {
    Node<Clothes*>* current = list.getHead();
    while (current) {
        if (current->data->getID() == itemID) {
            return current->data->getPrice();
        }
        current = current->next;
    }
    return -1; 
}



#ifndef CapNhatOrder_H
#define CapNhatOrder_H

#include <iostream>
#include <string>

using namespace std;

// Cập nhật các Option: Size, % Đường, % Đá, Topping
void capNhatOrder() {
    string size, topping, ghiChu;
    int duong, da;
    cout << "--- CẬP NHẬT ORDER ---" << endl;
    cout << "Chọn Size (S/M/L): "; getline(cin, size);
    cout << "% Đường: "; cin >> duong;
    cout << "% Đá: "; cin >> da; cin.ignore();
    cout << "Topping: "; getline(cin, topping);
    cout << "Ghi chú: "; getline(cin, ghiChu);

    cout << "--> Đã cập nhật xong tùy chọn Order." << endl;
}

#endif

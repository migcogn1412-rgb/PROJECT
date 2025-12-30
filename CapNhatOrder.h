#ifndef CAPNHATORDER_H
#define CAPNHATORDER_H

#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <sstream>

using namespace std;

const int MAX_ORDER = 200;

struct Order {
    string maHD, ban, doUong, size, duong, da, topping, doAnNhe, ghiChu;
};

// Đọc một dòng thành struct Order
Order docDongOrder(string line) {
    istringstream ss(line);
    Order o;
    getline(ss, o.maHD, '|'); getline(ss, o.ban, '|');
    getline(ss, o.doUong, '|'); getline(ss, o.size, '|');
    getline(ss, o.duong, '|'); getline(ss, o.da, '|');
    getline(ss, o.topping, '|'); getline(ss, o.doAnNhe, '|');
    getline(ss, o.ghiChu);
    return o;
}

// Ghi đè file
void saveFileOrder(string tenFile, Order ds[], int sl) {
    ofstream f(tenFile);
    for (int i = 0; i < sl; i++) {
        f << format("{}|{}|{}|{}|{}|{}|{}|{}|{}\n", 
            ds[i].maHD, ds[i].ban, ds[i].doUong, ds[i].size, 
            ds[i].duong, ds[i].da, ds[i].topping, ds[i].doAnNhe, ds[i].ghiChu);
    }
}

// Ghi nối tiếp (Append)
void appendOrder(string tenFile, Order o) {
    ofstream f(tenFile, ios::app);
    f << format("{}|{}|{}|{}|{}|{}|{}|{}|{}\n", 
        o.maHD, o.ban, o.doUong, o.size, o.duong, o.da, o.topping, o.doAnNhe, o.ghiChu);
}

// Cập nhật và xử lý thanh toán (Đẩy file)
void capNhatOrder() {
    Order ds[MAX_ORDER];
    int sl = 0;
    string fChua = "OrderChuaThanhToan.txt", fDa = "OrderDaThanhToan.txt";

    ifstream fIn(fChua);
    string line;
    while (getline(fIn, line) && sl < MAX_ORDER) {
        if (line.length() > 5) ds[sl++] = docDongOrder(line);
    }
    fIn.close();

    cout << "\nNhap Ma HD: "; string ma; getline(cin, ma);
    bool found = false;
    for(int i=0; i<sl; i++) {
        if(ds[i].maHD == ma) {
            cout << format(" -> Mon: {} | Ghi chu: {}\n", ds[i].doUong, ds[i].ghiChu);
            found = true;
        }
    }

    if (!found) { cout << "Khong thay!\n"; return; }

    cout << "Xac nhan Thanh toan toan bo (y/n)? ";
    string choice; getline(cin, choice);
    if (choice == "y" || choice == "Y") {
        Order dsConLai[MAX_ORDER];
        int slMoi = 0;
        for (int i = 0; i < sl; i++) {
            if (ds[i].maHD == ma) appendOrder(fDa, ds[i]);
            else dsConLai[slMoi++] = ds[i];
        }
        saveFileOrder(fChua, dsConLai, slMoi);
        cout << "--> Da thanh toan & Luu lich su!\n";
    }
}

#endif

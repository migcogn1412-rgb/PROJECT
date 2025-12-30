#ifndef MENU_H
#define MENU_H

#include "CauTruc.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>

// --- HÀM 1: LOAD DỮ LIỆU TỪ FILE TXT ---

vector<MonUong> loadMenuDoUong() {
    vector<MonUong> list;
    ifstream f("DoUong.txt");
    string line, segment;
    if(f.is_open()) {
        while(getline(f, line)) {
            if(line.length() < 3) continue;
            MonUong d;
            stringstream ss(line);
            // Format file main tạo ra: Tên|Giá|Loại|Mã
            getline(ss, d.ten, '|');
            getline(ss, segment, '|'); d.giaGoc = stoi(segment);
            getline(ss, d.loai, '|');
            getline(ss, d.ma);
            if(d.ma != "") list.push_back(d);
        }
        f.close();
    }
    return list;
}

vector<MonAn> loadMenuDoAn() {
    vector<MonAn> list;
    ifstream f("DoAn.txt");
    string line, segment;
    if(f.is_open()) {
        while(getline(f, line)) {
            if(line.length() < 3) continue;
            MonAn d;
            stringstream ss(line);
            getline(ss, d.ten, '|');
            getline(ss, segment, '|'); d.giaGoc = stoi(segment);
            getline(ss, d.loai, '|');
            getline(ss, d.ma);
            if(d.ma != "") list.push_back(d);
        }
        f.close();
    }
    return list;
}

vector<MonTopping> loadMenuTopping() {
    vector<MonTopping> list;
    ifstream f("Topping.txt");
    string line, segment;
    if(f.is_open()) {
        while(getline(f, line)) {
            if(line.length() < 3) continue;
            MonTopping t;
            stringstream ss(line);
            getline(ss, t.ten, '|');
            getline(ss, segment, '|'); t.giaGoc = stoi(segment);
            getline(ss, t.ma);
            if(t.ma != "") list.push_back(t);
        }
        f.close();
    }
    return list;
}

vector<ConfigSize> loadCauHinhSize() {
    vector<ConfigSize> list;
    ifstream f("CauHinhOrder.txt");
    string line, segment;
    if(f.is_open()) {
        while(getline(f, line)) {
            if(line.length() < 2) continue;
            ConfigSize c;
            stringstream ss(line);
            // Format: Size|Giá
            getline(ss, c.size, '|');
            getline(ss, segment); c.giaCongThem = stoi(segment);
            list.push_back(c);
        }
        f.close();
    }
    return list;
}

// --- HÀM 2: TÌM KIẾM ---

MonUong timMonUong(string ma, const vector<MonUong>& list) {
    for(const auto& item : list) {
        if(item.ma == ma) return item;
    }
    return {"", "", "", 0};
}

MonAn timMonAn(string ma, const vector<MonAn>& list) {
    for(const auto& item : list) {
        if(item.ma == ma) return item;
    }
    return {"", "", "", 0};
}

MonTopping timTopping(string ma, const vector<MonTopping>& list) {
    for(const auto& item : list) {
        if(item.ma == ma) return item;
    }
    return {"", "", 0};
}

ConfigSize timSize(string tenSize, const vector<ConfigSize>& list) {
    for(const auto& item : list) {
        if(item.size == tenSize) return item;
    }
    return {"", 0};
}

// --- HÀM 3: HIỂN THỊ MENU ĐỂ CHỌN ---

void hienThi_MenuUong(const vector<MonUong>& list) {
    cout << "\n--- MENU DO UONG ---\n";
    cout << left << setw(10) << "MA" << setw(30) << "TEN" << "GIA\n";
    cout << string(50, '-') << endl;
    for(const auto& i : list) 
        cout << left << setw(10) << i.ma << setw(30) << i.ten << i.giaGoc << "\n";
}

void hienThi_MenuAn(const vector<MonAn>& list) {
    cout << "\n--- MENU DO AN ---\n";
    cout << left << setw(10) << "MA" << setw(30) << "TEN" << "GIA\n";
    cout << string(50, '-') << endl;
    for(const auto& i : list) 
        cout << left << setw(10) << i.ma << setw(30) << i.ten << i.giaGoc << "\n";
}

void hienThi_Topping(const vector<MonTopping>& list) {
    cout << "\n... TOPPING ...\n";
    for(const auto& t : list) 
        cout << "[" << t.ma << "] " << t.ten << "(+" << t.giaGoc << ")  ";
    cout << endl;
}

void hienThi_Size(const vector<ConfigSize>& list) {
    cout << "   -> Chon Size: ";
    for(const auto& s : list) 
        cout << s.size << "(+" << s.giaCongThem << ")  ";
    cout << endl;
}

#endif

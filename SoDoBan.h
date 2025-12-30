#ifndef SODOBAN_H
#define SODOBAN_H

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define SIZE 5

struct QuanCafe {
    int ban[SIZE][SIZE];
};

static QuanCafe qc;

// Doc file SoDoBan.txt
void docSoDoBan() {
    ifstream file("SoDoBan.txt");
    int soBan, trangThai;
    char dau;

    while (file >> soBan >> dau >> trangThai) {
        int index = soBan - 1;
        qc.ban[index / SIZE][index % SIZE] = trangThai;
    }
    file.close();
}

// Hien thi so do ban
void hienThiSoDo() {
    cout << "\nSƠ ĐỒ BÀN (0: Trống | 1: Có khách)\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int soBan = i * SIZE + j + 1;
            cout << setw(2) << soBan << "[" << qc.ban[i][j] << "] ";
        }
        cout << endl;
    }
    cout << endl;
}

// Khach chon ban
void chonBan() {
    int soBan;
    while (true) {
        cout << "Nhập số bàn (1-25), 0 để thoát: ";
        cin >> soBan;

        if (soBan == 0) {
            cout << "Thoát chương trình.\n";
            return;
        }

        if (soBan < 1 || soBan > 25) {
            cout << "Bàn không tồn tại!\n";
            continue;
        }

        int index = soBan - 1;
        if (qc.ban[index / SIZE][index % SIZE] == 0) {
            cout << "Bàn " << soBan << " đang trống\n";
            return;
        } else {
            cout << "Bàn " << soBan << " đã có khách\n";
            cout << "Hãy chọn bàn khác hoặc nhập 0 để thoát.\n";
        }
    }
}

// Ham gop toan bo chuong trinh
void soDoBan() {
    docSoDoBan();
    hienThiSoDo();
    chonBan();
}

#endif 

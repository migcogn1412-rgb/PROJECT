#ifndef TAOORDER_H
#define TAOORDER_H

#include "Menu.h"
#include <string>

// --- HÀM CẬP NHẬT TRẠNG THÁI BÀN ---
// Tự đọc/ghi file SoDoBan.txt độc lập để không phụ thuộc file Main
void setTrangThaiBan(int ban, int trangThai) {
    vector<string> lines;
    ifstream fIn("SoDoBan.txt");
    string line;
    // Đọc file cũ
    if(fIn.is_open()) {
        while(getline(fIn, line)) lines.push_back(line);
        fIn.close();
    }
    
    // Ghi file mới
    ofstream fOut("SoDoBan.txt");
    bool timThay = false;
    for(string s : lines) {
        if(s.length() < 3) continue;
        stringstream ss(s);
        string sBan; getline(ss, sBan, '|');
        
        if(stoi(sBan) == ban) {
            fOut << ban << "|0|" << trangThai << endl;
            timThay = true;
        } else {
            fOut << s << endl;
        }
    }
    // Nếu chưa có file sơ đồ bàn thì tạo mới dòng này (dự phòng)
    if(!timThay) fOut << ban << "|0|" << trangThai << endl;
    
    fOut.close();
}

// --- HIỂN THỊ SƠ ĐỒ BÀN ĐỂ CHỌN ---
void xemSoDoBan() {
    cout << "\n--- TRANG THAI BAN ---\n";
    ifstream f("SoDoBan.txt");
    string line;
    if(!f.is_open()) { cout << "(Chua co du lieu ban)\n"; return; }
    
    while(getline(f, line)) {
        if(line.length() < 3) continue;
        stringstream ss(line);
        string sBan, sDau, sTrangThai;
        getline(ss, sBan, '|');
        getline(ss, sDau, '|'); 
        getline(ss, sTrangThai);
        
        int iBan = stoi(sBan);
        int iTT = stoi(sTrangThai);
        cout << "[Ban " << iBan << ": " << (iTT == 1 ? "CO KHACH" : "Trong") << "]  ";
        if(iBan % 5 == 0) cout << endl;
    }
    cout << endl;
    f.close();
}

// --- LƯU PHIẾU ORDER ---
void luuPhieuOrder(int soBan, const vector<ChiTietOrder>& ds, string ghiChu) {
    string tenFile = "Order_Ban_" + to_string(soBan) + ".txt";
    ofstream f(tenFile); // Ghi đè (tạo phiếu mới)
    
    // Dòng 1: Ghi chú
    f << "GHI_CHU|" << ghiChu << endl;
    
    // Các dòng sau: Món ăn
    for(auto m : ds) {
        // Format: Loai|Ma|Ten|Size|GiaSize|Topping|GiaTopping|SoLuong|ThanhTien
        f << m.loai << "|" << m.maMon << "|" << m.tenMon << "|"
          << m.size << "|" << m.giaSize << "|"
          << m.dsTopping << "|" << m.giaTopping << "|"
          << m.soLuong << "|" << m.thanhTien << endl;
    }
    f.close();
    cout << "\n--> [THANH CONG] Da chuyen Order xuong bep (File " << tenFile << ")\n";
}

// --- LOGIC CHÍNH: TẠO ORDER MỚI ---
// Tên hàm này bạn hãy gọi trong main.cpp
void taoOrderMoi() {
    vector<MonUong> listUong = loadMenuDoUong();
    vector<MonAn> listAn = loadMenuDoAn();
    vector<MonTopping> listTopping = loadMenuTopping();
    vector<ConfigSize> listSize = loadCauHinhSize();

    xemSoDoBan();
    int soBan;
    cout << ">> Chon so ban khach ngoi (0 thoat): ";
    cin >> soBan;
    if (soBan == 0) return;

    vector<ChiTietOrder> gioHang;
    string maChon;
    
    // --- GỌI ĐỒ UỐNG ---
    while(true) {
        hienThi_MenuUong(listUong);
        cout << "Nhap MA Do Uong (0 sang Do An): "; cin >> maChon;
        if(maChon == "0") break;

        MonUong m = timMonUong(maChon, listUong);
        if(m.ma == "") { cout << "Ma khong dung!\n"; continue; }

        ChiTietOrder ct;
        ct.maMon = m.ma; ct.tenMon = m.ten; ct.loai = "DO_UONG";
        
        hienThi_Size(listSize);
        cout << "   -> Size: "; cin >> ct.size;
        ConfigSize sz = timSize(ct.size, listSize);
        ct.giaSize = (sz.size != "") ? sz.giaCongThem : 0;

        hienThi_Topping(listTopping);
        ct.dsTopping = ""; ct.giaTopping = 0;
        cin.ignore();
        while(true) {
            cout << "   -> Ma Topping (Enter dung): ";
            string maTP; getline(cin, maTP);
            if(maTP == "") break;
            MonTopping tp = timTopping(maTP, listTopping);
            if(tp.ma != "") {
                ct.dsTopping += tp.ten + ", ";
                ct.giaTopping += tp.giaGoc;
            }
        }

        cout << "   -> So luong: "; cin >> ct.soLuong;
        ct.thanhTien = (m.giaGoc + ct.giaSize + ct.giaTopping) * ct.soLuong;
        gioHang.push_back(ct);
        cout << "   => Da them: " << ct.tenMon << endl;
    }

    // --- GỌI ĐỒ ĂN ---
    while(true) {
        hienThi_MenuAn(listAn);
        cout << "Nhap MA Do An (0 ket thuc): "; cin >> maChon;
        if(maChon == "0") break;

        MonAn m = timMonAn(maChon, listAn);
        if(m.ma == "") { cout << "Ma khong dung!\n"; continue; }

        ChiTietOrder ct;
        ct.maMon = m.ma; ct.tenMon = m.ten; ct.loai = "DO_AN";
        ct.size = ""; ct.giaSize = 0; ct.dsTopping = ""; ct.giaTopping = 0;

        cout << "   -> So luong: "; cin >> ct.soLuong;
        ct.thanhTien = m.giaGoc * ct.soLuong;
        gioHang.push_back(ct);
        cout << "   => Da them: " << ct.tenMon << endl;
    }

    // --- KẾT THÚC ---
    cin.ignore();
    string ghiChu;
    cout << ">> Ghi chu: "; getline(cin, ghiChu);

    if(!gioHang.empty()) {
        setTrangThaiBan(soBan, 1); // Đánh dấu bàn có khách
        luuPhieuOrder(soBan, gioHang, ghiChu); // Lưu file
    } else {
        cout << "(!) Huy order (Rong)\n";
    }
}

#endif

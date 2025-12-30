#ifndef TAOORDER_H
#define TAOORDER_H

#include "SoDoBan.h"
#include "Menu.h"
#include <ctime>
#include <iomanip>

// --- CÁC HÀM TIỆN ÍCH CŨ ---
void capNhatTrangThaiFile(int banCanUpdate, int trangThaiMoi) {
    vector<pair<int, int>> data;
    ifstream fIn("SoDoBan.txt");
    int b, t;
    char sep;
    while(fIn >> b >> sep >> t) {
        if (b == banCanUpdate) t = trangThaiMoi;
        data.push_back({b, t});
    }
    fIn.close();

    ofstream fOut("SoDoBan.txt");
    for(auto p : data) {
        fOut << p.first << "|" << p.second << endl;
    }
    fOut.close();
}

string layNgayGio() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year) 
           + " " + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);
}

void ghiHoaDonVaoFile(const HoaDon& hd) {
    ofstream f("LichSuHoaDon.txt", ios::app);
    f << "HEAD|" << hd.maHD << "|" << hd.ngay << "|" << hd.soBan << "|" << hd.tongTien << "|" << hd.ghiChu << endl;
    for(auto m : hd.dsMon) {
        f << "ITEM|" << hd.maHD << "|" << m.maMon << "|" << m.tenMon << "|" << m.soLuong << "|" << m.thanhTien << endl;
    }
    f.close();
}

// --- HÀM MỚI: IN HÓA ĐƠN RA MÀN HÌNH ---
void inHoaDonChiTiet(const HoaDon& hd) {
    cout << "\n";
    cout << "******************************************\n";
    cout << "          HOA DON THANH TOAN              \n";
    cout << "******************************************\n";
    cout << " Ma HD:   " << hd.maHD << endl;
    cout << " Ngay:    " << hd.ngay << endl;
    cout << " Ban So:  " << hd.soBan << endl;
    cout << "------------------------------------------\n";
    cout << left << setw(20) << "TEN MON" << setw(5) << "SL" << setw(15) << "THANH TIEN" << endl;
    cout << "------------------------------------------\n";

    for (const auto& item : hd.dsMon) {
        // In tên món
        cout << left << setw(20) << item.tenMon 
             << setw(5) << item.soLuong 
             << right << setw(10) << item.thanhTien << " d" << endl;
        
        // In chi tiết nhỏ bên dưới nếu là đồ uống
        if (item.loai == "DO_UONG") {
            cout << left << setw(25) << "  Size: " + item.size << endl;
            if (!item.dsTopping.empty()) {
                cout << left << setw(25) << "  Topping: " + item.dsTopping << endl;
            }
        }
        cout << "- - - - - - - - - - - - - - - - - - - - - \n";
    }

    cout << "------------------------------------------\n";
    cout << right << setw(25) << "TONG CONG: " << setw(10) << hd.tongTien << " d\n";
    cout << right << setw(25) << "KHACH DUA: " << setw(10) << hd.tienKhachDua << " d\n";
    cout << right << setw(25) << "TIEN THOI: " << setw(10) << hd.tienThoi << " d\n";
    cout << "------------------------------------------\n";
    cout << " Ghi chu: " << hd.ghiChu << endl;
    cout << "******************************************\n";
    cout << "      CAM ON QUY KHACH & HEN GAP LAI      \n";
    cout << "******************************************\n";
}

// --- LOGIC CHÍNH ---
void taoOrderMoi() {
    docSoDoBan(); 
    vector<Mon> menuDoUong = loadMenu("DoUong.txt");
    vector<Mon> menuDoAn = loadMenu("DoAn.txt");
    vector<Topping> menuTopping = loadTopping("Topping.txt");

    hienThiSoDo(); 
    int soBan;
    cout << ">> Chon so ban de order (0 thoat): ";
    cin >> soBan;
    if (soBan == 0) return;
    if (soBan < 1 || soBan > 25) { cout << "Ban khong ton tai!\n"; return; }
    
    int idx = soBan - 1;
    if (qc.ban[idx/SIZE][idx%SIZE] == 1) {
        cout << "(!) Ban nay dang co khach.\n";
        return;
    }

    HoaDon hd;
    hd.soBan = soBan;
    hd.ngay = layNgayGio();
    hd.maHD = "HD" + to_string(time(0)); 
    hd.tongTien = 0;

    string maChon;

    // --- LOOP ĐỒ UỐNG ---
    while(true) {
        hienThiMenu(menuDoUong, "MENU DO UONG");
        cout << "Nhap MA mon (VD: CP01), nhap '0' sang Do An: ";
        cin >> maChon;
        if(maChon == "0") break;

        Mon m = timMonTheoMa(maChon, menuDoUong);
        if(m.maMon == "") { cout << "Ma khong hop le!\n"; continue; }

        ChiTietOrder ct;
        ct.maMon = m.maMon; ct.tenMon = m.tenMon; ct.loai = "DO_UONG";
        ct.giaTopping = 0;
        
        cout << "   -> Size (S: +0d, M: +3000d, L: +6000d): "; cin >> ct.size;
        cout << "   -> % Duong: "; cin >> ct.duong;
        cout << "   -> % Da: "; cin >> ct.da;
        
        ct.dsTopping = "";
        string maTP;
        hienThiTopping(menuTopping);
        cin.ignore();
        while(true) {
            cout << "   -> Nhap Ma Topping (Enter de dung): ";
            getline(cin, maTP);
            if(maTP == "") break;
            
            Topping tp = timToppingTheoMa(maTP, menuTopping);
            if(tp.maTopping != "") {
                ct.dsTopping += tp.tenTopping + ", ";
                ct.giaTopping += tp.gia;
            }
        }

        cout << "   -> So luong: "; cin >> ct.soLuong;
        long giaSize = (ct.size == "L" || ct.size == "l") ? 6000 : (ct.size == "M" || ct.size == "m" ? 3000 : 0);
        ct.thanhTien = (m.gia + giaSize + ct.giaTopping) * ct.soLuong;
        
        hd.dsMon.push_back(ct);
        hd.tongTien += ct.thanhTien;
        cout << "   => DA THEM (Tam tinh: " << hd.tongTien << "d)\n";
    }

    // --- LOOP ĐỒ ĂN ---
    while(true) {
        hienThiMenu(menuDoAn, "MENU DO AN VAT");
        cout << "Nhap MA mon (VD: BN01), nhap '0' de ket thuc: ";
        cin >> maChon;
        if(maChon == "0") break;

        Mon m = timMonTheoMa(maChon, menuDoAn);
        if(m.maMon == "") { cout << "Ma khong hop le!\n"; continue; }

        ChiTietOrder ct;
        ct.maMon = m.maMon; ct.tenMon = m.tenMon; ct.loai = "DO_AN";
        ct.size = ""; ct.duong = 0; ct.da = 0; ct.dsTopping = ""; ct.giaTopping = 0;

        cout << "   -> So luong: "; cin >> ct.soLuong;
        ct.thanhTien = m.gia * ct.soLuong;

        hd.dsMon.push_back(ct);
        hd.tongTien += ct.thanhTien;
        cout << "   => DA THEM (Tam tinh: " << hd.tongTien << "d)\n";
    }

    cin.ignore();
    cout << ">> Ghi chu: ";
    getline(cin, hd.ghiChu);

    // --- THANH TOÁN (MỚI) ---
    cout << "\n========== THANH TOAN ==========\n";
    cout << " TONG TIEN CAN TRA: " << hd.tongTien << " VND\n";
    
    if (hd.tongTien > 0) {
        do {
            cout << " Nhap so tien khach dua: ";
            cin >> hd.tienKhachDua;
            if (hd.tienKhachDua < hd.tongTien) {
                cout << " (!) Tien khach dua thieu " << (hd.tongTien - hd.tienKhachDua) << "d. Vui long nhap lai.\n";
            }
        } while (hd.tienKhachDua < hd.tongTien);

        hd.tienThoi = hd.tienKhachDua - hd.tongTien;
        cout << " -> Tien thoi lai: " << hd.tienThoi << " VND\n";
    } else {
        hd.tienKhachDua = 0;
        hd.tienThoi = 0;
    }

    // Lưu và In hóa đơn
    capNhatTrangThaiFile(soBan, 1);
    docSoDoBan();
    ghiHoaDonVaoFile(hd);
    
    // Gọi hàm in hóa đơn vừa viết
    inHoaDonChiTiet(hd);
}

#endif

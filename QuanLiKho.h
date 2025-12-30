#ifndef QUANLYKHO_H
#define QUANLYKHO_H

#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <sstream>

using namespace std;

const int MAX_KHO = 500;   // Tổng số nguyên liệu tối đa trong kho
const int MAX_NHAP = 50;   // Số loại món tối đa trong một hóa đơn nhập

// --- CẤU TRÚC DỮ LIỆU ---
struct HangHoa {
    string ten;
    int soLuong = 0;
    int gia = 0;
};

// Cấu trúc đầy đủ để đọc file nguyên liệu (Tên|Loại|Giá|SốLượng)
struct NguyenLieu {
    string ten, loai;
    int gia = 0;
    int soLuong = 0;
};

// --- CÁC HÀM TIỆN ÍCH ---

// 1. QUẢN LÝ NHÀ CUNG CẤP
void themNhaCungCap() {
    string tenNCC;
    cout << "\n[+] NHẬP TÊN NHÀ CUNG CẤP MỚI: ";
    getline(cin, tenNCC);
    
    ofstream f("NhaCungCap.txt", ios::app);
    if (f.is_open()) {
        f << tenNCC << endl;
        f.close();
        cout << "--> [THÀNH CÔNG] Đã lưu Nhà cung cấp.\n";
    }
}

// 2. TỰ ĐỘNG CẬP NHẬT KHO

void capNhatKhoTuDong(HangHoa dsMoi[], int n) {
    NguyenLieu kho[MAX_KHO];
    int soLuongTrongKho = 0;

    // Đọc kho hiện tại vào mảng tĩnh
    ifstream fIn("NguyenLieuTrongKho.txt");
    string line;
    while (getline(fIn, line) && soLuongTrongKho < MAX_KHO) {
        if (line.length() < 3) continue;
        istringstream ss(line);
        getline(ss, kho[soLuongTrongKho].ten, '|');
        getline(ss, kho[soLuongTrongKho].loai, '|');
        string sGia, sSL;
        getline(ss, sGia, '|'); kho[soLuongTrongKho].gia = stoi(sGia);
        getline(ss, sSL);      kho[soLuongTrongKho].soLuong = stoi(sSL);
        soLuongTrongKho++;
    }
    fIn.close();

    // Duyệt danh sách hàng vừa nhập để cộng dồn
    for (int i = 0; i < n; i++) {
        bool timThay = false;
        for (int j = 0; j < soLuongTrongKho; j++) {
            if (kho[j].ten == dsMoi[i].ten) {
                kho[j].soLuong += dsMoi[i].soLuong; 
                kho[j].gia = dsMoi[i].gia;         
                timThay = true;
                break;
            }
        }
        // Nếu món mới hoàn toàn, thêm vào cuối mảng kho
        if (!timThay && soLuongTrongKho < MAX_KHO) {
            kho[soLuongTrongKho].ten = dsMoi[i].ten;
            kho[soLuongTrongKho].loai = "ChuaPhanLoai";
            kho[soLuongTrongKho].gia = dsMoi[i].gia;
            kho[soLuongTrongKho].soLuong = dsMoi[i].soLuong;
            soLuongTrongKho++;
        }
    }

    // Ghi đè lại file kho sau khi xử lý xong trên mảng
    ofstream fOut("NguyenLieuTrongKho.txt", ios::out);
    for (int i = 0; i < soLuongTrongKho; i++) {
        fOut << format("{}|{}|{}|{}\n", kho[i].ten, kho[i].loai, kho[i].gia, kho[i].soLuong);
    }
    fOut.close();
}

// 3. TẠO HÓA ĐƠN NHẬP
void taoHoaDonNhap() {
    int n;
    cout << "\n[?] Hôm nay bạn nhập bao nhiêu loại sản phẩm: ";
    string sN; getline(cin, sN);
    try { n = stoi(sN); } catch (...) { n = 0; }

    if (n <= 0 || n > MAX_NHAP) {
        cout << "--> Số lượng không hợp lệ!\n";
        return;
    }

    HangHoa danhSachHang[MAX_NHAP]; // Mảng tĩnh thay cho vector
    long long tongTienHD = 0;

    for (int i = 0; i < n; i++) {
        cout << format("--- Sản phẩm {}/{} ---\n", i + 1, n);
        cout << " + Tên: ";      getline(cin, danhSachHang[i].ten);
        cout << " + SL nhập: ";  string sL; getline(cin, sL); danhSachHang[i].soLuong = stoi(sL);
        cout << " + Giá nhập: "; string sG; getline(cin, sG); danhSachHang[i].gia = stoi(sG);
        
        tongTienHD += (long long)danhSachHang[i].soLuong * danhSachHang[i].gia;
    }

    string maDon, ngay;
    cout << "\n[*] Nhập Mã đơn nhập: "; getline(cin, maDon);
    cout << "[*] Nhập Ngày nhập: ";    getline(cin, ngay);

    // Ghi lịch sử hóa đơn (Ghi nối tiếp - append)
    ofstream fLog("LichSuHoaDon.txt", ios::app);
    if (fLog.is_open()) {
        fLog << format("MA: {} | NGAY: {} | TONG: {} VND\n", maDon, ngay, tongTienHD);
        for (int i = 0; i < n; i++) {
            fLog << format("   + {} (SL: {})\n", danhSachHang[i].ten, danhSachHang[i].soLuong);
        }
        fLog.close();
    }

    // Cập nhật số lượng vào kho gốc
    capNhatKhoTuDong(danhSachHang, n);
    cout << "\n--> [THÀNH CÔNG] Đã cập nhật kho và lưu lịch sử!\n";
}

// 4. TRA CỨU LỊCH SỬ NHẬP
void traCuuLichSuNhap() {
    string tuKhoa;
    cout << "\nNhập Mã đơn hoặc Ngày cần tìm: ";
    getline(cin, tuKhoa);

    ifstream f("LichSuHoaDon.txt");
    string line;
    bool found = false;
    cout << "\n--- KẾT QUẢ TRA CỨU ---" << endl;
    while (getline(f, line)) {
        // Tìm kiếm chuỗi đơn giản trong từng dòng của file
        if (line.find(tuKhoa) != string::npos) {
            cout << line << endl;
            // Nếu dòng đó là dòng tiêu đề (có chữ MA:), ta in thêm các dòng sản phẩm bên dưới
            found = true;
        }
    }
    if (!found) cout << "Không tìm thấy dữ liệu trùng khớp.\n";
    f.close();
}

#endif

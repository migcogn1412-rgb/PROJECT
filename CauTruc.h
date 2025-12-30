#ifndef CAUTRUC_H
#define CAUTRUC_H

#include <string>
#include <vector>
using namespace std;

// === CÁC STRUCT GỐC (GIỐNG FILE MAIN) ===

struct DoUong {
    string ten, loai, ma;
    int giaGoc = 0;
};

struct DoAn {
    string ten, loai, ma;
    int giaGoc = 0;
};

struct Topping {
    string ten, ma;
    int giaGoc = 0;
};

struct CauHinh {
    string size;
    int giaCongThem = 0;
};

// === CÁC STRUCT MỚI (DÙNG CHO ORDER & HÓA ĐƠN) ===

// Chi tiết 1 món khách đã chọn
struct ChiTietOrder {
    string maMon;
    string tenMon;
    string loai;      // "DO_UONG" hoặc "DO_AN"
    
    // Option (chỉ dùng cho đồ uống)
    string size;      // S, M, L
    long giaSize;     // Giá cộng thêm của size
    string dsTopping; // Tên các topping nối chuỗi
    long giaTopping;  // Tổng tiền topping
    
    // Chung
    int soLuong;
    long thanhTien;   // (GiaGoc + GiaSize + GiaTopping) * SoLuong
};

// Hóa đơn tổng
struct HoaDon {
    string maHD;
    string ngay;
    int soBan;
    vector<ChiTietOrder> dsMon; // Danh sách món đã gọi
    string ghiChu;
    long tongTien;
    long tienKhachDua;
    long tienThoi;
};

// Quản lý bàn
struct Ban {
    int soBan;
    int trangThai; // 0: Trống, 1: Có khách
};

#endif

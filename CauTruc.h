#ifndef CAUTRUC_H
#define CAUTRUC_H

#include <string>
#include <vector>
using namespace std;

// --- ĐỔI TÊN STRUCT ĐỂ KHÔNG ĐỤNG HÀNG VỚI MAIN.CPP ---

struct MonUong { // Trong main là DoUong
    string ten, loai, ma;
    int giaGoc; 
};

struct MonAn { // Trong main là DoAn
    string ten, loai, ma;
    int giaGoc;
};

struct MonTopping { // Trong main là Topping
    string ten, ma;
    int giaGoc;
};

struct ConfigSize { // Trong main là CauHinh
    string size;
    int giaCongThem;
};

// --- CÁC STRUCT RIÊNG CỦA CHỨC NĂNG ORDER ---

// Chi tiết 1 món khách gọi
struct ChiTietOrder {
    string maMon;
    string tenMon;
    string loai;      // "DO_UONG" hoặc "DO_AN"
    
    // Option (chỉ đồ uống)
    string size;      
    int giaSize;      
    string dsTopping; // Chuỗi tên topping
    int giaTopping;   
    
    int soLuong;
    long thanhTien;   // Tổng tiền món này
};

#endif

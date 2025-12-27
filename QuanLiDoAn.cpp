#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <sstream>

using std::cout, std::cin, std::endl;
using std::string, std::ofstream, std::ifstream, std::ios;
using std::format, std::istringstream, std::getline, std::stoi;

const int TOI_DA = 100;

//KHAI BÁO STRUCT
struct DoAn {
	string ten, loai, ma;
	int giaGoc = 0;
};

//HÀM TIỆN ÍCH
void veDuong(int doDai) {
	cout << string(doDai, '-') << endl;
}

void veTieuDe(string tieuDe) {
	cout << endl;
	veDuong(60);
	cout << format("|-{:^56}-|", tieuDe) << endl;
	veDuong(60);
	cout << endl;
}

void dungManHinh() {
	cout << endl;
	veDuong(60);
	cout << "--> Nhấn [ENTER] để quay lại...";
	string rac;
	getline(cin, rac);
}

//ĐỌC THÔNG TIN ĐỒ ĂN TỪ 1 DÒNG
DoAn docDoAn(string thongTin) {
	istringstream phanTach(thongTin);
	DoAn d;
	d.ten = ""; d.giaGoc = 0; d.loai = ""; d.ma = "";
	string boNhoDem;

	getline(phanTach, d.ten, '|');
	getline(phanTach, boNhoDem, '|');
	d.giaGoc = stoi(boNhoDem);
	getline(phanTach, d.loai, '|');
	getline(phanTach, d.ma);

	return d;
}

//ĐỌC THÔNG TIN TỪ FILE ĐỒ ĂN
bool docFileTuNguonDoAn(string tenFile, DoAn danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	thuTu = 0;
	string boNhoDem;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() < 5) continue;
		danhSach[thuTu] = docDoAn(boNhoDem);
		if (danhSach[thuTu].ma != "") thuTu++;
	}
	docFile.close();
	return true;
}

//GHI THÔNG TIN VÀO FILE ĐỒ ĂN
bool ghiFileVaoNguonDoAn(string tenFile, DoAn danhSach[], int& thuTu) {
	ofstream ghiFile(tenFile, ios::out);
	if (!ghiFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	for (int i = 0; i < thuTu; i++) {
		ghiFile << danhSach[i].ten << "|"
      			<< danhSach[i].giaGoc << "|"
      			<< danhSach[i].loai << "|"
      			<< danhSach[i].ma << endl;
	}
	ghiFile.close();
	return true;
}

//XÓA 1 DÒNG ĐỒ ĂN
void xoaDongDoAn(DoAn danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

//CẬP NHẬT THÔNG TIN ĐỒ ĂN
void capNhatDoAn(DoAn& mon) {
	string boNhoDem;
	cout << format("\n--- ĐANG SỬA MÓN: {} ---\n", mon.ten);
	cout << "(Bấm Enter nếu muốn giữ nguyên giá trị cũ)\n\n";

	cout << format("Mã mới (cũ: {}): ", mon.ma);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ma = boNhoDem;

	cout << format("Tên mới (cũ: {}): ", mon.ten);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.ten = boNhoDem;

	cout << format("Giá mới (cũ: {}): ", mon.giaGoc);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.giaGoc = stoi(boNhoDem);

	cout << format("Loại mới (cũ: {}): ", mon.loai);
	getline(cin, boNhoDem);
	if (boNhoDem != "") mon.loai = boNhoDem;
}

//THÊM ĐỒ ĂN
void themDoAn(string fileDoAn) {
	veTieuDe("THÊM ĐỒ ĂN MỚI");

	ofstream themDoAn(fileDoAn, ios::app);
	if (!themDoAn.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileDoAn << "'!" << endl;
		return;
	}

	DoAn moi;
	string boNhoDem;

	cout << format("{:<25}: ", "Nhập mã đồ ăn");
	getline(cin, boNhoDem);
	moi.ma = boNhoDem;

	cout << format("{:<25}: ", "Nhập tên món");
	getline(cin, boNhoDem);
	moi.ten = boNhoDem;

	cout << format("{:<25}: ", "Nhập giá gốc");
	getline(cin, boNhoDem);
	moi.giaGoc = stoi(boNhoDem);

	cout << format("{:<25}: ", "Nhập loại đồ ăn");
	getline(cin, boNhoDem);
	moi.loai = boNhoDem;

	veDuong(60);
	cout << " [*] XÁC NHẬN (Y/N): ";
	getline(cin, boNhoDem);

	if (boNhoDem == "Y" || boNhoDem == "y") {
		themDoAn << moi.ten << "|" << moi.giaGoc << "|" << moi.loai << "|" << moi.ma << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm đồ ăn vào hệ thống! *_*" << endl;
	}
	if (boNhoDem == "N" || boNhoDem == "n") {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm đồ ăn mới! *_*" << endl;
	}

	themDoAn.close();
}

//XÓA ĐỒ ĂN
void xoaDoAn(string fileDoAn) {
	veTieuDe("XÓA ĐỒ ĂN");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileTuNguonDoAn(fileDoAn, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* đồ ăn muốn xóa: ";
	string maXoa;
	getline(cin, maXoa);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maXoa) {
			timThay = true;
			cout << format("\nĐang xóa món: [{}] - {}\n", danhSach[i].ma, danhSach[i].ten);

			veDuong(60);
			string boNhoDem;
			cout << " [*] XÁC NHẬN (Y/N): ";
			getline(cin, boNhoDem);

			if (boNhoDem == "Y" || boNhoDem == "y") {
				xoaDongDoAn(danhSach, thuTu, i);
				cout << "--> [THÀNH CÔNG] Đã xóa đồ ăn! *_*" << endl;
				break;
			}
			if (boNhoDem == "N" || boNhoDem == "n") {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa đồ ăn! *_*" << endl;
				break;
			}
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ ăn: " << maXoa << endl;
	}

	ghiFileVaoNguonDoAn(fileDoAn, danhSach, thuTu);
}

//SỬA ĐỒ ẮN
void suaDoAn(string fileDoAn) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileTuNguonDoAn(fileDoAn, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* đồ ăn muốn sửa: ";
	string maSua;
	getline(cin, maSua);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma == maSua) {
			timThay = true;

			string boNhoDem;
			cout << " [*] XÁC NHẬN (Y/N): ";
			getline(cin, boNhoDem);

			if (boNhoDem == "Y" || boNhoDem == "y") {
				capNhatDoAn(danhSach[i]);
				cout << "\n--> [THÀNH CÔNG] Đã cập nhật thông tin! *_*" << endl;
				break;
			}
			if (boNhoDem == "N" || boNhoDem == "n") {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác cập nhật thông tin! *_*" << endl;
				break;
			}
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ ăn!" << endl;
	}

	ghiFileVaoNguonDoAn(fileDoAn, danhSach, thuTu);
}

//TÌM KIẾM ĐỒ ĂN
void timKiemDoAn(string fileDoAn) {
	veTieuDe("TÌM KIẾM ĐỒ ĂN");

	DoAn danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileTuNguonDoAn(fileDoAn, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* hoặc *TỪ KHÓA*: ";
	string doTimKiem;
	getline(cin, doTimKiem);

	cout << endl;
	veDuong(75);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ ĂN", "GIÁ", "LOẠI") << endl;
	veDuong(75);

	bool timThay = false;
	for (int i = 0; i < thuTu; i++) {
		if (danhSach[i].ma.find(doTimKiem) != string::npos || danhSach[i].ten.find(doTimKiem) != string::npos) {
			cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc, danhSach[i].loai) << endl;
			timThay = true;
		}
	}
	veDuong(75);
	if (!timThay) {
		cout << "\n--> Không tìm thấy kết quả nào phù hợp với: " << doTimKiem << endl;
	}
}

//HÀM QUẢN LÍ CHỨC NĂNG LIÊN QUAN ĐẾN ĐỒ ĂN
void quanLiDoAn() {
	while (true) {
		system("cls");
		veTieuDe("[II] QUẢN LÍ ĐỒ ĂN");
		cout << format("{:<60}", "[1] Thêm đồ ăn mới") << endl;
		cout << format("{:<60}", "[2] Xóa đồ ăn") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa thông tin") << endl;
		cout << format("{:<60}", "[4] Tìm kiếm đồ ăn") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) themDoAn("DoAn.txt");
		else if (luaChon == 2) xoaDoAn("DoAn.txt");
		else if (luaChon == 3) suaDoAn("DoAn.txt");
		else if (luaChon == 4) timKiemDoAn("DoAn.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

int main(){
    quanLiDoAn();
}

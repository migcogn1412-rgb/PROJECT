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
struct DoUong {
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

//ĐỌC THÔNG TIN ĐỒ UỐNG TỪ 1 DÒNG
DoUong docDoUong(string thongTin) {
	istringstream phanTach(thongTin);
	DoUong d;
	d.ten = ""; d.giaGoc = 0; d.loai = ""; d.ma = "";
	string boNhoDem;

	getline(phanTach, d.ten, '|');
	getline(phanTach, boNhoDem, '|');
	d.giaGoc = stoi(boNhoDem);
	getline(phanTach, d.loai, '|');
	getline(phanTach, d.ma);

	return d;
}

//ĐỌC THÔNG TIN TỪ FILE ĐỒ UỐNG
bool docFileTuNguonDoUong(string tenFile, DoUong danhSach[], int& thuTu) {
	ifstream docFile(tenFile, ios::in);
	if (!docFile.is_open()) {
		cout << "LỖI: Không thể mở file '" << tenFile << "'!" << endl;
		return false;
	}
	string boNhoDem;
	while (getline(docFile, boNhoDem)) {
		if (boNhoDem.length() < 5) continue;
		danhSach[thuTu] = docDoUong(boNhoDem);
		if (danhSach[thuTu].ma != "") thuTu++;
	}
	docFile.close();
	return true;
}

//GHI THÔNG TIN VÀO FILE ĐỒ UỐNG
bool ghiFileVaoNguonDoUong(string tenFile, DoUong danhSach[], int& thuTu) {
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

//XÓA 1 DÒNG THÔNG TIN ĐỒ UỐNG
void xoaDongDoUong(DoUong danhSach[], int& thuTu, int i) {
	for (int j = i; j < thuTu - 1; j++) {
		danhSach[j] = danhSach[j + 1];
	}
	thuTu--;
}

//CẬP NHẬT THÔNG TIN ĐỒ UỐNG
void capNhatDoUong(DoUong& mon) {
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

//IN MENU ĐỒ UỐNG
void inMenuDoUong(string tieuDeMenu, DoUong danhSach[], int& thuTu) {
	cout << tieuDeMenu << endl;
	veDuong(73);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ UỐNG", "GIÁ", "LOẠI") << endl;
	veDuong(73);

	for (int i = 0; i < thuTu; i++) {
		cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", danhSach[i].ma, danhSach[i].ten, danhSach[i].giaGoc, danhSach[i].loai) << endl;
	}

	veDuong(73);
	cout << endl;
}

//THÊM THÔNG TIN ĐỒ UỐNG
void themDoUong(string fileDoUong) {
	veTieuDe("THÊM ĐỒ UỐNG MỚI");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonDoUong(fileDoUong, danhSach, thuTu)) {
		inMenuDoUong("* MENU ĐỒ UỐNG HIỆN TẠI *", danhSach, thuTu);
	}

	ofstream themDoUong(fileDoUong, ios::app);
	if (!themDoUong.is_open()) {
		cout << "LỖI: Không thể mở file '" << fileDoUong << "'!" << endl;
		return;
	}

	DoUong moi;
	string boNhoDem;

	cout << format("{:<25}: ", "Nhập mã đồ uống");
	getline(cin, boNhoDem);
	moi.ma = boNhoDem;

	cout << format("{:<25}: ", "Nhập tên đồ uống");
	getline(cin, boNhoDem);
	moi.ten = boNhoDem;

	cout << format("{:<25}: ", "Nhập giá gốc");
	getline(cin, boNhoDem);
	moi.giaGoc = stoi(boNhoDem);

	cout << format("{:<25}: ", "Nhập loại đồ uống");
	getline(cin, boNhoDem);
	moi.loai = boNhoDem;

	veDuong(60);
	cout << " [*] XÁC NHẬN (Y/N): ";
	getline(cin, boNhoDem);

	if (boNhoDem == "Y" || boNhoDem == "y") {
		themDoUong << moi.ten << "|" << moi.giaGoc << "|" << moi.loai << "|" << moi.ma << endl;
		cout << "\n--> [THÀNH CÔNG] Đã thêm đồ uống vào hệ thống! *_*\n" << endl;
	}
	if (boNhoDem == "N" || boNhoDem == "n") {
		cout << "\n--> [THẤT BẠI] Đã hủy thao tác thêm đồ uống mới! *_*" << endl;
	}

	themDoUong.close();
}

//XÓA ĐỒ UỐNG
void xoaDoUong(string fileDoUong) {
	veTieuDe("XÓA ĐỒ UỐNG");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonDoUong(fileDoUong, danhSach, thuTu)) {
		inMenuDoUong("* MENU ĐỒ UỐNG HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ uống muốn xóa: ";
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
				xoaDongDoUong(danhSach, thuTu, i);
				cout << "\n--> [THÀNH CÔNG] Đã xóa đồ uống! *_*" << endl;
				break;
			}
			if (boNhoDem == "N" || boNhoDem == "n") {
				cout << "\n--> [THẤT BẠI] Đã hủy thao tác xóa đồ uống! *_*" << endl;
				break;
			}
		}
	}

	if (!timThay) {
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ uống: " << maXoa << endl;
	}

	ghiFileVaoNguonDoUong(fileDoUong, danhSach, thuTu);
}

//SỬA ĐỒ UỐNG
void suaDoUong(string fileDoUong) {
	veTieuDe("CHỈNH SỬA THÔNG TIN");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (docFileTuNguonDoUong(fileDoUong, danhSach, thuTu)) {
		inMenuDoUong("* MENU ĐỒ UỐNG HIỆN TẠI *", danhSach, thuTu);
	}

	cout << "Nhập *MÃ* đồ uống muốn sửa: ";
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
				capNhatDoUong(danhSach[i]);
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
		cout << "\n--> [CẢNH BÁO] Không tìm thấy mã đồ uống!" << endl;
	}

	ghiFileVaoNguonDoUong(fileDoUong, danhSach, thuTu);
}

//TÌM KIẾM ĐỒ UỐNG
void timKiemDoUong(string fileDoUong) {
	veTieuDe("TÌM KIẾM ĐỒ UỐNG");

	DoUong danhSach[TOI_DA];
	int thuTu = 0;
	if (!docFileTuNguonDoUong(fileDoUong, danhSach, thuTu)) return;

	cout << "Nhập *MÃ* hoặc *TỪ KHÓA*: ";
	string doTimKiem;
	getline(cin, doTimKiem);

	cout << endl;
	veDuong(75);
	cout << format("| {:<10} | {:<30} | {:<10} | {:<10} |", "MÃ", "TÊN ĐỒ UỐNG", "GIÁ", "LOẠI") << endl;
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

//HÀM QUẢN LÍ CHỨC NĂNG LIÊN QUAN ĐẾN ĐỒ UỐNG
void quanLiDoUong() {
	while (true) {
		system("cls");
		veTieuDe("[I] QUẢN LÍ ĐỒ UỐNG");
		cout << format("{:<60}", "[1] Thêm đồ uống mới") << endl;
		cout << format("{:<60}", "[2] Xóa đồ uống") << endl;
		cout << format("{:<60}", "[3] Chỉnh sửa thông tin") << endl;
		cout << format("{:<60}", "[4] Tìm kiếm đồ uống") << endl;
		cout << format("{:<60}", "[0] Quay lại") << endl;
		veDuong(60);
		cout << " [*] CHỌN: ";

		string boNhoDem;
		getline(cin, boNhoDem);
		int luaChon = 0;
		if (boNhoDem != "") luaChon = stoi(boNhoDem);
		if (luaChon == 0) break;

		system("cls");
		if (luaChon == 1) themDoUong("DoUong.txt");
		else if (luaChon == 2) xoaDoUong("DoUong.txt");
		else if (luaChon == 3) suaDoUong("DoUong.txt");
		else if (luaChon == 4) timKiemDoUong("DoUong.txt");
		else cout << "\n--> Lựa chọn không hợp lệ!" << endl;

		dungManHinh();
	}
}

int main(){
    quanLiDoUong();
}

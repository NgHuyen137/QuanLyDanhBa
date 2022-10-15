#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#pragma warning(disable : 4996)

using namespace std;
struct NgaySinh {
	int ngay, thang, nam;
};
typedef NgaySinh NgayHeThong;

struct KhachHang {
	string name;
	string sdt;
	string diachi;
	NgaySinh ngsinh;
};

struct Node {
	KhachHang key;
	Node* left, * right;
};
typedef Node* Tree;

Node* createNode(KhachHang key) {
	Node* node = new Node;
	node->key = key;
	node->left = node->right = NULL;
	return node;
}


void insertNode(Tree& root, Node* node) {
	if (root == NULL)
		root = node;
	else if (node->key.sdt> root->key.sdt)
		insertNode(root->right, node);
	else if (node->key.sdt< root->key.sdt)
		insertNode(root->left, node);
	else return;
}

//int compare(string sdt1, string sdt2) {
//	if (sdt1.compare(sdt2) == 0) return -1; // sdt1=sdt2
//	if (sdt1.compare(sdt2) > 0) return 1; // sdt1>sdt2
//	else return 0; // sdt1<sdt2
//}

/*Cac ham xoa*/
/*Ham tim node nho nhat ke tu node root*/
Node* minNode(Node* root) {
	Node* minRoot = root; //con tro giu dia chi node nho nhat
	if (root->left == NULL)
		return minRoot;
	minNode(root->left);
}

void XoaKhachHang(Tree& root, string sdt) {
	if (root == NULL) return; //Khong tim thay sdt can xoa hoac cay rong
	else if (root->key.sdt>sdt)
		XoaKhachHang(root->left, sdt);
	else if (root->key.sdt< sdt)
		XoaKhachHang(root->right, sdt);
	else {
		if (root->left == NULL && root->right == NULL)
			root = NULL;
		else if (root->left == NULL) {
			Node* t = root;
			root = root->right;
			delete t;
		}
		else if (root->right == NULL) {
			Node* t = root;
			root = root->left;
			delete t;
		}
		else {
			Node* minRoot = minNode(root->right);
			Node* copy = createNode(minRoot->key);
			XoaKhachHang(root, minRoot->key.sdt);
			copy->left = root->left;
			copy->right = root->right;
			delete root;
			root = copy;
		}
	}
}

/*Cac ham doc file*/
/*Ham doc ngay sinh*/
void DocNgsinh(ifstream& filein, NgaySinh& ngsinh) {
	filein >> ngsinh.ngay;
	filein.ignore(1);
	filein >> ngsinh.thang;
	filein.ignore(1);
	filein >> ngsinh.nam;
	filein.ignore(1);
}
/*Ham doc thong tin mot khach hang*/
void DocKhachHang(ifstream& filein, KhachHang& key) {
	getline(filein, key.name, ',');
	DocNgsinh(filein, key.ngsinh);
	getline(filein, key.sdt, ',');
	getline(filein, key.diachi);
}
/*Ham doc danh ba*/
void DocDanhBa(ifstream& filein, Tree& root) {
	KhachHang key;
	while (filein.peek() != EOF) {
		DocKhachHang(filein, key);
		Node* node = createNode(key);
		insertNode(root, node);
	}
}

/*Cac ham nhap, xuat khach hang*/
void nhapKhachHang(KhachHang& key) {
	cout << "\nNhap ho ten: ";
	cin.ignore();
	getline(cin, key.name);

	do {
		cout << "Nhap so dien thoai: ";
		getline(cin, key.sdt);
	} while (key.sdt.length() != 10);

	cout << "Nhap dia chi: ";
	getline(cin, key.diachi);
	cout << "Nhap ngay sinh: ";
	cin >> key.ngsinh.ngay >> key.ngsinh.thang >> key.ngsinh.nam;
}

//void xuatKhachHang(KhachHang key) {
//	cout << "Ho ten: " << key.name << endl;
//	cout << "So dien thoai: " << key.sdt << endl;
//	cout << "Dia chi: " << key.diachi << endl;
//	cout << "Ngay sinh: " << key.ngsinh.ngay << "/" << key.ngsinh.thang << "/" << key.ngsinh.nam << endl;
//}

ostream& operator<<(ostream& COUT, KhachHang key) {
	COUT << "Ho ten: " << key.name << endl;
	COUT << "So dien thoai: " << key.sdt << endl;
	COUT << "Dia chi: " << key.diachi << endl;
	COUT << "Ngay sinh: " << key.ngsinh.ngay << "/" << key.ngsinh.thang << "/" << key.ngsinh.nam << endl;
	return COUT;
}

void XuatDS(Tree root) {
	if (root != NULL) {
		cout << root->key << endl;
		XuatDS(root->left);
		XuatDS(root->right);
	}
}
void XuatKHCungNgaySinh(Tree root, NgayHeThong ngay_ht) {
	if (root != NULL) {
		if (root->key.ngsinh.ngay == ngay_ht.ngay) {
			cout << root->key << endl;
		}
		XuatKHCungNgaySinh(root->left, ngay_ht);
		XuatKHCungNgaySinh(root->right, ngay_ht);
	}
}

//void createBTree(Tree& root, int size) {
//	KhachHang key;
//	for (int i = 0; i < size; i++) {
//		cout << "\nKhach hang thu " << i << endl;
//		nhapKhachHang(key);
//		Node* node = createNode(key);
//		insertNode(root, node);
//	}
//}

void printNode(string sdt, int h) {
	for (int i = 0; i < h; i++)
		cout << "          ";
	cout << sdt << endl << endl;
}

void printBTree(Tree root, int h) {
	if (root == NULL) {
		for (int i = 0; i < h; i++)
			cout << "          ";
		cout << "*" << endl << endl;
		return;
	}
	printBTree(root->right, h + 1);
	printNode(root->key.sdt, h);
	printBTree(root->left, h + 1);
}

Node* TimKiemSdt(Tree root, string sdt) {
	if (root) {
		if (root->key.sdt == sdt) return root; // tim thay sdt
		if (sdt < root->key.sdt)
			return TimKiemSdt(root->left, sdt);
		return TimKiemSdt(root->right, sdt);
	}
	return NULL; // Khong tim thay
}
void menu() {
	Tree root = NULL;
	int ch;
	bool quit = false;
	do {
		system("cls");
		cout << "===========================================================" << endl;
		cout << "*CAY NHI PHAN QUAN LY KHACH HANG*" << endl;
		cout << "1. Doc danh sach khach hang tu file" << endl;
		cout << "2. Xuat danh sach khach hang" << endl;
		cout << "3. Xuat cay BST luu so dien thoai khach hang" << endl;
		cout << "4. Them khach hang vao danh sach" << endl;
		cout << "5. Xoa khach hang voi so dien thoai bat ky" << endl;
		cout << "6. Tim khach hang co cung ngay sinh nhat trong ngay hien tai" << endl;
		cout << "============================================================" << endl;
		cout << "\nNhap lua chon: ";
		cin >> ch;
		switch (ch) {
		case 1:
		{
			ifstream filein;
			char fileName[30];
			cout << "\nNhap ten file: "; cin >> fileName;
			filein.open(fileName, ios::in);
			if (!filein) {
				cout << "\nKhong mo duoc file !";
				system("pause");
			}
			else {
				DocDanhBa(filein, root);
				cout << "Doc file thanh cong ! (nhap 2 de kiem tra)" << endl;
				system("pause");
			}
		}
		break;
		case 2:
		{
			XuatDS(root);
			system("pause");
		}
		break;
		case 3:
		{
			printBTree(root, 0);
			system("pause");
		}
		break;
		case 4:
		{
			KhachHang key;
			cout << "\nNhap thong tin khach hang can them: ";
			nhapKhachHang(key);
			Node* node = createNode(key);
			insertNode(root, node);
			cout << "\nDa them khach hang vao danh sach. Nhan 2 de kiem tra !";
			system("pause");
		}
		break;
		case 5:
		{
			string sdt;
			do {
				cout << "\nNhap so dien thoai khach hang can xoa (10 chu so): ";
				cin >> sdt;
			} while (sdt.length() != 10);
			Node* temp = TimKiemSdt(root, sdt);
			if (temp == NULL) cout << "\nKhong tim thay so dien thoai trong danh sach !";
			else {
				XoaKhachHang(root, sdt);
				cout << "\nDa xoa thanh cong so dien thoai " << sdt;
			}
			system("pause");
		}
		break;
		case 6:
		{
			time_t now = time(0);
			tm* ltm = localtime(&now);
			NgayHeThong ngay_ht;
			ngay_ht.ngay = ltm->tm_mday;
			ngay_ht.thang = ltm->tm_mon;
			ngay_ht.nam = ltm->tm_year;
			XuatKHCungNgaySinh(root, ngay_ht);
			system("pause");
		}
		break;
		}
	} while (!quit);
}

int main() {
	menu();
}

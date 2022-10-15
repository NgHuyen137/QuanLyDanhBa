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
	else if (node->key.sdt > root->key.sdt)
		insertNode(root->right, node);
	else if (node->key.sdt < root->key.sdt)
		insertNode(root->left, node);
	else return;
}

/*Cac ham xoa*/
/*Ham tim node nho nhat cua cay con phai*/
void minNode(Node* rightChild, Node*& minnode) {//rightChild: cay con phai
	if (rightChild->left == NULL)
		minnode = rightChild;
	else
		minNode(rightChild->left, minnode);
}
/*Ham xoa 1 khach hang co sdt cho truoc*/
void XoaKhachHang(Tree& root, string sdt) {
	if (root == NULL) 
		cout << "Khong tim thay so dien thoai can xoa" << endl;
	else if (root->key.sdt > sdt)
		XoaKhachHang(root->left, sdt);
	else if (root->key.sdt < sdt)
		XoaKhachHang(root->right, sdt);
	else {
		if (root->left == NULL && root->right == NULL)
			root = NULL;
		else if (root->left == NULL) {
			Node* delnode = root;
			root = root->right;
			delete delnode;
		}
		else if (root->right == NULL) {
			Node* delnode = root;
			root = root->left;
			delete delnode;
		}
		else {
			Node* minnode = NULL;
			minNode(root->right, minnode);

			Node* copy = createNode(minnode->key);
			XoaKhachHang(root, minnode->key.sdt);
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
void XuatKHCungNgaySinh(Tree root, NgayHeThong ngay_ht, bool& flag) {
	if (root != NULL) {
		if (root->key.ngsinh.ngay == ngay_ht.ngay) {
			cout << root->key << endl;
		}
		XuatKHCungNgaySinh(root->left, ngay_ht, flag);
		XuatKHCungNgaySinh(root->right, ngay_ht, flag);
	}
}

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
			XoaKhachHang(root, sdt);
			system("pause");
		}
		break;
		case 6:
		{
			time_t now = time(0);
			tm* ltm = localtime(&now);
			NgayHeThong ngay_ht;
			bool flag = 0;
			ngay_ht.ngay = ltm->tm_mday;
			ngay_ht.thang = ltm->tm_mon;
			ngay_ht.nam = ltm->tm_year;
			XuatKHCungNgaySinh(root, ngay_ht, flag);
			if (flag == 0)
				cout << "Khong tim thay khach hang co ngay sinh hom nay" << endl;
			system("pause");
		}
		break;
		}
	} while (!quit);
}

int main() {
	menu();
}

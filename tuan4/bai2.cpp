#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct NgaySinh {
	int ngay, thang, nam;
};

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

int Compare(string sdt1, string sdt2) {
	if (sdt1.compare(sdt2) == 0) return -1;
	if (sdt1.compare(sdt2) > 0) return 1;
	return 0;
}

void insertNode(Tree& root, Node* node) {
	if (root == NULL)
		root = node;
	else if (Compare(node->key.sdt, root->key.sdt) == 1)
		insertNode(root->right, node);
	else if (Compare(node->key.sdt, root->key.sdt) == 0)
		insertNode(root->left, node);
	else return;
}

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
	else if (Compare(root->key.sdt, sdt) == 1) 
		XoaKhachHang(root->left, sdt);
	else if (Compare(root->key.sdt, sdt) == 0)
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
	cout << "Nhap ho ten: "; 
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

void xuatKhachHang(KhachHang key) {
	cout << "Ho ten: " << key.name << endl;
	cout << "So dien thoai: " << key.sdt << endl;
	cout << "Dia chi: " << key.diachi << endl;
	cout << "Ngay sinh: " << key.ngsinh.ngay << "/" << key.ngsinh.thang << "/" << key.ngsinh.nam << endl;
}

void createBTree(Tree& root, int size) {
	KhachHang key;
	for (int i = 0; i < size; i++) {
		cout << "\nKhach hang thu " << i << endl;
		nhapKhachHang(key);
		Node* node = createNode(key);
		insertNode(root, node);
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


int main() {
	Tree root = NULL;
	ifstream filein;
	filein.open("Danhba1.txt",ios::in);
	if (filein) {
		DocDanhBa(filein, root);
	}
	printBTree(root, 0);
	cout << endl << endl;
	XoaKhachHang(root, "0890232920");
	cout << "Sau khi xoa" << endl;
	printBTree(root, 0);
}
#include <iostream>
using namespace std;
/*Khai bao kieu du lieu Node*/
struct Node {
	int key;
	Node* left;
	Node* right;
};
typedef Node* link; 

/*Ham tao node*/
Node* createNode(int key) {
	Node* node = new Node;
	node->key = key;
	node->left = node->right = NULL;
	return node;
}

/*Ham them mot Node vao cay*/
//void insertNode(link& root, Node* node) {
//	Node* ptr = root; //Con tro giu dia chi node dang xet
//	if (root == NULL) { //Cay rong
//		root = node;
//	}
//	else {
//		while (ptr != NULL) {
//			if (node->key < ptr->key) //Xet cay con trai
//				ptr = ptr->left; 
//			else if (node->key > ptr->key) //Xet cay con phai
//				ptr = ptr->right; 
//			else return; //Trung khoa
//		}
//	}
//	ptr = node;
//}

void insertNode(link& root, Node* node) {
	if (root == NULL) //Cay rong
		root = node;
	else if (node->key < root->key) //Xet cay con trai
		insertNode(root->left, node);
	else if (node->key > root->key) //Xet cay con phai
		insertNode(root->right, node);
	else return; //Trung khoa
}

/*Ham tim chieu cao cay*/
int heightBTree(link root) {
	int height = 0;
	while (root != NULL) {
		height++;
		root = root->left;
	}
	return height;
}

/*Cac ham duyet cay*/
void Preorder(link root) {
	if (root != NULL) {
		cout << root->key << " ";
		Preorder(root->left);
		Preorder(root->right);
	}
}
void Inorder(link root) {
	if (root != NULL) {
		Inorder(root->left);
		cout << root->key << " ";
		Inorder(root->right);
	}
}
void Postorder(link root) {
	if (root != NULL) {
		Postorder(root->left);
		Postorder(root->right);
		cout << root->key << " ";
	}
}

/*Ham tinh tong cac node co gia tri lon hon x*/
//int sumNode(link root, int x) {
//	//Duyet cay theo Preorder
//	if (root != NULL) {
//
//	}
//}

/*Ham tim node co khoa x*/
/*Su dung de quy*/
int searchNode_Recursion(link root, int x) {
	if (root == NULL) return -1; //Khong tim thay node co khoa x
	else if (x == root->key) return x; //Tim thay tra ve x
	else if (x < root->key)
		searchNode_Recursion(root->left, x);
	else 
		searchNode_Recursion(root->right, x);
}

/*Khong su dung de quy*/
int searchNode(link root, int x) {

}


/*Ham tao cay*/
void createBTree(link& root, int size) { //size: so luong node 
	int key;
	for (int i = 0; i < size; i++) {
		cout << "Nhap khoa: "; cin >> key;
		Node* node = createNode(key);
		insertNode(root, node);
	}
}

/*Ham in khoa*/
void printNode(int key, int h) { //h: chieu cao cay
	for (int i = 0; i < h; i++)
		cout << "  ";
	cout << key << endl;
}

/*Ham in cay*/
void printBTree(link root, int h) {
	if (root == NULL) {
		for (int i = 0; i < h; i++)
			cout << "  ";
		cout << "*" << endl;
		return;
	}
	printBTree(root->left, h + 1);
	printNode(root->key, h);
	printBTree(root->right, h + 1);
}

int main() {
	int size;
	link root = NULL; //Tao cay rong
	
	cout << "Nhap so luong node: "; cin >> size;
	createBTree(root, size); //Tao cay 
	
	printBTree(root, 0); //In cay

	/*Duyet cay*/
	cout << "Duyet cay theo Preorder: ";
	Preorder(root); //Duyet cay Root->Left->Right
	cout << endl;

	cout << "Duyet cay theo Inorder: ";
	Inorder(root); //Duyet cay Left->Root->Right
	cout << endl;

	cout << "Duyet cay theo Postorder: ";
	Postorder(root); //Duyet cay Left->Right->Root
	cout << endl;

	/*Tim chieu cao cay*/
	int height = heightBTree(root);
	cout << "Chieu cao cay: " << height << endl;

	/*Tim node co khoa x*/
	int x, find;
	cout << "Nhap khoa can tim: "; cin >> x;
	find = searchNode_Recursion(root, x);
	if (find == -1)
		cout << "Khong tim thay khoa " << x << endl;
	else
		cout << "Tim thay khoa " << find << endl;



}
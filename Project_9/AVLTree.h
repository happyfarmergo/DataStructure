#include "AVLTreeNode.h"

class AVLTree {
private:
	AVLTreeNode *root;
private:
	int Max(int x, int y);
	int GetHeight(AVLTreeNode *r);                          //��ȡ����
	void showTitle();										//��ӡ����
	void InOrder(AVLTreeNode *r);							//�������
	AVLTreeNode *SingleLeftRotation(AVLTreeNode *A);		//������
	AVLTreeNode *SingleRightRotation(AVLTreeNode *A);		//������
	AVLTreeNode *DoubleLeftRightRotation(AVLTreeNode *A);	//����˫��
	AVLTreeNode *DoubleRightLeftRotation(AVLTreeNode *A);	//����˫��
public:
	AVLTree();
	~AVLTree();
	void Clear(AVLTreeNode *&r);                            //ɾ����rΪ��������
	void Search(int elem);                                  //�����в��ҽڵ�
	AVLTreeNode* Insert(AVLTreeNode *T, int elem);          //����TΪ�������в���ڵ�
	void ShowTree();                                        //��ʾ����
	void Init();
	void Run();
};

AVLTree::AVLTree() :
root(NULL) {
}

AVLTree::~AVLTree() {
	Clear(root);
}

inline int AVLTree::Max(int x, int y) {
	return x > y ? x : y;
}

inline int AVLTree::GetHeight(AVLTreeNode *r) {
	return r ? r->height : 0;
}

void AVLTree::showTitle() {
	cout << "**             ����������             **\n"
		<< "========================================\n"
		<< "**            1.��������������        **\n"
		<< "**            2.����Ԫ��              **\n"
		<< "**            3.��ѯԪ��              **\n"
		<< "**            4.�˳�����              **\n"
		<< "========================================"
		<< endl;
}

void AVLTree::Clear(AVLTreeNode *&r) {
	if (r) {
		Clear(r->leftChild);
		Clear(r->rightChild);
		delete r;
		r = NULL;
	}
}

AVLTreeNode *AVLTree::SingleLeftRotation(AVLTreeNode *A) {
	AVLTreeNode *B = A->leftChild;
	A->leftChild = B->rightChild;
	B->rightChild = A;
	A->height = Max(GetHeight(A->leftChild), GetHeight(A->rightChild)) + 1;
	B->height = Max(GetHeight(B->leftChild), A->height) + 1;
	return B;
}

AVLTreeNode *AVLTree::SingleRightRotation(AVLTreeNode *A) {
	AVLTreeNode *B = A->rightChild;
	A->rightChild = B->leftChild;
	B->leftChild = A;
	A->height = Max(GetHeight(A->leftChild), GetHeight(A->rightChild)) + 1;
	B->height = Max(GetHeight(B->rightChild), A->height) + 1;
	return B;
}

AVLTreeNode *AVLTree::DoubleLeftRightRotation(AVLTreeNode *A) {
	A->leftChild = SingleRightRotation(A->leftChild);
	return SingleLeftRotation(A);
}

AVLTreeNode *AVLTree::DoubleRightLeftRotation(AVLTreeNode *A) {
	A->rightChild = SingleLeftRotation(A->rightChild);
	return SingleRightRotation(A);
}

void AVLTree::InOrder(AVLTreeNode *r) {
	if (r) {
		InOrder(r->leftChild);
		cout << r->value << "->";
		InOrder(r->rightChild);
	}
}

void AVLTree::ShowTree() {
	cout << "Bsort_Tree is:" << endl;
	InOrder(root);
	cout << endl;
	/*PreOrder(root);
	cout << endl;*/
}

void AVLTree::Init() {
	int n;
	while (cin >> n, n != 0)
		root = Insert(root, n);
}

AVLTreeNode* AVLTree::Insert(AVLTreeNode *T, int elem) {
	if (!T) {                                                //����ΪNULL
		T = new AVLTreeNode(elem);
	} else if (elem < T->value) {                            //elemС������
		T->leftChild = Insert(T->leftChild, elem);           //���뵽������
		if (GetHeight(T->leftChild) - GetHeight(T->rightChild) == 2) { //��T��ʼ��ƽ��
			if (elem < T->leftChild->value)                 //elem��T����������������
				T = SingleLeftRotation(T);
			else                                            //elem��T����������������
				T = DoubleLeftRightRotation(T);
		}
	} else if (elem>T->value) {                             //elem��������
		T->rightChild = Insert(T->rightChild, elem);        //���뵽������
		if (GetHeight(T->rightChild) - GetHeight(T->leftChild) == 2) { //��T��ʼ��ƽ��
			if (elem > T->rightChild->value)                //elem��T����������������
				T = SingleRightRotation(T);
			else											//elem��T����������������
				T = DoubleRightLeftRotation(T);
		}
	} else {                                                //elem�Ѿ�������
		cout << "The input key(" << elem << ")is have in!" << endl;
		return T;
	}
	T->height = Max(GetHeight(T->leftChild), GetHeight(T->rightChild)) + 1;
	return T;
}

void AVLTree::Search(int elem) {
	AVLTreeNode *parent = root;
	while (parent&&elem != parent->value) {
		if (elem < parent->value)
			parent = parent->leftChild;
		else
			parent = parent->rightChild;
	}
	if (parent)cout << "search success!" << endl;
	else cout << "search failure!" << endl;
}

void AVLTree::Run() {
	showTitle();
	int n, elem;
	do {
		cout << "\nPlease select:";
		cin >> n;
		switch (n) {

			//��ʼ��
		case 1:
			Clear(root);
			cout << "Please input key to create Bsort_Tree:" << endl;
			Init();
			ShowTree();
			break;

			//����
		case 2:
			cout << "Please input key to be inserted:";
			cin >> elem;
			root = Insert(root, elem);
			ShowTree();
			break;

			//����
		case 3:
			cout << "Please input key to be searched:";
			cin >> elem;
			Search(elem);
			break;

			//�˳�
		case 4:
			break;

			//����Ƿ�
		default:
			cout << "Invalid input!" << endl;
			break;

		}
	} while (n != 4);
}

#include "AVLTreeNode.h"

class AVLTree {
private:
	AVLTreeNode *root;
private:
	int Max(int x, int y);
	int GetHeight(AVLTreeNode *r);                          //获取树高
	void showTitle();										//打印标题
	void InOrder(AVLTreeNode *r);							//中序遍历
	AVLTreeNode *SingleLeftRotation(AVLTreeNode *A);		//单左旋
	AVLTreeNode *SingleRightRotation(AVLTreeNode *A);		//单右旋
	AVLTreeNode *DoubleLeftRightRotation(AVLTreeNode *A);	//左右双旋
	AVLTreeNode *DoubleRightLeftRotation(AVLTreeNode *A);	//右左双旋
public:
	AVLTree();
	~AVLTree();
	void Clear(AVLTreeNode *&r);                            //删除以r为根的子树
	void Search(int elem);                                  //在树中查找节点
	AVLTreeNode* Insert(AVLTreeNode *T, int elem);          //在以T为根的树中插入节点
	void ShowTree();                                        //显示树形
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
	cout << "**             二叉排序树             **\n"
		<< "========================================\n"
		<< "**            1.建立二叉排序树        **\n"
		<< "**            2.插入元素              **\n"
		<< "**            3.查询元素              **\n"
		<< "**            4.退出程序              **\n"
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
	if (!T) {                                                //树根为NULL
		T = new AVLTreeNode(elem);
	} else if (elem < T->value) {                            //elem小于树根
		T->leftChild = Insert(T->leftChild, elem);           //插入到左子树
		if (GetHeight(T->leftChild) - GetHeight(T->rightChild) == 2) { //从T开始不平衡
			if (elem < T->leftChild->value)                 //elem在T左子树的左子树上
				T = SingleLeftRotation(T);
			else                                            //elem在T左子树的右子树上
				T = DoubleLeftRightRotation(T);
		}
	} else if (elem>T->value) {                             //elem大于树根
		T->rightChild = Insert(T->rightChild, elem);        //插入到右子树
		if (GetHeight(T->rightChild) - GetHeight(T->leftChild) == 2) { //从T开始不平衡
			if (elem > T->rightChild->value)                //elem在T右子树的右子树上
				T = SingleRightRotation(T);
			else											//elem在T右子树的左子树上
				T = DoubleRightLeftRotation(T);
		}
	} else {                                                //elem已经在树中
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

			//初始化
		case 1:
			Clear(root);
			cout << "Please input key to create Bsort_Tree:" << endl;
			Init();
			ShowTree();
			break;

			//插入
		case 2:
			cout << "Please input key to be inserted:";
			cin >> elem;
			root = Insert(root, elem);
			ShowTree();
			break;

			//搜索
		case 3:
			cout << "Please input key to be searched:";
			cin >> elem;
			Search(elem);
			break;

			//退出
		case 4:
			break;

			//输入非法
		default:
			cout << "Invalid input!" << endl;
			break;

		}
	} while (n != 4);
}

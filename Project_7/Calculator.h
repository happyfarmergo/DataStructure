#include "Node.h"
#include <sstream>
#include <stack>

using namespace std;

class Calculator {
private:
	Node *root;
private:
	bool IsNum(char ch);                                //判断ch是不是数字字符
	int getPriority(char optr);                         //返回optr的优先级
	bool IsSuperior(char cx, char cy);                  //若cx优先级低于cy，返回true，否则为false
	void Merge(stack<Node *>&opndStack,                 //合并两棵子树
		stack<char >&optrStack);
public:
	Calculator();
	~Calculator();
	void PreOrder(Node *r);                             //先序遍历
	void InOrder(Node *r);								//中序遍历
	void PostOrder(Node *r);							//后序遍历
	void Build();										//建立表达式树
	void Clear(Node *&r);								//销毁树
	void Run();											//主程序

};

Calculator::Calculator() :
root(NULL) {
}

Calculator::~Calculator() {
	Clear(root);
}

inline bool Calculator::IsNum(char ch) {
	return ch >= '0'&&ch <= '9';
}

inline int Calculator::getPriority(char optr) {
	return optr == '+' || optr == '-' ? 0 : 1;  //是＋-则返回0，否则（*/）返回1
}

inline bool Calculator::IsSuperior(char curOptr, char topOptr) {
	return getPriority(curOptr) <= getPriority(topOptr);
}

void Calculator::Merge(stack<Node *>&opndStack, stack<char >&optrStack) {
	Node *nodePtr, *lOpnd, *rOpnd;
	char topOptr;
	rOpnd = opndStack.top();                           //右子树
	opndStack.pop();
	lOpnd = opndStack.top();                           //左子树
	opndStack.pop();
	topOptr = optrStack.top();                         //树根
	optrStack.pop();
	nodePtr = new Node(OPTR, lOpnd, rOpnd);            //合并成一棵子树
	nodePtr->optr = topOptr;
	opndStack.push(nodePtr);                           //添加到操作数栈
}

void Calculator::Build() {
	char ch;
	int elem;
	Node *nodePtr;
	stack<Node *>opndStack;                            //操作数栈
	stack<char >optrStack;                             //操作符栈
	while (cin >> ch) {
		if (IsNum(ch)) {                               //读入为操作数
			cin.putback(ch);
			cin >> elem;
			nodePtr = new Node(OPND);
			nodePtr->opnd = elem;
			opndStack.push(nodePtr);
		} else {                                       //读入为操作符
			if (ch == '(')                             //读入'('，入栈
				optrStack.push(ch);
			else if (ch == ')') {                      //读入')',持续出栈直到栈顶为'('
				while (optrStack.top() != '(') 
					Merge(opndStack, optrStack);
				optrStack.pop();
			} else {
				while (!optrStack.empty()              //栈顶优先级比ch高，则合并子树
					&& optrStack.top() != '('
					&&IsSuperior(ch, optrStack.top())) 
					Merge(opndStack, optrStack);
				optrStack.push(ch);
			}
		}
	}
	while (!optrStack.empty())                         //栈不为空，进行最后的处理
		Merge(opndStack, optrStack);
	root = opndStack.top();
}

void Calculator::PreOrder(Node *r) {
	if (r) {
		if (r->tag == OPND)cout << r->opnd;
		else cout << r->optr;
		cout << ' ';
		PreOrder(r->leftChild);
		PreOrder(r->rightChild);
	}
}

void Calculator::InOrder(Node *r) {
	if (r) {
		if (r->tag == OPTR&&r->leftChild && r->leftChild->tag == OPTR &&getPriority(r->leftChild->optr) < getPriority(r->optr)) {
			cout << "( ";
			InOrder(r->leftChild);
			cout << ") ";
		} else
			InOrder(r->leftChild);

		if (r->tag == OPND)cout << r->opnd;
		else cout << r->optr;
		cout << ' ';
		if (r->tag == OPTR&&r->rightChild && r->rightChild->tag == OPTR &&getPriority(r->rightChild->optr) < getPriority(r->optr)) {
			cout << "( ";
			InOrder(r->rightChild);
			cout << ") ";
		} else
			InOrder(r->rightChild);
	}
}

void Calculator::PostOrder(Node *r) {
	if (r) {
		PostOrder(r->leftChild);
		PostOrder(r->rightChild);

		if (r->tag == OPND)cout << r->opnd;
		else cout << r->optr;
		cout << ' ';
	}
}

void Calculator::Clear(Node *&r) {
	if (r) {
		Clear(r->leftChild);
		Clear(r->rightChild);
		delete r;
		r = NULL;
	}
}

void Calculator::Run() {
	cout << "请输入表达式: ";
	Build();

	cout << "波兰表达式: ";
	PreOrder(root);
	cout << '\n' << endl;

	cout << "中缀表达式: ";
	InOrder(root);
	cout << '\n' << endl;

	cout << "逆波兰表达式: ";
	PostOrder(root);
	cout << '\n' << endl;
}
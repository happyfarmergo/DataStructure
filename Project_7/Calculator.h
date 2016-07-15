#include "Node.h"
#include <sstream>
#include <stack>

using namespace std;

class Calculator {
private:
	Node *root;
private:
	bool IsNum(char ch);                                //�ж�ch�ǲ��������ַ�
	int getPriority(char optr);                         //����optr�����ȼ�
	bool IsSuperior(char cx, char cy);                  //��cx���ȼ�����cy������true������Ϊfalse
	void Merge(stack<Node *>&opndStack,                 //�ϲ���������
		stack<char >&optrStack);
public:
	Calculator();
	~Calculator();
	void PreOrder(Node *r);                             //�������
	void InOrder(Node *r);								//�������
	void PostOrder(Node *r);							//�������
	void Build();										//�������ʽ��
	void Clear(Node *&r);								//������
	void Run();											//������

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
	return optr == '+' || optr == '-' ? 0 : 1;  //�ǣ�-�򷵻�0������*/������1
}

inline bool Calculator::IsSuperior(char curOptr, char topOptr) {
	return getPriority(curOptr) <= getPriority(topOptr);
}

void Calculator::Merge(stack<Node *>&opndStack, stack<char >&optrStack) {
	Node *nodePtr, *lOpnd, *rOpnd;
	char topOptr;
	rOpnd = opndStack.top();                           //������
	opndStack.pop();
	lOpnd = opndStack.top();                           //������
	opndStack.pop();
	topOptr = optrStack.top();                         //����
	optrStack.pop();
	nodePtr = new Node(OPTR, lOpnd, rOpnd);            //�ϲ���һ������
	nodePtr->optr = topOptr;
	opndStack.push(nodePtr);                           //��ӵ�������ջ
}

void Calculator::Build() {
	char ch;
	int elem;
	Node *nodePtr;
	stack<Node *>opndStack;                            //������ջ
	stack<char >optrStack;                             //������ջ
	while (cin >> ch) {
		if (IsNum(ch)) {                               //����Ϊ������
			cin.putback(ch);
			cin >> elem;
			nodePtr = new Node(OPND);
			nodePtr->opnd = elem;
			opndStack.push(nodePtr);
		} else {                                       //����Ϊ������
			if (ch == '(')                             //����'('����ջ
				optrStack.push(ch);
			else if (ch == ')') {                      //����')',������ջֱ��ջ��Ϊ'('
				while (optrStack.top() != '(') 
					Merge(opndStack, optrStack);
				optrStack.pop();
			} else {
				while (!optrStack.empty()              //ջ�����ȼ���ch�ߣ���ϲ�����
					&& optrStack.top() != '('
					&&IsSuperior(ch, optrStack.top())) 
					Merge(opndStack, optrStack);
				optrStack.push(ch);
			}
		}
	}
	while (!optrStack.empty())                         //ջ��Ϊ�գ��������Ĵ���
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
	cout << "��������ʽ: ";
	Build();

	cout << "�������ʽ: ";
	PreOrder(root);
	cout << '\n' << endl;

	cout << "��׺���ʽ: ";
	InOrder(root);
	cout << '\n' << endl;

	cout << "�沨�����ʽ: ";
	PostOrder(root);
	cout << '\n' << endl;
}
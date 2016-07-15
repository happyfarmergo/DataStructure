#include <iostream>
#include <string>
#include <cctype>

#define OPTR 0               //����ڵ�����Ϊ������
#define OPND 1               //����ڵ�����Ϊ������

class Node {
public:
	int tag;                 //�ڵ�����
	union {                  //�ڵ�����
		char optr;
		int opnd;
	};
	Node *leftChild;
	Node *rightChild;
	Node();
	Node(int id, Node *left = NULL, Node *right = NULL);
};

Node::Node() :
leftChild(NULL), rightChild(NULL) {
}

Node::Node(int id, Node *left, Node *right) :
tag(id), leftChild(left), rightChild(right) {
}


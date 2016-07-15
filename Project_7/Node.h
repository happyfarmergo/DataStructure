#include <iostream>
#include <string>
#include <cctype>

#define OPTR 0               //代表节点类型为操作符
#define OPND 1               //代表节点类型为操作数

class Node {
public:
	int tag;                 //节点类型
	union {                  //节点数据
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


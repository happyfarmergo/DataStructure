#ifndef _AVL_TREE_NODE_H_
#define _AVL_TREE_NODE_H_

#include <iostream>
#include <string>

using namespace std;

struct AVLTreeNode {
	int value;
	int height;
	AVLTreeNode *leftChild, *rightChild;
	AVLTreeNode() {}
	AVLTreeNode(int v, AVLTreeNode *left = NULL, AVLTreeNode *right = NULL) :
		value(v), height(0), leftChild(left), rightChild(right) {
	}
};

#endif